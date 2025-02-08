#include "file.h"

#include "sort/search.h"

namespace camellia::token {

std::string file_t::name() const {
  return self._name;
}

int file_t::base() const {
  return self._base;
}

int file_t::size() const {
  return self._size;
}

int file_t::line_count() {
  self._mutex.lock();
  const int n = static_cast<int>(self._lines.size());
  self._mutex.unlock();
  return n;
}

void file_t::add_line(int p_offset) {
  self._mutex.lock();
  if (const size_t i = self._lines.size();
      (i == 0 || self._lines[i - 1] < p_offset) && p_offset < self._size) {
    self._lines.emplace_back(p_offset);
  }
  self._mutex.unlock();
}

void file_t::merge_line(int p_line) {
  if (p_line < 1) {
    throw std::runtime_error(
        fmt::format("invalid line number {} (should be >= 1)", p_line));
  }
  self._mutex.lock();
  defer(self._mutex.unlock());
  if (p_line > self._lines.size()) {
    throw std::runtime_error(fmt::format(
        "invalid line number %d (should be < %d)", p_line, self._lines.size()));
  }
  // To merge the line numbered <p_line> with the line numbered <p_line+1>,
  // we need to remove the entry in lines corresponding to the line
  // numbered <p_line+1>. The entry in lines corresponding to the line
  // numbered <p_line+1> is located at index <p_line>, since indices in lines
  // are 0-based and line numbers are 1-based.
  std::copy(self._lines.begin() + p_line + 1, self._lines.end(),
            self._lines.begin() + p_line);
  self._lines.pop_back();
}

std::vector<int> file_t::lines() {
  self._mutex.lock();
  defer(self._mutex.unlock());
  auto copy = self._lines;
  return copy;
}

void file_t::set_lines(const std::vector<int>& p_lines) {
  // varify validity of lines table
  for (int i = 0; i < p_lines.size(); i++) {
    if (i > 0 && p_lines[i] <= p_lines[i - 1] || p_lines.size() <= p_lines[i]) {
      throw std::runtime_error("invalid line");
    }
  }
  // set line table
  self._mutex.lock();
  defer(self._mutex.unlock());
  self._lines = p_lines;
}

void file_t::set_lines_for_content(const std::vector<uint8_t>& p_content) {
  std::vector<int> lines;
  int line = 0;
  for (int i = 0; i < p_content.size(); i++) {
    if (line >= 0) {
      lines.emplace_back(line);
    }
    line = -1;
    if (p_content[i] == '\n') {
      line = i + 1;
    }
  }
  // set line table
  self._mutex.lock();
  defer(self._mutex.unlock());
  self._lines = lines;
}

pos_t file_t::line_start(int p_line) {
  if (p_line < 1) {
    panic("invalid line number {} (should be >= 1)", p_line);
  }
  self._mutex.lock();
  defer(self._mutex.unlock());
  if (p_line > self._lines.size()) {
    panic("invalid line number {} (should be < {})", p_line,
          self._lines.size());
  }
  return pos_t(self._base + self._lines[p_line - 1]);
}

void file_t::add_line_info(int p_offset, const std::string& p_filename,
                           int p_line) {
  self.add_line_column_info(p_offset, p_filename, p_line, 1);
}

void file_t::add_line_column_info(int p_offset, const std::string& p_filename,
                                  int p_line, int p_column) {
  self._mutex.lock();
  defer(self._mutex.unlock());
  if (def const i = self._infos.size();
      (i == 0 || self._infos[i - 1].offset < p_offset) &&
      p_offset < self._size) {
    self._infos.emplace_back(
        line_info_t{p_offset, p_filename, p_line, p_column});
  }
}

pos_t file_t::pos(int p_offset) {
  if (p_offset > self.size()) {
    panic("invalid file offset {} (should be <= {})", p_offset, self._size);
  }
  return pos_t{self._base + p_offset};
}

int file_t::offset(const pos_t& p_pos) {
  if (p_pos.value < self._base || p_pos.value > self._base + self._size) {
    panic("invalid Pos value {} (should be in [{}, {}])", p_pos.value,
          self._base, self._base + self._size);
  }
  return p_pos.value - self._base;
}

int file_t::line(const pos_t& p_pos) {
  return self.position(p_pos).line;
}

position_t file_t::position_for(pos_t p_pos, bool p_adjusted) {
  position_t position = {};
  if (p_pos.value != pos_t::k_no_pos) {
    if (p_pos.value < self._base || self._base + self._size) {
      panic("invalid Pos value {} (should be in [{}, {}])", p_pos.value,
            self._base, self._base + self._size);
    }
    position = self._positon(p_pos, p_adjusted);
  }
  return position;
}

position_t file_t::position(pos_t p_pos) {
  return position_for(p_pos, true);
}

std::tuple<std::string, int, int> file_t::_unpack(int p_offset,
                                                  bool p_adjusted) {
  int line = 0, column = 0;
  std::string filename = self._name;
  self._mutex.lock();
  defer(self._mutex.unlock());
  if (const int i = search_ints(self._lines, p_offset); i >= 0) {
    line = i + 1;
    column = p_offset - self._lines[i] + 1;
  }
  if (p_adjusted && !self._infos.empty()) {
    // few files have extra line infos
    if (const int i = search_infos(self._infos, p_offset); i >= 0) {
      const line_info_t& alt = self._infos[i];
      filename = alt.filename;
      if (const int j = search_ints(self._lines, alt.offset); j >= 0) {
        // j+1 is the line at which the alternative position was recorded
        const int d =
            line - (j + 1);  // line distance from alternative position base
        line = alt.line + d;
        if (alt.column == 0) {
          // alternative column is unknown => relative column is unknown
          // (the current specification for line directives requires
          // this to apply until the next PosBase/line directive,
          // not just until the new newline)
          column = 0;
        } else if (d == 0) {
          // the alternative position base is on the current line
          // => column is relative to alternative column
          column = alt.column + (p_offset - alt.offset);
        }
      }
    }
  }
  return {filename, line, column};
}

position_t file_t::_positon(pos_t p_pos, bool p_adjusted) {
  position_t ans;
  int offset = p_pos.value - self._base;
  ans.offset = offset;
  std::tie(ans.filename, ans.line, ans.column) =
      self._unpack(offset, p_adjusted);
  return ans;
}

int file_t::search_ints(const std::vector<int>& p_vec, int p_value) {
  return sort::search(static_cast<int>(p_vec.size()),
                      [&](const int i) -> bool { return p_vec[i] > p_value; }) -
         1;
}

int file_t::search_infos(const std::vector<line_info_t>& p_infos, int p_value) {
  return sort::search(
             static_cast<int>(p_infos.size()),
             [&](const int i) -> bool { return p_infos[i].offset > p_value; }) -
         1;
}

}  // namespace camellia::token
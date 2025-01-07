#include "file.h"

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
  if(p_line > self._lines.size()) {
    panic("invalid line number {} (should be < {})", p_line, self._lines.size());
  }
  return pos_t(self._base + self._lines[p_line-1]);
}

}  // namespace camellia::token
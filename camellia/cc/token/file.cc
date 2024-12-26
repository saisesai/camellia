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
  defer _(nullptr, [&](...) { self._mutex.unlock(); });
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

}  // namespace camellia::token
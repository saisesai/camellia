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

}  // namespace camellia::token
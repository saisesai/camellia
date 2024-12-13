#ifndef CAMELLIA_TOKEN_FILE_H
#define CAMELLIA_TOKEN_FILE_H

#include <mutex>
#include <string>
#include <vector>

#include "line_info.h"

namespace camellia::token {

// A file_t is a handle for a file belonging to a file_set_t.
// A file_t has a name, size, and line offset table.
class file_t {
  std::string _name;  // file name as provided to add_file
  int _base = 0;      // pos_t value range for this file is [base...base+size]
  int _size = 0;      // file size as provided to add_file

  // lines and infos are protected by mutex.
  std::mutex _mutex;
  // lines contains the offset of the first character for each line (the first entry is always 0).
  std::vector<int> _lines;
  std::vector<line_info_t> _infos;
};
}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_FILE_H

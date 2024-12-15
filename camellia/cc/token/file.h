#ifndef CAMELLIA_TOKEN_FILE_H
#define CAMELLIA_TOKEN_FILE_H

#include "config.h"

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

  // name returns the file name of file f as registered with add_file.
  [[nodiscard]] std::string name() const;

  // base returns the base offset of file f as registered with add_file.
  [[nodiscard]] int base() const;

  // size returns the size of file f as registered with add_file.
  [[nodiscard]] int size() const;

  // line_count returns the number of lines in file f.
  [[nodiscard]] int line_count();

  // add_line adds the line offset for a new line.
  // The line offset must be larger than the offset for the previous line
  // and smaller than the file size; otherwise the line offset is ignored.
  void add_line(int p_offset);
};

}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_FILE_H

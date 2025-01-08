#ifndef CAMELLIA_TOKEN_FILE_H
#define CAMELLIA_TOKEN_FILE_H

#include "config.h"

#include "common/mutex.h"

#include "line_info.h"
#include "pos.h"

namespace camellia::token {

// A file_t is a handle for a file belonging to a file_set_t.
// A file_t has a name, size, and line offset table.
class file_t {
  std::string _name;  // file name as provided to add_file
  int _base = 0;      // pos_t value range for this file is [base...base+size]
  int _size = 0;      // file size as provided to add_file

  // lines and infos are protected by mutex.
  common::mutex_t _mutex;
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

  // merge_line merges a line with the following line. It is akin to replacing
  // the newline character at the end of the line with a space (to not change the
  // remaining offsets). To obtain the line number, consult e.g. Position.Line.
  // merge_line will panic if given an invalid line number.
  void merge_line(int p_line);

  // lines returns the effective line offset table of the form described by set_lines.
  // Callers must not mutate the result.
  [[nodiscard]] std::vector<int> lines();

  // set_lines sets the line offsets for a file and reports whether it succeeded.
  // The line offsets are the offsets of the first character of each line;
  // for instance for the content "ab\nc\n" the line offsets are {0, 3}.
  // An empty file has an empty line offset table.
  // Each line offset must be larger than the offset for the previous line
  // and smaller than the file size; otherwise set_lines fails and returns
  // false.
  // Callers must not mutate the provided slice after SetLines returns.
  void set_lines(const std::vector<int>& p_lines);

  // set_lines_for_content sets the line offsets for the given file content.
  // It ignores position-altering //line comments.
  void set_lines_for_content(const std::vector<byte>& p_content);

  // line_start returns the pos_t value of the start of the specified line.
  // It ignores any alternative positions set using add_line_colomn_info.
  // line_start panics if the 1-based line number is invalid.
  pos_t line_start(int p_line);
};

}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_FILE_H

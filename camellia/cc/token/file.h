#ifndef CAMELLIA_TOKEN_FILE_H
#define CAMELLIA_TOKEN_FILE_H

#include "config.h"

#include "common/mutex.h"

#include "line_info.h"
#include "pos.h"
#include "position.h"

namespace camellia::token {

// A file_t is a handle for a file belonging to a file_set_t.
// A file_t has a name, size, and line offset table.
class file_t {
 public:
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

  // add_line_info is like add_line_column_info with a column = 1 argument.
  void add_line_info(int p_offset, const std::string& p_filename, int p_line);

  // add_line_column_info adds alternative file, line, and column number
  // information for a given file offset. The offset must be larger
  // than the offset for the previously added alternative line info
  // and smaller than the file size; otherwise the information is
  // ignored.
  //
  // add_line_column_info is typically used to register alternative position
  // information for line directives such as //line filename:line:column.
  void add_line_column_info(int p_offset, const std::string& p_filename,
                            int p_line, int p_column);

  // pos returns the pos value for the given file offset;
  // the offset must be <= f.size().
  // f.pos(f.offset(p)) == p.
  pos_t pos(int p_offset);

  // offset returns the offset for the given file position p;
  // p must be a valid Pos value in that file.
  // f.offset(f.pos(offset)) == offset.
  int offset(const pos_t& p_pos);

  // line returns the line number for the given file position p;
  // p must be a Pos value in that file or k_no_pos.
  int line(const pos_t& p_pos);

  // position_for returns the position_t value for the given file position p.
  // If adjusted is set, the position may be adjusted by position-altering
  // //line comments; otherwise those comments are ignored.
  // p must be a pos_t value in f or k_no_pos.
  position_t position_for(pos_t p_pos, bool p_adjusted);

  // position returns the position_t value for the given file position p.
  // Calling f.position(p) is equivalent to calling f.position_for(p, true).
  position_t position(pos_t p_pos);

 private:
  std::string _name;  // file name as provided to add_file
  int _base = 0;      // pos_t value range for this file is [base...base+size]
  int _size = 0;      // file size as provided to add_file

  // _unpack returns the filename and line and column number for a file offset.
  // If adjusted is set, unpack will return the filename and line information
  // possibly adjusted by //line comments; otherwise those comments are ignored.
  std::tuple<std::string, int, int> _unpack(int p_offset, bool p_adjusted);

  // _postion returns postion info for the given pos
  position_t _positon(pos_t p_pos, bool p_adjusted);

  // helper functions
 public:
  static int search_ints(const std::vector<int>& p_vec, int p_value);
  static int search_infos(const std::vector<line_info_t>& p_infos, int p_value);
};

}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_FILE_H

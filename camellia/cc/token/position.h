#ifndef CAMELLIA_TOKEN_POSITION_H
#define CAMELLIA_TOKEN_POSITION_H

#include <string>

namespace camellia::token {

// position_t describes an arbitrary source position
// including the file, line, and column location.
// A position_t is valid if the line number is > 0.
class position_t {
public:
  std::string filename;
  int offset;
  int line;
  int column;

  // is_valid reports whether the position is valid.
  [[nodiscard]] bool is_valid() const;

  // string returns a string in one of several forms:
  //
  //	file:line:column    valid position with file name
  //	file:line           valid position with file name but no column (column == 0)
  //	line:column         valid position without file name
  //	line                valid position without file name and no column (column == 0)
  //	file                invalid position with file name
  //	-                   invalid position without file name
  [[nodiscard]] std::string string() const;
};

} // namespace: camellia::token

#endif // CAMELLIA_TOKEN_POSITION_H

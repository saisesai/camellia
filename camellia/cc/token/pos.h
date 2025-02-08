#ifndef CAMELLIA_TOKEN_POS_H
#define CAMELLIA_TOKEN_POS_H

#include "config.h"

namespace camellia::token {
// pos_t is a compact encoding of a source position within a file set.
// It can be converted into a postion_t for a more convenient, but much
// larger, representation.
//
// The pos_t value for a given file is a number in the range [base, base+size],
// where base and size are specified when a file is added to the file set.
// The difference between a pos_t value and the corresponding file base
// corresponds to the byte offset of that position (represented by the Pos value)
// from the beginning of the file. Thus, the file base offset is the Pos value
// representing the first byte in the file.
//
// To create the pos_t value for a specific source offset (measured in bytes),
// first add the respective file to the current file set using file_set.add_file
// and then call file_t.pos(offset) for that file. Given a pos_t value p
// for a specific file set fset, the corresponding Position value is
// obtained by calling fset.position(p).
//
// pos_t values can be compared directly with the usual comparison operators:
// If two Pos values p and q are in the same file, comparing p and q is
// equivalent to comparing the respective source file offsets. If p and q
// are in different files, p < q is true if the file implied by p was added
// to the respective file set before the file implied by q.
class pos_t {
 public:
  enum Value { k_no_pos = 0 };
  int value = 0;

  explicit pos_t(int p_value);

  [[nodiscard]] bool is_valid() const;
};
}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_POS_H

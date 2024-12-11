#ifndef CAMELLIA_TOKEN_UTILS_H
#define CAMELLIA_TOKEN_UTILS_H

#include "token.h"

namespace camellia::token {

class utils {
 public:
  // Maps an identifier to its keyword token or IDENT (if not a keyword).
  static token_t lookup(const std::string& p_ident);

  // Reports whether name not starts with an '_'.
  static bool is_export(const std::string & p_name);

  // Reports whether name is a camellia keyword, such as "proc" or "return".
  static bool is_keyword(const std::string & p_name);

  // Reports whether name is a Go identifier, that is, a non-empty
  // string made up of letters, digits, and underscores, where the first character
  // is not a digit. Keywords are not identifiers.
  static bool is_identifier(const std::string & p_name);
};

}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_UTILS_H

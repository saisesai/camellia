#include "token_utils.h"

namespace camellia::token {

token_t utils::lookup(const std::string& p_ident) {
  for (const auto& [key, value] : token_t::tokens) {
    if (value == p_ident) {
      return key;
    }
  }
  return token_t::k_ident;
}

bool utils::is_export(const std::string& p_name) {
  return p_name[0] != '_';
}

bool utils::is_keyword(const std::string& p_name) {
  return lookup(p_name).is_keyword();
}

bool utils::is_identifier(const std::string& p_name) {
  if (p_name.empty() || is_keyword(p_name)) {
    return false;
  }

  for (int i = 0; i < p_name.length(); i++) {
    if (!isalpha(p_name[i]) && p_name[i] != '_' &&
        (i == 0 || !isdigit(p_name[i]))) {
      return false;
    }
  }

  return true;
}

}  // namespace camellia::token
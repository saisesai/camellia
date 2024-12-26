#include "token.h"

namespace camellia::token {

std::map<token_t, std::string> g_tokens = {
    {token_t::k_illegal, "ILLEGAL"},
    {token_t::k_eof, "EOF"},
    {token_t::k_comment, "COMMENT"},
    {token_t::k_ident, "IDENT"},
    {token_t::k_int, "INT"},
    {token_t::k_float, "FLOAT"},
    {token_t::k_imag, "IMAG"},
    {token_t::k_char, "CHAR"},
    {token_t::k_string, "STRING"},
    {token_t::k_add, "+"},
    {token_t::k_sub, "-"},
    {token_t::k_mul, "*"},
    {token_t::k_quo, "/"},
    {token_t::k_rem, "%"},
    {token_t::k_and, "&"},
    {token_t::k_or, "|"},
    {token_t::k_xor, "^"},
    {token_t::k_shl, "<<"},
    {token_t::k_shr, ">>"},
    {token_t::k_and_not, "&^"},
    {token_t::k_add_assign, "+="},
    {token_t::k_sub_assign, "-="},
    {token_t::k_mul_assign, "*="},
    {token_t::k_quo_assign, "/="},
    {token_t::k_mod_assign, "%="},
    {token_t::k_add_assign, "+="},
    {token_t::k_and_assign, "&="},
    {token_t::k_or_assign, "|="},
    {token_t::k_xor_assign, "^="},
    {token_t::k_shl_assign, "<<="},
    {token_t::k_shr_assign, ">>="},
    {token_t::k_and_not_assign, "&^="},
    {token_t::k_land, "&&"},
    {token_t::k_lor, "||"},
    {token_t::k_inc, "++"},
    {token_t::k_dec, "--"},
    {token_t::k_eql, "=="},
    {token_t::k_lss, "<"},
    {token_t::k_gtr, ">"},
    {token_t::k_assign, "="},
    {token_t::k_not, "!"},
    {token_t::k_neq, "!="},
    {token_t::k_leq, "<="},
    {token_t::k_geq, ">="},
    {token_t::k_ellipsis, "..."},
    {token_t::k_lparen, "("},
    {token_t::k_lbrack, "["},
    {token_t::k_lbrace, "{"},
    {token_t::k_comma, ","},
    {token_t::k_period, "."},
    {token_t::k_rparen, ")"},
    {token_t::k_rbrack, "]"},
    {token_t::k_rbrace, "}"},
    {token_t::k_semicolon, ";"},
    {token_t::k_colon, ":"},
    {token_t::k_def, "def"},
    {token_t::k_import, "import"},
    {token_t::k_native, "native"},
    {token_t::k_proc, "proc"},
    {token_t::k_return, "return"},
    {token_t::k_for, "for"},
    {token_t::k_break, "break"},
    {token_t::k_continue, "continue"},

};

std::string token_t::string() const {
  if (g_tokens.find(self._value) != g_tokens.end()) {
    return g_tokens[self._value];
  }
  return "TOKEN(" + std::to_string(self._value) + ")";
}

int token_t::precedence() const {
  switch (self._value) {
    case k_lor:
      return 1;
    case k_land:
      return 2;
    case k_eql:
    case k_neq:
    case k_lss:
    case k_leq:
    case k_gtr:
    case k_geq:
      return 3;
    case k_add:
    case k_sub:
    case k_or:
    case k_xor:
      return 4;
    case k_mul:
    case k_quo:
    case k_rem:
    case k_shl:
    case k_shr:
    case k_and:
    case k_and_not:
      return 5;
    default:
      return k_lowest_prec;
  }
}

bool token_t::is_literal() const {
  return k_literal_begin < self._value && self._value < k_literal_end;
}

bool token_t::is_operator() const {
  return k_operator_begin < self._value && self._value < k_operator_end;
}

bool token_t::is_keyword() const {
  return k_keyword_begin < self._value && self._value < k_keyword_end;
}

bool token_t::operator<(const token_t& p_rhs) const {
  return self._value < p_rhs._value;
}

token_t lookup(const std::string& p_ident) {
  for (const auto& [key, value] : g_tokens) {
    if (value == p_ident) {
      return key;
    }
  }
  return token_t::k_ident;
}

bool is_export(const std::string& p_name) {
  return p_name[0] != '_';
}

bool is_keyword(const std::string& p_name) {
  return lookup(p_name).is_keyword();
}

bool is_identifier(const std::string& p_name) {
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
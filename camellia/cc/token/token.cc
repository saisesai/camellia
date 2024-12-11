#include "token.h"

namespace camellia::token {

std::map<token_t, std::string> token_t::tokens = {
    {k_illegal, "ILLEGAL"},
    {k_eof, "EOF"},
    {k_comment, "COMMENT"},
    {k_ident, "IDENT"},
    {k_int, "INT"},
    {k_float, "FLOAT"},
    {k_imag, "IMAG"},
    {k_char, "CHAR"},
    {k_string, "STRING"},
    {k_add, "+"},
    {k_sub, "-"},
    {k_mul, "*"},
    {k_quo, "/"},
    {k_rem, "%"},
    {k_and, "&"},
    {k_or, "|"},
    {k_xor, "^"},
    {k_shl, "<<"},
    {k_shr, ">>"},
    {k_and_not, "&^"},
    {k_add_assign, "+="},
    {k_sub_assign, "-="},
    {k_mul_assign, "*="},
    {k_quo_assign, "/="},
    {k_mod_assign, "%="},
    {k_add_assign, "+="},
    {k_and_assign, "&="},
    {k_or_assign, "|="},
    {k_xor_assign, "^="},
    {k_shl_assign, "<<="},
    {k_shr_assign, ">>="},
    {k_and_not_assign, "&^="},
    {k_land, "&&"},
    {k_lor, "||"},
    {k_inc, "++"},
    {k_dec, "--"},
    {k_eql, "=="},
    {k_lss, "<"},
    {k_gtr, ">"},
    {k_assign, "="},
    {k_not, "!"},
    {k_neq, "!="},
    {k_leq, "<="},
    {k_geq, ">="},
    {k_ellipsis, "..."},
    {k_lparen, "("},
    {k_lbrack, "["},
    {k_lbrace, "{"},
    {k_comma, ","},
    {k_period, "."},
    {k_rparen, ")"},
    {k_rbrack, "]"},
    {k_rbrace, "}"},
    {k_semicolon, ";"},
    {k_colon, ":"},
    {k_def, "def"},
    {k_import, "import"},
    {k_native, "native"},
    {k_proc, "proc"},
    {k_return, "return"},
    {k_for, "for"},
    {k_break, "break"},
    {k_continue, "continue"},

};

std::string token_t::string() const {
  if (tokens.find(_value) != tokens.end()) {
    return tokens[_value];
  }
  return "TOKEN(" + std::to_string(_value) + ")";
}

int token_t::precedence() const {
  switch (_value) {
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
  return k_literal_begin < _value && _value < k_literal_end;
}

bool token_t::is_operator() const {
  return k_operator_begin < _value && _value < k_operator_end;
}

bool token_t::is_keyword() const {
  return k_keyword_begin < _value && _value < k_keyword_end;
}

bool token_t::operator<(const token_t& p_rhs) const {
  return _value < p_rhs._value;
}

}  // namespace camellia::token
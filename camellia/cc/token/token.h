#ifndef CAMELLIA_TOKEN_H
#define CAMELLIA_TOKEN_H

#include "config.h"

namespace camellia::token {

class token_t {
 public:
  // The list of tokens.
  enum value {
    // Special tokens.
    k_illegal,
    k_eof,
    k_comment,

    // Indentifiers and basic type literals.
    k_literal_begin,

    k_ident,   // main
    k_int,     // 12345
    k_float,   // 123.45
    k_imag,    // 123.45i
    k_char,    // 'a'
    k_string,  // "abc"

    k_literal_end,

    // Operators and delimitors.
    k_operator_begin,

    k_add,  // +
    k_sub,  // -
    k_mul,  // *
    k_quo,  // /
    k_rem,  // %

    k_and,      // &
    k_or,       // |
    k_xor,      // ^
    k_shl,      // <<
    k_shr,      // >>
    k_and_not,  // &^

    k_add_assign,  // +=
    k_sub_assign,  // -=
    k_mul_assign,  // *=
    k_quo_assign,  // /=
    k_mod_assign,  // %=

    k_and_assign,      // &=
    k_or_assign,       // |=
    k_xor_assign,      // ^=
    k_shl_assign,      // <<=
    k_shr_assign,      // >>=
    k_and_not_assign,  // &^=

    k_land,  // &&
    k_lor,   // ||
    k_inc,   // ++
    k_dec,   // --

    k_eql,     // ==
    k_lss,     // <
    k_gtr,     // >
    k_assign,  // =
    k_not,     // !

    k_neq,       // !=
    k_leq,       // <=
    k_geq,       // >=
    k_ellipsis,  // ...

    k_lparen,  // (
    k_lbrack,  // [
    k_lbrace,  // {
    k_comma,   // ,
    k_period,  // .

    k_rparen,     // )
    k_rbrack,     // ]
    k_rbrace,     // }
    k_semicolon,  // ;
    k_colon,      // :

    k_operator_end,

    // Keywords.
    k_keyword_begin,

    k_def,     // def
    k_import,  // import
    k_native,  // native

    k_proc,    // proc
    k_return,  // return

    k_for,       // for
    k_break,     // break
    k_continue,  // continue

    k_keyword_end,
  };

  // A set of constants for precedence-based expression parsing.
  // Non-operators have lowest precedence, followed by operators
  // starting with precedence 1 up to unary operators. The highest
  // precedence serves as "catch-all" precedence for selector,
  // indexing, and other operator and delimiter tokens.
  enum precedence_set {
    k_lowest_prec = 0,  // non-operators
    k_unary_prec = 6,
    k_highest_prec = 7,
  };

  // Default constructor.
  token_t() = default;

  // Initializes the token_t object with a given value.
  // It allows implicit conversion from the value type to token_t.
  constexpr token_t(value p_value) : _value(p_value) {}  // NOLINT

  // Returns the correcsponding string to the token.
  [[nodiscard]] std::string string() const;

  // Returns the operator precedence of the binary operator op.
  // If op is not a binary operator, the result is LowestPrecedence.
  [[nodiscard]] int precedence() const;

  // Returns true for tokens corresponding to identifiers
  // and basic type literals; it returns false otherwise.
  [[nodiscard]] bool is_literal() const;

  // Returns true for tokens corresponding to operators and
  // delimiters; it returns false otherwise.
  [[nodiscard]] bool is_operator() const;

  // Returns true for tokens corresponding to keywords;
  // it returns false otherwise.
  [[nodiscard]] bool is_keyword() const;

  // Compares the current token_t object with another token_t object (p_rhs).
  // Returns true if the current object is considered less than p_rhs.
  // This allows token_t to be used as a key type in associative containers like std::map.
  bool operator<(const token_t& p_rhs) const;

 private:
  value _value = k_illegal;
};

// map<token int value, token string value>
extern std::map<token_t, std::string> g_tokens;

// Maps an identifier to its keyword token or IDENT (if not a keyword).
token_t lookup(const std::string& p_ident);

// Reports whether name not starts with an '_'.
bool is_export(const std::string& p_name);

// Reports whether name is a camellia keyword, such as "proc" or "return".
bool is_keyword(const std::string& p_name);

// Reports whether name is a Go identifier, that is, a non-empty
// string made up of letters, digits, and underscores, where the first character
// is not a digit. Keywords are not identifiers.
bool is_identifier(const std::string& p_name);

}  // namespace camellia::token

#endif  // CAMELLIA_TOKEN_H

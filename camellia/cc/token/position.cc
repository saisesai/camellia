#include "position.h"

bool camellia::token::position_t::is_valid() const {
  return line > 0;
}

std::string camellia::token::position_t::string() const {
  std::string out = filename;
  if (is_valid()) {
    if (!out.empty()) {
      out += ":";
    }
    out += std::to_string(line);
    if (column != 0) {
      out += ":" + std::to_string(column);
    }
  }
  if (out.empty()) {
    out = "-";
  }
  return out;
}
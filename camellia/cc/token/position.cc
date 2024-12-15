#include "position.h"

bool camellia::token::position_t::is_valid() const {
  return self.line > 0;
}

std::string camellia::token::position_t::string() const {
  std::string out = self.filename;
  if (self.is_valid()) {
    if (!out.empty()) {
      out += ":";
    }
    out += std::to_string(self.line);
    if (self.column != 0) {
      out += ":" + std::to_string(self.column);
    }
  }
  if (out.empty()) {
    out = "-";
  }
  return out;
}
#include "pos.h"

namespace camellia::token {

bool pos_t::is_valid() const {
  return value != no_pos;
}

}  // namespace camellia::token
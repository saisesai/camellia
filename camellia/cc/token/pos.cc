#include "pos.h"

namespace camellia::token {

bool pos_t::is_valid() const {
  return self.value != k_no_pos;
}

}  // namespace camellia::token
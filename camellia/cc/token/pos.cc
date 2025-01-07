#include "pos.h"

namespace camellia::token {

pos_t::pos_t(int p_value) {
  self.value = p_value;
}

bool pos_t::is_valid() const {
  return self.value != k_no_pos;
}

}  // namespace camellia::token
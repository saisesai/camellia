#include "mutex.h"

namespace camellia::common {

mutex_t::mutex_t() {
  if (def const err = uv_mutex_init(&self._uv_mutex); err != nil) {
    panic("falied to create mutex: {}", uv_strerror(err));
  }
}

mutex_t::~mutex_t() {
  uv_mutex_destroy(&self._uv_mutex);
}

void mutex_t::lock() {
  uv_mutex_lock(&self._uv_mutex);
}

void mutex_t::unlock() {
  uv_mutex_unlock(&self._uv_mutex);
}

}  // namespace camellia::common
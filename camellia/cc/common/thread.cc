#include "thread.h"


namespace camellia::common {

thread_t::thread_t(thread_entry_t p_entry, void* p_args) {
  if (def const err = uv_thread_create(&self._uv_thread, p_entry, p_args);
      err != nil) {
    panic("falied to create thread: {}", uv_strerror(err));
  }
}

void thread_t::join() {
  if(def const err = uv_thread_join(&self._uv_thread); err != nil) {
    panic("falied to join thread: {}", uv_strerror(err));
  }
}

} // namespace camellia::common
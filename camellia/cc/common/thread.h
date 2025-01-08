#ifndef CAMELLIA_COMMON_THREAD_H
#define CAMELLIA_COMMON_THREAD_H

#include "config.h"

namespace camellia::common {

typedef uv_thread_cb thread_entry_t;

class thread_t {
public:
  thread_t() = delete;

  thread_t(thread_entry_t p_entry, void* p_args);

  virtual ~thread_t();

  void join();

private:
  uv_thread_t _uv_thread{};
};

} // namespace camellia::common

#endif // CAMELLIA_COMMON_THREAD_H

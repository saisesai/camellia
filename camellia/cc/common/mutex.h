#ifndef CAMELLIA_COMMON_MUTEX_H
#define CAMELLIA_COMMON_MUTEX_H

#include "config.h"

namespace camellia::common {

class mutex_t {
public:
  mutex_t();

  virtual ~mutex_t();

  void lock();

  void unlock();

private:
  uv_mutex_t _uv_mutex{};
};

}

#endif // CAMELLIA_COMMON_MUTEX_H

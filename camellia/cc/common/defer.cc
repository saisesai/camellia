#include "defer.h"

#include <utility>

#include "config.h"

camellia::common::Defer::Defer(std::function<void()> p_func) {
  self._func = std::move(p_func);
}

camellia::common::Defer::~Defer() {
  self._func();
}
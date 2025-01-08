#include "defer.h"

#include <utility>

#include "config.h"

camellia::builtin::Defer::Defer(std::function<void()> p_func) {
  self._func = std::move(p_func);
}

camellia::builtin::Defer::~Defer() {
  self._func();
}
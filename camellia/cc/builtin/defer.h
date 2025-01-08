#ifndef CAMELLIA_BUILTIN_DEFER_H
#define CAMELLIA_BUILTIN_DEFER_H

#include <functional>

namespace camellia::builtin {

class Defer {
 public:
  explicit Defer(std::function<void()> p_func);
  ~Defer();

 private:
  std::function<void()> _func;
};

}  // namespace camellia::builtin


#define DEFER_CONCATENATE(x, y) x##y
#define DEFER_MAKE_UNIQUE_NAME(x, y) DEFER_CONCATENATE(x, y)
#define DEFER(func) camellia::builtin::Defer DEFER_MAKE_UNIQUE_NAME(__defer_, __LINE__)([&]() { func; })
#define defer(func) DEFER(func)

#endif  // CAMELLIA_BUILTIN_DEFER_H

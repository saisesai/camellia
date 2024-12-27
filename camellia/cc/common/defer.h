#ifndef CAMELLIA_COMMON_DEFER_H
#define CAMELLIA_COMMON_DEFER_H

#include <functional>

namespace camellia::common {

class Defer {
 public:
  explicit Defer(std::function<void()> p_func);
  ~Defer();

 private:
  std::function<void()> _func;
};

}  // namespace camellia::common


#define DEFER_CONCATENATE(x, y) x##y
#define DEFER_MAKE_UNIQUE_NAME(x, y) DEFER_CONCATENATE(x, y)
#define DEFER(func) Defer DEFER_MAKE_UNIQUE_NAME(__defer_, __LINE__)([&]() { func; })
#define defer(func) DEFER(func)

#endif  // CAMELLIA_COMMON_DEFER_H

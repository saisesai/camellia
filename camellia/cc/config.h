#ifndef CMELLIA_CONFIG_H
#define CMELLIA_CONFIG_H

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

#include "fmt/core.h"

#define self (*(this))

namespace camellia {
using defer = std::shared_ptr<void>;
}  // namespace camellia

#endif  // CMELLIA_CONFIG_H

#ifndef CMELLIA_CONFIG_H
#define CMELLIA_CONFIG_H

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

#include "fmt/core.h"

#include "common/defer.h"

#define byte uint8_t
#define self (*(this))
#define panic(mp_fmt, ...) throw std::runtime_error(fmt::format(mp_fmt, ##__VA_ARGS__))

namespace camellia {
using namespace common;
}  // namespace camellia


#endif  // CMELLIA_CONFIG_H

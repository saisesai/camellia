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

#define self (*(this))

namespace camellia {
using namespace common;
}  // namespace camellia

#endif  // CMELLIA_CONFIG_H

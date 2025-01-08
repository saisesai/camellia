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

// 3rd
#include "fmt/core.h"
#include "uv.h"

#include "builtin/defer.h"

#define nil 0
#define def auto
#define byte uint8_t
#define self (*(this))
#define panic(mp_fmt, ...) throw std::runtime_error(fmt::format(mp_fmt, ##__VA_ARGS__))


#endif  // CMELLIA_CONFIG_H

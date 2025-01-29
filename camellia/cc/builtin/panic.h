#ifndef CAMELLIA_BUILTIN_PANIC_H
#define CAMELLIA_BUILTIN_PANIC_H

#define panic(__mp_fmt, ...) throw std::runtime_error(fmt::format(__mp_fmt, ##__VA_ARGS__))

#endif // CAMELLIA_BUILTIN_PANIC_H

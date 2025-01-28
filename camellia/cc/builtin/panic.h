#ifndef CAMELLIA_BUILTIN_PANIC_H
#define CAMELLIA_BUILTIN_PANIC_H

#define panic(mp_fmt, ...) throw std::runtime_error(fmt::format(mp_fmt, ##__VA_ARGS__))

#endif // CAMELLIA_BUILTIN_PANIC_H

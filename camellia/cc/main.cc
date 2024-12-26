#include <iostream>

#include "token/token.h"

using namespace camellia;

int main() {
  defer _(nullptr, [](...) { std::cout << "defer" << std::endl; });
  std::cout << (token::is_export("abc") ? "yes" : "no") << std::endl;
  std::cout << (token::is_export("_abc") ? "yes" : "no") << std::endl;
  return 0;
}
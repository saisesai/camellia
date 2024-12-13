#include <iostream>

#include "token/token.h"
#include "token/token_utils.h"

using namespace camellia::token;

int main() {
  std::cout << (utils::is_export("abc") ? "yes" : "no") << std::endl;
  std::cout << (utils::is_export("_abc") ? "yes" : "no") << std::endl;
  return 0;
}
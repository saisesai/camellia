#include <iostream>

#include "token/token.h"
#include "token/utils.h"

using namespace camellia::token;

int main() {
  std::cout << utils::is_identifier("1a123") << std::endl;
  return 0;
}
#include "search.h"

namespace camellia::sort {

int search(int p_n, const std::function<bool(int)>& p_f) {
  int i = 0, j = p_n;
  while (i < j) {
    if (const int h = (i + j) >> 1; !p_f(h)) {
      i = h + 1;
    } else {
      j = h;
    }
  }
  return i;
}

}  // namespace camellia::sort
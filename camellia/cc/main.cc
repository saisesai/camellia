#include "config.h"

using namespace std;
using namespace camellia;

int main() {
  defer(cout << 3 << endl);
  defer(cout << 2 << endl);
  defer(cout << 1 << endl);
  return 0;
}
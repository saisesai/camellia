#ifndef CAMELLIA_SORT_SEARCH_H
#define CAMELLIA_SORT_SEARCH_H

#include "config.h"

namespace camellia::sort {

// search uses binary search to find and return the smallest index i
// in [0, n) at which f(i) is true, assuming that on the range [0, n),
// f(i) == true implies f(i+1) == true. That is, Search requires that
// f is false for some (possibly empty) prefix of the input range [0, n)
// and then true for the (possibly empty) remainder; search returns
// the first true index. If there is no such index, search returns n.
// (Note that the "not found" return value is not -1 as in, for instance,
// strings.Index.)
// search calls f(i) only for i in the range [0, n).
int search(int p_n, const std::function<bool(int)>& p_f);

}  // namespace camellia::sort

#endif  // CAMELLIA_SORT_SEARCH_H

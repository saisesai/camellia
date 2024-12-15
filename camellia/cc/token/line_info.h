#ifndef LINE_INFO_H
#define LINE_INFO_H

#include "config.h"

namespace camellia::token {

// A line_info_t object describes alternative file, line, and column
// number information (such as provided via a //line directive)
// for a given file offset.
struct line_info_t {
  int offset;
  std::string filename;
  int line, column;
};

}  // namespace camellia::token

#endif  //LINE_INFO_H

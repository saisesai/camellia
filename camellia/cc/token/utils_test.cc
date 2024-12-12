#include "gtest/gtest.h"

#include "utils.h"

#include <string>
#include <vector>

using namespace std;
using namespace camellia::token;

TEST(token_utils_test, test_is_identifier) {
  struct test_t {
    string name;
    string in;
    bool want;
  };
  vector<test_t> tests = {
      {"Empty", "", false},
      {"Space", " ", false},
      {"SpaceSuffix", "foo ", false},
      {"Number", "123", false},
      {"Keyword", "proc", false},

      {"LettersASCII", "foo", true},
      {"MixedASCII", "_bar123", true},
      {"UppercaseKeyword", "Func", true},
  };
  for (const auto& [name, in, want] : tests) {
    bool got = utils::is_identifier(in);
    EXPECT_EQ(got, want) << "Test " << name << "Error!";
  }
}
#include "token.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
using namespace camellia::token;

TEST(token_test, test_is_identifier) {
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
    bool got = is_identifier(in);
    EXPECT_EQ(got, want) << "test " << name << " failed!";
  }
}
#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParsePid;

  const std::string normal =
      "1234 (test proc) S 1 1234 1234 0 -1 4194304 500 0 1 0 "
      "100 50 0 0 20 0 1 0 99999 8888888 1234";
  assert(ParsePid(normal) == 1234);
  std::printf("ParsePid normal case passed\n");

  const std::string parens =
      "42 (comm (with) parens) S 1 42 42 0 -1 0 0 0 10 20 0 0 20 0";
  assert(ParsePid(parens) == 42);
  std::printf("ParsePid with embedded parens passed\n");

  assert(ParsePid("") == -1);
  assert(ParsePid("noparen") == -1);
  assert(ParsePid("(nopid) S 1") == -1);
  std::printf("ParsePid invalid inputs return -1\n");

  assert(ParsePid("1 (a) S") == 1);
  assert(ParsePid("99999 (z) R 1 2 3") == 99999);
  std::printf("ParsePid boundary PIDs passed\n");

  assert(ParsePid("  123 (proc) S") == 123);
  assert(ParsePid("abc (proc) S") == -1);
  std::printf("ParsePid whitespace and non-numeric handling passed\n");

  assert(ParsePid("42junk (proc) S") == -1);
  assert(ParsePid("12 34 (proc) S") == -1);
  assert(ParsePid("2147483648 (proc) S") == -1);
  std::printf("ParsePid rejects partial and overflowing numeric fields\n");

  std::printf("All ParsePid tests passed.\n");
  return 0;
}

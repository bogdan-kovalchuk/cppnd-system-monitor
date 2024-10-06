#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseLong;

  assert(ParseLong("0") == 0);
  assert(ParseLong("1") == 1);
  assert(ParseLong("-1") == -1);
  assert(ParseLong("42") == 42);
  assert(ParseLong("99999") == 99999);
  assert(ParseLong("-100") == -100);
  std::printf("ParseLong valid inputs passed\n");

  assert(ParseLong("") == 0);
  assert(ParseLong("abc") == 0);
  assert(ParseLong("12abc") == 0);
  assert(ParseLong("  42") == 0);
  std::printf("ParseLong invalid inputs return fallback\n");

  assert(ParseLong("", 99) == 99);
  assert(ParseLong("abc", -1) == -1);
  assert(ParseLong("xyz", 42) == 42);
  std::printf("ParseLong custom fallback passed\n");

  assert(ParseLong("  42", 0) == 0);
  assert(ParseLong("42  ", 0) == 0);
  std::printf("ParseLong whitespace handling passed\n");

  std::printf("All ParseLong tests passed.\n");
  return 0;
}

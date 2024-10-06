#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseLong;

  assert(ParseLong("\t42") == 0);
  assert(ParseLong("\n42") == 0);
  assert(ParseLong("\r42") == 0);
  assert(ParseLong(" \t 42") == 0);
  std::printf("ParseLong rejects leading whitespace\n");

  assert(ParseLong("  42", -1) == -1);
  assert(ParseLong("\t100", -1) == -1);
  std::printf("ParseLong whitespace returns custom fallback\n");

  assert(ParseLong("+42") == 42);
  assert(ParseLong("-42") == -42);
  assert(ParseLong("+0") == 0);
  std::printf("ParseLong explicit sign prefix accepted\n");

  assert(ParseLong("0") == 0);
  assert(ParseLong("42") == 42);
  assert(ParseLong("-1") == -1);
  std::printf("ParseLong plain numeric inputs still work\n");

  assert(ParseLong("42abc") == 0);
  assert(ParseLong("12 34", -1) == -1);
  std::printf("ParseLong rejects trailing non-digit input\n");

  std::printf("All ParseLong strict whitespace tests passed.\n");
  return 0;
}

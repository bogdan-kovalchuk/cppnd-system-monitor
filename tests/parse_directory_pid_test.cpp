#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <limits>

int main() {
  using LinuxParser::ParseDirectoryPid;

  assert(ParseDirectoryPid("1") == 1);
  assert(ParseDirectoryPid("00042") == 42);
  assert(ParseDirectoryPid("0") == 0);
  std::printf("ParseDirectoryPid accepts numeric proc entry names\n");

  assert(ParseDirectoryPid("") == -1);
  assert(ParseDirectoryPid("self") == -1);
  assert(ParseDirectoryPid("12x") == -1);
  assert(ParseDirectoryPid("-2") == -1);
  assert(ParseDirectoryPid("2147483648") == -1);
  std::printf("ParseDirectoryPid rejects non-PID and overflowing names\n");

  return 0;
}

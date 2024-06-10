#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <limits>
#include <string>

int main() {
  using LinuxParser::ParseSystemUpTime;

  assert(ParseSystemUpTime("12345.67 98765.43") == 12345);
  std::printf("ParseSystemUpTime normal uptime passed\n");

  assert(ParseSystemUpTime("0.00 0.00") == 0);
  std::printf("ParseSystemUpTime zero uptime passed\n");

  assert(ParseSystemUpTime("86400.50 172800.25") == 86400);
  std::printf("ParseSystemUpTime truncates fractional seconds\n");

  assert(ParseSystemUpTime("") == 0);
  std::printf("ParseSystemUpTime empty content returns zero\n");

  assert(ParseSystemUpTime("abc def") == 0);
  std::printf("ParseSystemUpTime non-numeric content returns zero\n");

  assert(ParseSystemUpTime("1 2") == 1);
  std::printf("ParseSystemUpTime minimal integer values passed\n");

  assert(ParseSystemUpTime("999999.99 0.00") == 999999);
  std::printf("ParseSystemUpTime large value passed\n");

  assert(ParseSystemUpTime("-1.0 0.0") == 0);
  assert(ParseSystemUpTime("nan 0.0") == 0);
  assert(ParseSystemUpTime("inf 0.0") == 0);
  assert(ParseSystemUpTime(std::to_string(std::numeric_limits<long>::max()) +
                           "000 0.0") == 0);
  std::printf("ParseSystemUpTime rejects invalid and overflowing values\n");

  std::printf("All ParseSystemUpTime tests passed.\n");
  return 0;
}

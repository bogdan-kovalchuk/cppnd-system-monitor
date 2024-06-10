#include "linux_parser.h"

#include <cassert>
#include <cstdio>

int main() {
  using LinuxParser::ComputeProcessUpTime;

  assert(ComputeProcessUpTime(1000, 25000, 100) == 750);
  assert(ComputeProcessUpTime(1000, 25099, 100) == 750);
  assert(ComputeProcessUpTime(1000, 0, 100) == 1000);
  std::printf("ComputeProcessUpTime converts process start ticks\n");

  assert(ComputeProcessUpTime(100, 10100, 100) == 0);
  assert(ComputeProcessUpTime(-1, 0, 100) == 0);
  assert(ComputeProcessUpTime(1, -1, 100) == 0);
  assert(ComputeProcessUpTime(1, 0, 0) == 0);
  std::printf("ComputeProcessUpTime clamps unavailable process timing\n");

  return 0;
}

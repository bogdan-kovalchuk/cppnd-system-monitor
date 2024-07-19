#include "format.h"

#include <cassert>
#include <cstdio>
#include <limits>

int main() {
  assert(Format::Percent(0.0f) == "0.0");
  assert(Format::Percent(0.125f) == "12.5");
  assert(Format::Percent(0.999f) == "99.9");
  assert(Format::Percent(1.0f) == "100.0");
  std::printf("Percent formats bounded ratios predictably\n");

  assert(Format::Percent(-0.5f) == "0.0");
  assert(Format::Percent(1.5f) == "100.0");
  assert(Format::Percent(std::numeric_limits<float>::quiet_NaN()) == "0.0");
  std::printf("Percent clamps invalid display ratios\n");

  return 0;
}

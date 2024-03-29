#include "linux_parser.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseMemoryUtilization;

  const std::string normal =
      "MemTotal:       16384000 kB\n"
      "MemFree:         8192000 kB\n"
      "MemAvailable:   12288000 kB\n";
  float r = ParseMemoryUtilization(normal);
  float expected = (16384000.0f - 12288000.0f) / 16384000.0f;
  assert(std::fabs(r - expected) < 0.001f);
  std::printf("ParseMemoryUtilization normal case = %.4f\n", r);

  const std::string full =
      "MemTotal:       16384000 kB\n"
      "MemAvailable:   16384000 kB\n";
  assert(ParseMemoryUtilization(full) == 0.0f);
  std::printf("ParseMemoryUtilization fully available returns zero\n");

  const std::string empty_used =
      "MemTotal:       16384000 kB\n"
      "MemAvailable:          0 kB\n";
  assert(std::fabs(ParseMemoryUtilization(empty_used) - 1.0f) < 0.001f);
  std::printf("ParseMemoryUtilization zero available returns 1.0\n");

  assert(ParseMemoryUtilization("") == 0.0f);
  std::printf("ParseMemoryUtilization empty content returns zero\n");

  const std::string no_total =
      "MemFree:    8000 kB\n"
      "MemAvailable: 4000 kB\n";
  assert(ParseMemoryUtilization(no_total) == 0.0f);
  std::printf("ParseMemoryUtilization missing MemTotal returns zero\n");

  const std::string zero_total =
      "MemTotal:            0 kB\n"
      "MemAvailable:        0 kB\n";
  assert(ParseMemoryUtilization(zero_total) == 0.0f);
  std::printf("ParseMemoryUtilization zero MemTotal returns zero\n");

  const std::string no_available =
      "MemTotal: 16384000 kB\n"
      "MemFree: 4096000 kB\n"
      "Buffers: 1024000 kB\n"
      "Cached: 3072000 kB\n";
  assert(std::fabs(ParseMemoryUtilization(no_available) - 0.5f) < 0.001f);
  std::printf("ParseMemoryUtilization estimates availability without MemAvailable\n");

  const std::string malformed =
      "MemTotal: unknown kB\n"
      "MemAvailable: 1000 kB\n";
  assert(ParseMemoryUtilization(malformed) == 0.0f);

  const std::string impossible =
      "MemTotal: 1000 kB\n"
      "MemAvailable: 1001 kB\n";
  assert(ParseMemoryUtilization(impossible) == 0.0f);
  std::printf("ParseMemoryUtilization rejects incomplete or malformed data\n");

  std::printf("All ParseMemoryUtilization tests passed.\n");
  return 0;
}

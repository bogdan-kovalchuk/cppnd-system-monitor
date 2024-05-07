#include "linux_parser.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <limits>
#include <string>
#include <vector>
#include <unistd.h>

int main() {
  using LinuxParser::ComputeCpuUtilization;

  const long clk_tck = sysconf(_SC_CLK_TCK);

  assert(ComputeCpuUtilization({}) == 0.0f);
  assert(ComputeCpuUtilization({"100", "10"}) == 0.0f);
  assert(ComputeCpuUtilization({"100", "10", "5", "2", "1"}) == 0.0f);
  std::printf("ComputeCpuUtilization short data returns zero\n");

  {
    long uptime = 1000;
    long starttime = 100 * clk_tck;
    long seconds = uptime - 100;
    float total_s = 70.0f / (float)clk_tck;
    float expected = total_s / (float)seconds;
    std::vector<std::string> data = {"1000", "50", "10", "5", "5",
                                     std::to_string(starttime)};
    float result = ComputeCpuUtilization(data);
    assert(std::fabs(result - expected) < 0.001f);
    std::printf("ComputeCpuUtilization normal case passed (%.6f)\n", result);
  }

  {
    long starttime = 100 * clk_tck;
    std::vector<std::string> data = {"100", "50", "10", "5", "5",
                                     std::to_string(starttime)};
    float result = ComputeCpuUtilization(data);
    assert(result == 0.0f);
    assert(!std::isnan(result));
    assert(!std::isinf(result));
    std::printf("ComputeCpuUtilization zero-lifetime returns zero\n");
  }

  {
    long starttime = 200 * clk_tck;
    std::vector<std::string> data = {"100", "50", "10", "5", "5",
                                     std::to_string(starttime)};
    float result = ComputeCpuUtilization(data);
    assert(result == 0.0f);
    assert(!std::isnan(result));
    assert(!std::isinf(result));
    std::printf("ComputeCpuUtilization negative-lifetime returns zero\n");
  }

  {
    std::vector<std::string> data = {"abc", "50", "10", "5", "5", "1000"};
    float result = ComputeCpuUtilization(data);
    assert(result == 0.0f);
    std::printf("ComputeCpuUtilization non-numeric uptime returns zero\n");
  }

  {
    float expected = 0.0f;
    std::vector<std::string> data = {"5000", "0", "0", "0", "0", "0"};
    float result = ComputeCpuUtilization(data);
    assert(result == expected);
    std::printf("ComputeCpuUtilization zero total-time passed (%.6f)\n", result);
  }

  {
    const std::vector<std::string> data = {"1000", "-1", "10", "0", "0", "0"};
    assert(ComputeCpuUtilization(data) == 0.0f);
    std::printf("ComputeCpuUtilization rejects negative tick counts\n");
  }

  {
    const auto largest = std::to_string(std::numeric_limits<long>::max());
    const std::vector<std::string> data =
        {"1000", largest, largest, largest, largest, "0"};
    assert(ComputeCpuUtilization(data) == 0.0f);
    std::printf("ComputeCpuUtilization rejects overflowing accumulated ticks\n");
  }

  std::printf("All ComputeCpuUtilization tests passed.\n");
  return 0;
}

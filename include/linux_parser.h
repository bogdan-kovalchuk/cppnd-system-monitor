#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <cstdint>
#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {

// Proc filesystem parser approach:
// - Stream-based functions read /proc files line-by-line using istringstream.
//   Time complexity: O(n) where n is file size. Space: O(1) per call.
// - String-based helpers (ParseStatField, ParseStatusValue) operate on
//   pre-loaded content, enabling unit testing with synthetic data.
//   ParseStatField: O(f) where f is field index (scans tokens after comm).
//   ParseStatusValue: O(k) where k is content size (linear search for key).
// Both approaches handle malformed input gracefully with fallback values.

// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
std::vector<std::string> CpuUtilization();
std::vector<std::string> CpuUtilization(int pid);

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long UpTime(int pid);

std::string ParseStatField(const std::string& stat_line, int field_index);
std::string ParseStatusValue(const std::string& status_content,
                             const std::string& key);
long ParseLong(const std::string& s, long fallback = 0);
std::string ParseCmdline(const std::string& raw_cmdline);
std::string ParseMeminfoValue(const std::string& meminfo_content,
                              const std::string& key);
int ParsePid(const std::string& stat_line);
int ParseDirectoryPid(const std::string& directory_name);
std::string ParseRamMb(const std::string& ram_kb);
std::string ParseUid(const std::string& status_content);
std::string ParseKernel(const std::string& version_line);
std::string ParseOperatingSystem(const std::string& os_release_content);
float ParseMemoryUtilization(const std::string& meminfo_content);
std::string ParseUser(const std::string& passwd_content, const std::string& uid);
long ParseSystemUpTime(const std::string& uptime_content);
int ParseStatProcesses(const std::string& stat_content, const std::string& key);
float ComputeCpuUtilization(const std::vector<std::string>& cpu_data);
float ComputeProcessorUtilization(std::uint64_t user, std::uint64_t nice,
                                  std::uint64_t system, std::uint64_t idle,
                                  std::uint64_t iowait, std::uint64_t irq,
                                  std::uint64_t softirq, std::uint64_t steal,
                                  std::uint64_t prev_user,
                                  std::uint64_t prev_nice,
                                  std::uint64_t prev_system,
                                  std::uint64_t prev_idle,
                                  std::uint64_t prev_iowait,
                                  std::uint64_t prev_irq,
                                  std::uint64_t prev_softirq,
                                  std::uint64_t prev_steal,
                                  bool first_call);
};  // namespace LinuxParser

#endif

#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

namespace {
bool ParseUnsignedStrict(const string& value, std::uint64_t& result) {
  if (value.empty()) return false;
  const char* begin = value.data();
  const char* end = begin + value.size();
  const auto parsed = std::from_chars(begin, end, result);
  return parsed.ec == std::errc{} && parsed.ptr == end;
}

bool AddWithoutOverflow(std::uint64_t value, std::uint64_t& total) {
  if (value > std::numeric_limits<std::uint64_t>::max() - total) return false;
  total += value;
  return true;
}

int NumberOfProcesses(string skey) {
  std::ifstream stream(LinuxParser::kProcDirectory +
                       LinuxParser::kStatFilename);
  if (stream.is_open()) {
    string content((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return LinuxParser::ParseStatProcesses(content, skey);
  }
  return 0;
}
}  // namespace

string LinuxParser::OperatingSystem() {
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    string content((std::istreambuf_iterator<char>(filestream)),
                    std::istreambuf_iterator<char>());
    return ParseOperatingSystem(content);
  }
  return "";
}

string LinuxParser::Kernel() {
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    return ParseKernel(line);
  }
  return "";
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  if (directory == nullptr) return pids;
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    const int pid = ParseDirectoryPid(file->d_name);
    if (pid >= 0) pids.push_back(pid);
  }
  closedir(directory);
  std::sort(pids.begin(), pids.end());
  return pids;
}

float LinuxParser::MemoryUtilization() {
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    string content((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return ParseMemoryUtilization(content);
  }
  return 0.0f;
}

long LinuxParser::UpTime() {
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    string content((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return ParseSystemUpTime(content);
  }
  return 0;
}

vector<string> LinuxParser::CpuUtilization() {
  vector<string> stat_cpu;
  string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
        while (linestream >> value) {
          stat_cpu.push_back(value);
        }
        break;
      }
    }
  }
  return stat_cpu;
}

int LinuxParser::TotalProcesses() { return NumberOfProcesses("processes"); }

int LinuxParser::RunningProcesses() {
  return NumberOfProcesses("procs_running");
}

string LinuxParser::Command(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    string raw((std::istreambuf_iterator<char>(stream)),
                std::istreambuf_iterator<char>());
    return ParseCmdline(raw);
  }
  return "";
}

vector<string> LinuxParser::CpuUtilization(int pid) {
  vector<string> output;
  string value, seconds, line;
  std::ifstream stream_uptime(kProcDirectory + kUptimeFilename);
  if (stream_uptime.is_open()) {
    std::getline(stream_uptime, line);
    std::istringstream linestream(line);
    linestream >> seconds;
    output.push_back(seconds);
  }
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    for (int idx : {14, 15, 16, 17, 22}) {
      output.push_back(ParseStatField(line, idx));
    }
  }
  return output;
}

string LinuxParser::Ram(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    string content((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    string val = ParseStatusValue(content, "VmSize");
    if (!val.empty()) {
      bool numeric = std::all_of(val.begin(), val.end(), ::isdigit);
      return numeric ? val : "0";
    }
  }
  return "0";
}

string LinuxParser::Uid(int pid) {
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    string content((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return ParseUid(content);
  }
  return "";
}

string LinuxParser::User(int pid) {
  string uid = Uid(pid);
  if (uid.empty()) return "";
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    string content((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return ParseUser(content, uid);
  }
  return "";
}

long LinuxParser::UpTime(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    string field22 = ParseStatField(line, 22);
    if (!field22.empty()) {
      return ParseLong(field22, 0);
    }
  }
  return 0;
}

string LinuxParser::ParseStatField(const string& stat_line, int field_index) {
  if (field_index < 1) return "";
  if (field_index == 1) {
    auto pos = stat_line.find('(');
    if (pos == string::npos) return "";
    string pid_str = stat_line.substr(0, pos);
    while (!pid_str.empty() && std::isspace(pid_str.back())) pid_str.pop_back();
    return pid_str;
  }
  if (field_index == 2) {
    auto open = stat_line.find('(');
    auto close = stat_line.rfind(')');
    if (open == string::npos || close == string::npos || close <= open)
      return "";
    return stat_line.substr(open + 1, close - open - 1);
  }
  auto close = stat_line.rfind(')');
  if (close == string::npos || close + 1 >= stat_line.size() ||
      !std::isspace(static_cast<unsigned char>(stat_line[close + 1]))) {
    return "";
  }
  string tail = stat_line.substr(close + 1);
  std::istringstream iss(tail);
  string token;
  int current = 3;
  while (iss >> token) {
    if (current == field_index) return token;
    ++current;
  }
  return "";
}

string LinuxParser::ParseStatusValue(const string& status_content,
                                     const string& key) {
  string search_key = key + ":";
  std::istringstream stream(status_content);
  string line;
  while (std::getline(stream, line)) {
    if (line.find(search_key) == 0) {
      std::istringstream iss(line);
      string k, val;
      iss >> k;
      iss >> val;
      return val;
    }
  }
  return "";
}

long LinuxParser::ParseLong(const string& s, long fallback) {
  if (s.empty()) return fallback;
  char first = s.front();
  if (!std::isdigit(static_cast<unsigned char>(first)) && first != '-' && first != '+')
    return fallback;
  try {
    size_t pos = 0;
    long val = std::stol(s, &pos);
    if (pos != s.size()) return fallback;
    return val;
  } catch (const std::exception&) {
    return fallback;
  }
}

string LinuxParser::ParseCmdline(const string& raw_cmdline) {
  string result = raw_cmdline;
  std::replace(result.begin(), result.end(), '\0', ' ');
  while (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

string LinuxParser::ParseMeminfoValue(const string& meminfo_content,
                                      const string& key) {
  std::istringstream stream(meminfo_content);
  string line;
  while (std::getline(stream, line)) {
    const auto separator = line.find(':');
    if (separator == string::npos) continue;

    string parsed_key = line.substr(0, separator);
    const auto key_begin = parsed_key.find_first_not_of(" \t");
    const auto key_end = parsed_key.find_last_not_of(" \t");
    if (key_begin == string::npos) continue;
    parsed_key = parsed_key.substr(key_begin, key_end - key_begin + 1);
    if (parsed_key != key) continue;

    std::istringstream value_stream(line.substr(separator + 1));
    string value;
    value_stream >> value;
    return value;
  }
  return "";
}

int LinuxParser::ParsePid(const string& stat_line) {
  auto pos = stat_line.find('(');
  if (pos == string::npos || pos == 0) return -1;
  string pid_str = stat_line.substr(0, pos);
  while (!pid_str.empty() && std::isspace(pid_str.back())) pid_str.pop_back();
  const auto first = pid_str.find_first_not_of(" \t");
  if (first == string::npos) return -1;
  return ParseDirectoryPid(pid_str.substr(first));
}

string LinuxParser::ParseRamMb(const string& ram_kb) {
  long val = ParseLong(ram_kb, 0);
  if (val < 0) val = 0;
  long mb = val / 1024;
  if (val % 1024 >= 512) ++mb;
  return to_string(mb);
}

string LinuxParser::ParseUid(const string& status_content) {
  return ParseStatusValue(status_content, "Uid");
}

string LinuxParser::ParseKernel(const string& version_line) {
  std::istringstream iss(version_line);
  string os, version, kernel;
  if (!(iss >> os >> version)) return "";
  if (!(iss >> kernel)) return "";
  return kernel;
}

string LinuxParser::ParseOperatingSystem(const string& os_release_content) {
  std::istringstream stream(os_release_content);
  string line;
  while (std::getline(stream, line)) {
    const auto separator = line.find('=');
    if (separator == string::npos) continue;
    const auto key_begin = line.find_first_not_of(" \t");
    const auto key_end = line.find_last_not_of(" \t", separator - 1);
    if (key_begin == string::npos || key_end == string::npos ||
        line.substr(key_begin, key_end - key_begin + 1) != "PRETTY_NAME") {
      continue;
    }
    const auto value_begin = line.find_first_not_of(" \t", separator + 1);
    if (value_begin == string::npos) return "";
    const auto value_end = line.find_last_not_of(" \t");
    string value = line.substr(value_begin, value_end - value_begin + 1);
    if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
      value = value.substr(1, value.size() - 2);
    }
    return value;
  }
  return "";
}

float LinuxParser::ParseMemoryUtilization(const string& meminfo_content) {
  std::uint64_t total_memory = 0;
  std::uint64_t available_memory = 0;
  if (!ParseUnsignedStrict(ParseMeminfoValue(meminfo_content, "MemTotal"),
                           total_memory) ||
      total_memory == 0) {
    return 0.0f;
  }

  const string reported_available =
      ParseMeminfoValue(meminfo_content, "MemAvailable");
  if (!reported_available.empty()) {
    if (!ParseUnsignedStrict(reported_available, available_memory)) return 0.0f;
  } else {
    if (!ParseUnsignedStrict(ParseMeminfoValue(meminfo_content, "MemFree"),
                             available_memory)) {
      return 0.0f;
    }
    for (const char* key : {"Buffers", "Cached"}) {
      const string value = ParseMeminfoValue(meminfo_content, key);
      if (value.empty()) continue;
      std::uint64_t parsed = 0;
      if (!ParseUnsignedStrict(value, parsed) ||
          !AddWithoutOverflow(parsed, available_memory)) {
        return 0.0f;
      }
    }
  }
  if (available_memory > total_memory) return 0.0f;
  return static_cast<float>(
      static_cast<long double>(total_memory - available_memory) /
      static_cast<long double>(total_memory));
}

string LinuxParser::ParseUser(const string& passwd_content, const string& uid) {
  if (uid.empty()) return "";
  std::istringstream stream(passwd_content);
  string line;
  while (std::getline(stream, line)) {
    const auto password_separator = line.find(':');
    if (password_separator == string::npos || password_separator == 0) continue;
    const auto uid_separator = line.find(':', password_separator + 1);
    if (uid_separator == string::npos) continue;
    const auto group_separator = line.find(':', uid_separator + 1);
    if (group_separator == string::npos) continue;
    if (line.substr(uid_separator + 1,
                    group_separator - uid_separator - 1) == uid) {
      return line.substr(0, password_separator);
    }
  }
  return "";
}

long LinuxParser::ParseSystemUpTime(const string& uptime_content) {
  std::istringstream iss(uptime_content);
  long double uptime = 0.0;
  iss >> uptime;
  if (iss.fail() || !std::isfinite(uptime) || uptime < 0.0 ||
      uptime > static_cast<long double>(std::numeric_limits<long>::max())) {
    return 0;
  }
  return static_cast<long>(uptime);
}

long LinuxParser::ComputeProcessUpTime(long system_uptime, long start_ticks,
                                       long clock_ticks) {
  if (system_uptime < 0 || start_ticks < 0 || clock_ticks <= 0) return 0;
  const long start_seconds = start_ticks / clock_ticks;
  if (start_seconds > system_uptime) return 0;
  return system_uptime - start_seconds;
}

int LinuxParser::ParseStatProcesses(const string& stat_content, const string& key) {
  std::istringstream stream(stat_content);
  string line;
  while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    string k, val;
    linestream >> k >> val;
    if (k == key) {
      std::uint64_t parsed = 0;
      if (!ParseUnsignedStrict(val, parsed) ||
          parsed > static_cast<std::uint64_t>(std::numeric_limits<int>::max())) {
        return 0;
      }
      return static_cast<int>(parsed);
    }
  }
  return 0;
}

float LinuxParser::ComputeCpuUtilization(const vector<string>& data) {
  if (data.size() < 6) return 0.0f;
  long uptime = ParseLong(data[0], 0);
  long utime = ParseLong(data[1], 0);
  long stime = ParseLong(data[2], 0);
  long cutime = ParseLong(data[3], 0);
  long cstime = ParseLong(data[4], 0);
  long starttime = ParseLong(data[5], 0);
  if (uptime < 0 || utime < 0 || stime < 0 || cutime < 0 || cstime < 0 ||
      starttime < 0) {
    return 0.0f;
  }
  std::uint64_t total_time = 0;
  for (long value : {utime, stime, cutime, cstime}) {
    if (!AddWithoutOverflow(static_cast<std::uint64_t>(value), total_time)) {
      return 0.0f;
    }
  }
  long clk_tck = sysconf(_SC_CLK_TCK);
  if (clk_tck <= 0) return 0.0f;
  long seconds = uptime - (starttime / clk_tck);
  if (seconds <= 0) return 0.0f;
  return static_cast<float>(static_cast<long double>(total_time) /
                            static_cast<long double>(clk_tck) /
                            static_cast<long double>(seconds));
}

float LinuxParser::ComputeProcessorUtilization(
    std::uint64_t user, std::uint64_t nice, std::uint64_t system,
    std::uint64_t idle, std::uint64_t iowait, std::uint64_t irq,
    std::uint64_t softirq, std::uint64_t steal, std::uint64_t prev_user,
    std::uint64_t prev_nice, std::uint64_t prev_system,
    std::uint64_t prev_idle, std::uint64_t prev_iowait,
    std::uint64_t prev_irq, std::uint64_t prev_softirq,
    std::uint64_t prev_steal, bool first_call) {
  if (first_call) return 0.0f;

  const std::array<std::uint64_t, 8> current{
      user, nice, system, idle, iowait, irq, softirq, steal};
  const std::array<std::uint64_t, 8> previous{
      prev_user, prev_nice, prev_system, prev_idle,
      prev_iowait, prev_irq, prev_softirq, prev_steal};
  std::uint64_t busy_delta = 0;
  std::uint64_t idle_delta = 0;
  for (std::size_t index = 0; index < current.size(); ++index) {
    if (current[index] < previous[index]) return 0.0f;
    const std::uint64_t delta = current[index] - previous[index];
    std::uint64_t& bucket = (index == 3 || index == 4) ? idle_delta : busy_delta;
    if (!AddWithoutOverflow(delta, bucket)) return 0.0f;
  }
  std::uint64_t total_delta = busy_delta;
  if (!AddWithoutOverflow(idle_delta, total_delta) || total_delta == 0) {
    return 0.0f;
  }
  return static_cast<float>(static_cast<long double>(busy_delta) /
                            static_cast<long double>(total_delta));
}

int LinuxParser::ParseDirectoryPid(const string& directory_name) {
  if (directory_name.empty()) return -1;
  int pid = 0;
  const char* begin = directory_name.data();
  const char* end = begin + directory_name.size();
  const auto parsed = std::from_chars(begin, end, pid);
  if (parsed.ec != std::errc{} || parsed.ptr != end || pid < 0) return -1;
  return pid;
}

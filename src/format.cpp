#include "format.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

using std::string;
using std::to_string;

namespace {
void add_zero(string& s) {
  if (s.length() < 2) {
    s = "0" + s;
  }
}
}  // namespace

string Format::ElapsedTime(long seconds) {
  if (seconds < 0) seconds = 0;
  string h = to_string((seconds / 3600) % 100);  // goes to 0 after 99
  string m = to_string((seconds / 60) % 60);
  string s = to_string(seconds % 60);

  add_zero(h);
  add_zero(m);
  add_zero(s);

  return h + ":" + m + ":" + s;
}

string Format::ElapsedTimeDiv(long seconds) {
  if (seconds < 0) seconds = 0;
  char buf[16];
  long h = (seconds / 3600) % 100;
  ldiv_t rm = ldiv(seconds % 3600, 60);
  std::snprintf(buf, sizeof(buf), "%02ld:%02ld:%02ld", h, rm.quot, rm.rem);
  return buf;
}

string Format::Percent(float ratio) {
  if (!std::isfinite(ratio) || ratio < 0.0f) ratio = 0.0f;
  if (ratio > 1.0f) ratio = 1.0f;
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(1) << ratio * 100.0f;
  return stream.str();
}

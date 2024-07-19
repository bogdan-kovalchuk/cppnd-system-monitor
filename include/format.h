#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);
std::string ElapsedTimeDiv(long seconds);
std::string Percent(float ratio);
};  // namespace Format

#endif

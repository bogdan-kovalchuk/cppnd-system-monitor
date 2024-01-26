#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseStatField;
  using LinuxParser::ParseStatusValue;

  assert(ParseStatField("", 1).empty());
  assert(ParseStatField("", 22).empty());
  assert(ParseStatField("invalid", 1).empty());
  assert(ParseStatField("1234", 1).empty());
  assert(ParseStatField("1234 (proc)", 1) == "1234");
  assert(ParseStatField("1234 (proc)", 2) == "proc");
  assert(ParseStatField("1234 (proc) S", 3) == "S");
  assert(ParseStatField("1234 (proc) S", 4).empty());
  assert(ParseStatField("1234 (proc) S 1 2 3", 6) == "3");
  assert(ParseStatField("1234 (proc) S", -1).empty());
  assert(ParseStatField("1234 (proc) S", 0).empty());
  assert(ParseStatField("1234 (proc) S", 100).empty());
  std::printf("ParseStatField boundary tests passed\n");

  assert(ParseStatField("1234 () S 1", 2).empty());
  assert(ParseStatField("1234 (a(b)c) S 1", 2) == "a(b)c");
  assert(ParseStatField("1234 (proc) S", 3) == "S");
  assert(ParseStatField("1234 (proc)", 3).empty());
  assert(ParseStatField("1234 (proc)S 1", 3).empty());
  assert(ParseStatField("1234 (proc)\tS 1", 3) == "S");
  std::printf("ParseStatField validates separator after command name\n");
  std::printf("ParseStatField edge cases passed\n");

  assert(ParseStatusValue("", "Name").empty());
  assert(ParseStatusValue("Name:\ttest\n", "Name") == "test");
  assert(ParseStatusValue("Name:\ttest\n", "Missing").empty());
  assert(ParseStatusValue("Name:\ttest\n", "name").empty());
  assert(ParseStatusValue("Name:\n", "Name").empty());
  assert(ParseStatusValue("Name:\t  \n", "Name").empty());
  assert(ParseStatusValue("Name:\tval1\tval2\n", "Name") == "val1");
  std::printf("ParseStatusValue boundary tests passed\n");

  const std::string multiline =
      "Name:\tproc1\n"
      "State:\tS\n"
      "Uid:\t1000\n";
  assert(ParseStatusValue(multiline, "Name") == "proc1");
  assert(ParseStatusValue(multiline, "State") == "S");
  assert(ParseStatusValue(multiline, "Uid") == "1000");
  assert(ParseStatusValue(multiline, "Pid").empty());
  std::printf("ParseStatusValue multiline tests passed\n");

  std::printf("All invalid/boundary input tests passed.\n");
  return 0;
}

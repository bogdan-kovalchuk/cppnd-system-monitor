#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseOperatingSystem;

  const std::string ubuntu =
      "NAME=\"Ubuntu\"\n"
      "VERSION=\"22.04.3 LTS (Jammy Jellyfish)\"\n"
      "PRETTY_NAME=\"Ubuntu 22.04.3 LTS\"\n"
      "ID=ubuntu\n";
  assert(ParseOperatingSystem(ubuntu) == "Ubuntu 22.04.3 LTS");
  std::printf("ParseOperatingSystem Ubuntu passed\n");

  const std::string fedora =
      "NAME=Fedora\n"
      "VERSION=\"38 (Workstation Edition)\"\n"
      "PRETTY_NAME=\"Fedora 38 (Workstation Edition)\"\n"
      "ID=fedora\n";
  assert(ParseOperatingSystem(fedora) == "Fedora 38 (Workstation Edition)");
  std::printf("ParseOperatingSystem Fedora passed\n");

  assert(ParseOperatingSystem("").empty());
  std::printf("ParseOperatingSystem empty content returns empty\n");

  const std::string no_pretty =
      "NAME=Arch\n"
      "ID=arch\n";
  assert(ParseOperatingSystem(no_pretty).empty());
  std::printf("ParseOperatingSystem missing PRETTY_NAME returns empty\n");

  const std::string single_word =
      "PRETTY_NAME=Alpine\n";
  assert(ParseOperatingSystem(single_word) == "Alpine");
  std::printf("ParseOperatingSystem single-word name passed\n");

  const std::string unquoted =
      "PRETTY_NAME=\"Debian GNU/Linux 12 (bookworm)\"\n";
  assert(ParseOperatingSystem(unquoted) == "Debian GNU/Linux 12 (bookworm)");
  std::printf("ParseOperatingSystem multi-word with special chars passed\n");

  const std::string padded =
      "NAME=Example\n"
      "  PRETTY_NAME \t=\t \"Example OS Server\"   \n";
  assert(ParseOperatingSystem(padded) == "Example OS Server");
  assert(ParseOperatingSystem("PRETTY_NAME=\n").empty());
  std::printf("ParseOperatingSystem accepts spaced assignments\n");

  std::printf("All ParseOperatingSystem tests passed.\n");
  return 0;
}

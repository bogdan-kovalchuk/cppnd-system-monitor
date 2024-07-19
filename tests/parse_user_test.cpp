#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseUser;

  const std::string passwd =
      "root:x:0:0:root:/root:/bin/bash\n"
      "daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin\n"
      "bogdan:x:1000:1000:Bogdan:/home/bogdan:/bin/bash\n"
      "nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin\n";

  assert(ParseUser(passwd, "0") == "root");
  assert(ParseUser(passwd, "1") == "daemon");
  assert(ParseUser(passwd, "1000") == "bogdan");
  assert(ParseUser(passwd, "65534") == "nobody");
  std::printf("ParseUser standard passwd entries passed\n");

  assert(ParseUser("exact:x:42:43:Exact:/home/exact:/bin/sh\n", "42") ==
         "exact");
  assert(ParseUser("exact:x:42:43:Exact:/home/exact:/bin/sh\n", "43").empty());
  std::printf("ParseUser matches the UID field rather than the group field\n");

  assert(ParseUser(passwd, "9999").empty());
  assert(ParseUser(passwd, "").empty());
  std::printf("ParseUser unknown uid returns empty\n");

  assert(ParseUser("", "0").empty());
  std::printf("ParseUser empty passwd returns empty\n");

  const std::string single = "testuser:x:500:500:Test:/home/test:/bin/sh\n";
  assert(ParseUser(single, "500") == "testuser");
  assert(ParseUser(single, "0").empty());
  std::printf("ParseUser single entry passed\n");

  const std::string with_colons =
      "user1:x:100:100:User One,Room1,555-1234:/home/user1:/bin/bash\n"
      "user2:x:200:200:User Two:/home/user2:/bin/sh\n";
  assert(ParseUser(with_colons, "100") == "user1");
  assert(ParseUser(with_colons, "200") == "user2");
  std::printf("ParseUser with GECOS fields passed\n");

  const std::string malformed =
      "truncated:x:300\n"
      ":x:400:400:Missing name:/home/missing:/bin/sh\n"
      "valid:x:500:500:Valid:/home/valid:/bin/sh\n";
  assert(ParseUser(malformed, "300").empty());
  assert(ParseUser(malformed, "400").empty());
  assert(ParseUser(malformed, "500") == "valid");
  std::printf("ParseUser ignores incomplete passwd entries\n");

  std::printf("All ParseUser tests passed.\n");
  return 0;
}

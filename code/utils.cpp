#include "include/utils.hpp"

bool isHex(char c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
         (c >= 'A' && c <= 'F');
}

bool isMac(const std::string& mac) {
  if (mac.size() != 17) {
    return false;
  }

  for (int i = 0; i < 17; i++) {
    if (i % 3 == 2) {
      if (mac[i] != ':') {
        return false;
      }
    } else {
      if (!isHex(mac[i])) {
        return false;
      }
    }
  }

  return true;
}

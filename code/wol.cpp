#include "include/wol.hpp"

#include <cstdlib>
#include <iostream>

#include "include/database.hpp"

void wakeDevice(const std::string& name) {
  auto database = loadDatabase();
  for (const auto& entry : database) {
    std::string deviceName = entry.second.substr(0, entry.second.find(';'));
    std::string mac = entry.second.substr(entry.second.find(';') + 1);
    if (deviceName == name) {
      std::string command = "wakeonlan " + mac;
      std::cout << "Waking up " << name << " (" << mac << ")..." << std::endl;
      system(command.c_str());
      return;
    }
  }
}
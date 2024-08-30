#include "include/wol.hpp"

#include <cstdlib>
#include <iostream>

#include "include/database.hpp"

void wakeDevice(const std::string& name) {
  auto database = loadDatabase();
  if (database.find(name) != database.end()) {
    std::string command = "wakeonlan " + database[name];
    std::system(command.c_str());
  } else {
    std::cout << "The device " << name << " is not in the database"
              << std::endl;
  }
}

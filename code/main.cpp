#include <iostream>
#include <string>

#include "include/database.hpp"
#include "include/utils.hpp"
#include "include/wol.hpp"

void help() {
  std::cout << "Usage: wake <command> [arguments...]" << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  <name>              Wake a device" << std::endl;
  std::cout << "  add <name> <mac>    Add a device to the database"
            << std::endl;
  std::cout << "  remove <name>       Remove a device from the database"
            << std::endl;
  std::cout << "  list                List the devices in the database"
            << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    help();
    return 1;
  }

  std::string command = argv[1];
  if (command == "add") {
    if (argc < 4) {
      std::cout << "Usage: " << argv[0] << " add <name> <mac>" << std::endl;
      help();
      return 1;
    }
    addDevice(argv[2], argv[3]);
  } else if (command == "remove") {
    if (argc < 3) {
      std::cout << "Usage: " << argv[0] << " remove <name>" << std::endl;
      help();
      return 1;
    }
    removeDevice(argv[2]);
  } else if (command == "list") {
    listDevices();
  } else {
    wakeDevice(argv[1]);
  }

  return 0;
}

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// Path to the database file
const std::string DB_PATH = "/etc/wol/database.json";
// const std::string DB_PATH = "/home/sgonsan/Proyects/wake/code/database.json";

// Help function
void help() {
  std::cout << "Usage: wake <command> [arguments...]" << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  add <name> <mac>    Add a device to the database"
            << std::endl;
  std::cout << "  remove <name>       Remove a device from the database"
            << std::endl;
  std::cout << "  <name>              Wake a device" << std::endl;
}

// Function to load the database
std::map<std::string, std::string> loadDatabase() {
  std::map<std::string, std::string> database;

  if (std::ifstream(DB_PATH).good() == false) {
    std::ofstream file(DB_PATH);
    file << "{}";
  }

  std::ifstream file(DB_PATH);

  if (file.is_open()) {
    json root;
    file >> root;
    for (const auto& key : root.items()) {
      database[key.key()] = key.value();
    }
  }

  return database;
}

// Function to save the database
void saveDatabase(const std::map<std::string, std::string>& database) {
  json root;
  for (const auto& entry : database) {
    root[entry.first] = entry.second;
  }

  std::ofstream file(DB_PATH);
  file << root;
}

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

// Function to add a device to the database
void addDevice(const std::string& name, const std::string& mac) {
  if (!isMac(mac)) {
    std::cout << "The MAC address " << mac << " is not valid" << std::endl;
    return;
  }
  auto database = loadDatabase();
  for (const auto& entry : database) {
    if (entry.first == name || entry.second == mac) {
      std::cout << "The device " << name << " (" << mac
                << ") is already in the database" << std::endl;
      return;
    }
  }
  database[name] = mac;
  saveDatabase(database);
  std::cout << "The device " << name << " (" << mac
            << ") has been added to the database" << std::endl;
}

// Function to remove a device from the database
void removeDevice(const std::string& name) {
  auto database = loadDatabase();
  if (database.find(name) != database.end()) {
    std::cout << "Do you want to remove the device " << name << " ("
              << database[name] << ") from the database? [y/N] ";
    std::string answer;
    std::getline(std::cin, answer);
    if (answer != "y" && answer != "Y") {
      return;
    }
    database.erase(name);
    saveDatabase(database);
    std::cout << "The device " << name << " has been removed from the database"
              << std::endl;
  } else {
    std::cout << "The device " << name << " is not in the database"
              << std::endl;
  }
}

// Function to list the devices in the database
void listDevices() {
  auto database = loadDatabase();
  if (database.empty()) {
    std::cout << "The database is empty" << std::endl;
  } else {
    std::cout << "Devices in the database:" << std::endl;
    for (const auto& entry : database) {
      std::cout << "  " << entry.first << " (" << entry.second << ")"
                << std::endl;
    }
  }
}

// Function to send a wake-on-lan packet
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

// Main function
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
    if (argc < 2) {
      std::cout << "Usage: " << argv[0] << " list" << std::endl;
      help();
      return 1;
    }

    listDevices();

  } else {
    wakeDevice(argv[1]);
  }

  return 0;
}
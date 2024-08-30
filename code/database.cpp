#include "include/database.hpp"

#include <fstream>
#include <iostream>

#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

const std::string DB_PATH = "/etc/wol/database.json";

std::map<std::string, std::string> loadDatabase() {
  std::map<std::string, std::string> database;

  if (!std::ifstream(DB_PATH).good()) {
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

void saveDatabase(const std::map<std::string, std::string>& database) {
  json root;
  for (const auto& entry : database) {
    root[entry.first] = entry.second;
  }

  std::ofstream file(DB_PATH);
  file << root;
}

void addDevice(const std::string& name, const std::string& mac) {
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

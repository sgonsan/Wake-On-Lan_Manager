#include "include/database.hpp"

#include <fstream>
#include <iostream>

#include "include/nlohmann/json.hpp"
#include "include/utils.hpp"

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

// Function to edit a device in the database
void editDevice(const std::string& oldName) {
  std::string newName;
  std::string newMac;
  auto database = loadDatabase();

  // Check if the device is in the database
  if (database.find(oldName) == database.end()) {
    std::cout << "The device " << oldName << " is not in the database"
              << std::endl;
    return;
  }

  std::cout << "Enter the new name for the device [" << oldName << "]: ";
  std::getline(std::cin, newName);
  std::cout << "Enter the new MAC address for the device ["
            << database[oldName] << "]: ";
  std::getline(std::cin, newMac);

  // If a new name is provided, update it
  if (!newName.empty() && oldName != newName) {
    if (database.find(newName) != database.end()) {
      std::cout << "A device with the name " << newName << " already exists"
                << std::endl;
      return;
    }
    database[newName] = database[oldName];
    database.erase(oldName);
  }

  // If a new MAC address is provided, update it
  if (!newMac.empty() && isMac(newMac)) {
    database[newName.empty() ? oldName : newName] = newMac;
  } else if (!newMac.empty()) {
    std::cout << "The MAC address " << newMac << " is not valid" << std::endl;
    return;
  }

  saveDatabase(database);
  std::cout << "The device has been updated successfully" << std::endl;
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

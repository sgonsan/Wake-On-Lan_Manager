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
    json raw;
    file >> raw;
    for (const auto& key : raw.items()) {
      database[key.key()] = key.value();
    }
  }

  return database;
}

void saveDatabase(const std::map<std::string, std::string>& database) {
  json raw;
  for (const auto& entry : database) {
    raw[entry.first] = entry.second;
  }

  std::ofstream file(DB_PATH);
  file << raw;
}

void addDevice() {
  std::string name;
  std::string mac;
  auto database = loadDatabase();

  std::cout << "Enter the name of the device: ";
  std::getline(std::cin, name);

  if (name.empty()) {
    std::cout << "The name cannot be empty" << std::endl;
    return;
  }

  std::cout << "Enter the MAC address of the device: ";
  std::getline(std::cin, mac);

  if (!isMac(mac)) {
    std::cout << "The MAC address " << mac << (mac.empty() ? "cannot be empty" : " is not valid") << std::endl;
    return;
  }

  int id = 1;
  if (!database.empty()) {
    id = std::stoi(database.rbegin()->first) +
         1;  // Get the last ID and increment it
  }

  database[std::to_string(id)] = name + ";" + mac;  // Save as "id: name;mac"
  saveDatabase(database);

  std::cout << "Device " << name << " (" << mac << ") has been added with ID "
            << id << std::endl;
}

// Function to edit a device in the database
void editDevice() {
  auto database = loadDatabase();
  if (database.empty()) {
    std::cout << "The database is empty" << std::endl;
    return;
  }

  std::cout << "Select the device you want to edit:" << std::endl;
  for (const auto& entry : database) {
    // Display ID: name (mac)
    std::string name = entry.second.substr(0, entry.second.find(';'));
    std::string mac = entry.second.substr(entry.second.find(';') + 1);
    std::cout << entry.first << ": " << name << " (" << mac << ")" << std::endl;
  }
  std::string id;
  std::cout << "Enter the ID of the device to edit: ";
  std::getline(std::cin, id);

  if (database.find(id) != database.end()) {
    std::string newName, newMac;
    std::string currentName = database[id].substr(0, database[id].find(';'));
    std::string currentMac = database[id].substr(database[id].find(';') + 1);

    std::cout << "Enter the new name for the device [" << currentName << "]: ";
    std::getline(std::cin, newName);
    std::cout << "Enter the new MAC address for the device [" << currentMac
              << "]: ";
    std::getline(std::cin, newMac);

    if (!newName.empty()) currentName = newName;
    if (!newMac.empty() && isMac(newMac)) {
      currentMac = newMac;
    } else if (!newMac.empty()) {
      std::cout << "The MAC address " << newMac << " is not valid" << std::endl;
      return;
    }

    database[id] = currentName + ";" + currentMac;
    saveDatabase(database);
    std::cout << "The device has been updated successfully" << std::endl;
  } else {
    std::cout << "No device found with ID " << id << std::endl;
  }
}

void removeDevice() {
  auto database = loadDatabase();
  if (database.empty()) {
    std::cout << "The database is empty" << std::endl;
    return;
  }

  std::cout << "Select the device you want to remove:" << std::endl;
  for (const auto& entry : database) {
    // Display ID: name (mac)
    std::string name = entry.second.substr(0, entry.second.find(';'));
    std::string mac = entry.second.substr(entry.second.find(';') + 1);
    std::cout << entry.first << ": " << name << " (" << mac << ")" << std::endl;
  }

  std::string id;
  std::cout << "Enter the ID of the device to remove: ";
  std::getline(std::cin, id);

  if (database.find(id) != database.end()) {
    std::cout << "Do you want to remove the device " << database[id]
              << "? [y/N] ";
    std::string answer;
    std::getline(std::cin, answer);
    if (answer == "y" || answer == "Y") {
      database.erase(id);
      saveDatabase(database);
      std::cout << "The device has been removed successfully" << std::endl;
    }
  } else {
    std::cout << "No device found with ID " << id << std::endl;
  }
}

void listDevices() {
  auto database = loadDatabase();
  if (database.empty()) {
    std::cout << "The database is empty" << std::endl;
    return;
  }

  std::cout << "Devices in the database:" << std::endl;
  for (const auto& entry : database) {
    // Display ID: name (mac)
    std::string name = entry.second.substr(0, entry.second.find(';'));
    std::string mac = entry.second.substr(entry.second.find(';') + 1);
    std::cout << entry.first << ": " << name << " (" << mac << ")" << std::endl;
  }
}
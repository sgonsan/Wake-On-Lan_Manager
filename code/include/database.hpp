#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <map>
#include <string>

std::map<std::string, std::string> loadDatabase();
void saveDatabase(const std::map<std::string, std::string>& database);
void addDevice(const std::string& name, const std::string& mac);
void editDevice(const std::string& oldName);
void removeDevice(const std::string& name);
void listDevices();

#include "../database.cpp"

#endif

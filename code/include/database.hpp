#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <map>
#include <string>

std::map<std::string, std::string> loadDatabase();
void saveDatabase(const std::map<std::string, std::string>& database);
void addDevice();
void editDevice();
void removeDevice();
void listDevices();

#include "../database.cpp"

#endif

#pragma once 
#include <string>
std::string readFileContent(const std::string& filename);
std::string generateUniqueID(const std::string& content);
bool saveObject(const std::string& content, const std::string& uniqueID);
std::string extractHash(const std::string& versionFilename);

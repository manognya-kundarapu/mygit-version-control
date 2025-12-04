#pragma once
#include <string>
#include <vector>
#include <utility>
void updateIndex(const std::string& filename, const std::string& uniqueID);
std::vector<std::pair<std::string,std::string>> getStagedFiles();
void clearIndex();
void removeFromIndex(const std::string& filename);


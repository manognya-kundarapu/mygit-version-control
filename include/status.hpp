#pragma once
#include <unordered_map>
#include <string>
void showStatus();
std::unordered_map<std::string,std::string> getLastCommitFiles(); // <-- ADD THIS
std::unordered_map<std::string,std::string> getCommitFiles(int id);


#pragma once
#include <vector>
#include <string>
#include <utility>
int generateCommitID();
void writeCommitLog(int id, const std::string& msg,const std::vector<std::pair<std::string,std::string>>& staged);


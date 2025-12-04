#include "../include/status.hpp" 
#include <filesystem>
#include <unordered_map>
#include "../include/index.hpp"
#include "../include/object.hpp"
#include <fstream>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;
void writeCommitLog(int id, const string& msg,
    const vector<pair<string,string>>& staged) {
    // Load last commit's state
    unordered_map<string,string> commitFiles = getLastCommitFiles();
    for (auto &p : staged) {
        if (p.second == "DELETED") {
            commitFiles.erase(p.first); // remove permanently
        } else {
            commitFiles[p.first] = p.second;
        }
    }
    vector<string> toRemove;
    for (auto &entry : commitFiles) {
        if (!fs::exists(entry.first)) {
            toRemove.push_back(entry.first);
        }
    }
    for (auto &f : toRemove) {
        commitFiles.erase(f);
    }
    ofstream logFile(".mygit/log", ios::app);
    logFile << "Commit: " << id << endl;
    logFile << "Message: " << msg << endl;
    logFile << "Files:" << endl;

    for (auto &entry : commitFiles) {
        logFile << entry.first << " -> " << entry.second << endl;
    }

    logFile << "---------------------------" << endl;
    logFile.close();
}
int generateCommitID() {
    int id = 0;
    ifstream infile(".mygit/commit_id");
    if (infile.good()) {
        infile >> id;
        infile.close();
    }
    id++; // increment for new commit
    ofstream outfile(".mygit/commit_id");
    outfile << id;
    outfile.close();
    return id;
}


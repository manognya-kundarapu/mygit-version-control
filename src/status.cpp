#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "../include/status.hpp"
#include "../include/index.hpp"
#include "../include/object.hpp"
#include <fstream>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;
unordered_map<string,string> getLastCommitFiles() {
    unordered_map<string,string> commitFiles;
    ifstream logFile(".mygit/log");
    string line;
    vector<string> lines;
    while (getline(logFile, line)) {
        lines.push_back(line);
    }
    logFile.close();
    int i = lines.size() - 1;
    while (i >= 0 && lines[i] != "Files:") {
        i--;
    }
    if (i < 0) return commitFiles;
    i++; 
    while (i < (int)lines.size() && lines[i] != "---------------------------") {
        string file, arrow, id;
        stringstream ss(lines[i]);
        ss >> file >> arrow >> id;
        commitFiles[file] = id;
        i++;
    }
    return commitFiles;
}
void showStatus() {
    vector<pair<string,string>> staged = getStagedFiles();
    unordered_map<string,string> lastCommitFiles = getLastCommitFiles();
    vector<string> modified, untracked, stagedOnly, clean;
    vector<string> deletedStaged;
    vector<string> deletedNotStaged;
    unordered_map<string,string> stagedMap;
    for (auto &p : staged)
        stagedMap[p.first] = p.second;
    for (auto &p : stagedMap) {
        if (p.second == "DELETED") {
            deletedStaged.push_back(p.first);
        }
    }
    for (auto &entry : staged) {
        string filename = entry.first;
        if (entry.second == "DELETED")
            continue;
        if (!fs::exists(filename)) {
            deletedStaged.push_back(filename);
            continue;
        }
        string content = readFileContent(filename);
        string newID = generateUniqueID(content);
        if (newID != entry.second)
            modified.push_back(filename);
        else
            stagedOnly.push_back(filename);
    }
    for (auto &entry : lastCommitFiles) {
        string filename = entry.first;
        string oldID = entry.second;
        if (stagedMap.count(filename)) {
            if (stagedMap[filename] == "DELETED")
                continue;
            continue;
        }
        if (!fs::exists(filename)) {
            if (!stagedMap.count(filename)) {
                deletedNotStaged.push_back(filename);
            }
            continue;
        }
        string content = readFileContent(filename);
        string newHash = extractHash(generateUniqueID(content));
        string oldHash = extractHash(oldID);
        if (newHash != oldHash)
            modified.push_back(filename);
        else
            clean.push_back(filename);
    }
    for (auto &entry : fs::directory_iterator(".")) {
        string name = entry.path().filename();
        if (name == "." || name == ".." || name == ".mygit" ||
            name == ".git" || name == ".gitignore" || name == "mygit" ||
            name == "Makefile" || name == "LICENSE" || name == "README.md" ||
            name == "src" || name == "include") 
            continue;
        if (!fs::is_regular_file(entry.path())) continue;
        if (!stagedMap.count(name) && !lastCommitFiles.count(name))
            untracked.push_back(name);
    }
    if (!stagedOnly.empty()) {
        cout << "Staged:" << endl;
        for (auto &f : stagedOnly)
            cout << "  " << f << endl;
    }
    if (!modified.empty()) {
        cout << "Modified:" << endl;
        for (auto &f : modified)
            cout << "  " << f << endl;
    }
    if (!clean.empty()) {
        cout << "Clean:" << endl;
        for (auto &f : clean)
            cout << "  " << f << endl;
    }
    if (!deletedStaged.empty()) {
        cout << "Deleted (staged):" << endl;
        for (auto &f : deletedStaged)
            cout << "  " << f << endl;
    }
    if (!deletedNotStaged.empty()) {
        cout << "Deleted (not staged):" << endl;
        for (auto &f : deletedNotStaged)
            cout << "  " << f << endl;
    }
    if (!untracked.empty()) {
        cout << "Untracked:" << endl;
        for (auto &f : untracked)
            cout << "  " << f << endl;
    }
    if (stagedOnly.empty() && modified.empty() && clean.empty() &&
        untracked.empty() && deletedStaged.empty() && deletedNotStaged.empty())
        cout << "No changes!" << endl;
}
unordered_map<string,string> getCommitFiles(int id) {
    unordered_map<string,string> commitFiles;
    ifstream logFile(".mygit/log");
    string line;
    vector<string> lines;
    while (getline(logFile, line)) lines.push_back(line);
    logFile.close();
    for (int i = 0; i < (int)lines.size(); i++) {
        if (lines[i] == "Commit: " + to_string(id)) {
            while (i < lines.size() && lines[i] != "Files:") i++;
            i++; 
            while (i < lines.size() && lines[i] != "---------------------------") {
                string file, arrow, ver;
                stringstream ss(lines[i]);
                ss >> file >> arrow >> ver;
                commitFiles[file] = ver;
                i++;
            }
            break;
        }
    }
    return commitFiles;
}



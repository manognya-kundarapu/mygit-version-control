#include "../include/diff.hpp"
#include "../include/status.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
string loadVersionContent(const string& filename, int commitID) {
    auto commitFiles = getCommitFiles(commitID);
    if (!commitFiles.count(filename)) {
        return "__FILE_NOT_FOUND__";
    }
    string versionFile = commitFiles[filename];
    string path = ".mygit/objects/" + versionFile;
    ifstream in(path);
    if (!in) return "__ERROR__";
    return string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
}
vector<string> splitLines(const string& text) {
    vector<string> lines;
    stringstream ss(text);
    string line;
    while (getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}
void diffFile(const string& filename, int c1, int c2) {
    string oldContent = loadVersionContent(filename, c1);
    string newContent = loadVersionContent(filename, c2);
    if (oldContent == "__FILE_NOT_FOUND__") {
        cout << "File not found in commit " << c1 << endl;
        return;
    }
    if (newContent == "__FILE_NOT_FOUND__") {
        cout << "File not found in commit " << c2 << endl;
        return;
    }
    auto oldLines = splitLines(oldContent);
    auto newLines = splitLines(newContent);
    cout << "Diff between commit " << c1 << " and " << c2 
         << " for file: " << filename << endl;
    int n = oldLines.size();
    int m = newLines.size();
    int i = 0, j = 0;
    while (i < n || j < m) {
        if (i < n && j < m && oldLines[i] == newLines[j]) {
            i++; j++; // same line, skip
        }
        else {
            if (j < m) cout << "+ " << newLines[j] << endl;
            if (i < n) cout << "- " << oldLines[i] << endl;
            i++; 
            j++;
        }
    }
}

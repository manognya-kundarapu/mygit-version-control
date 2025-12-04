#include <iostream>
#include <fstream>
#include <filesystem>
#include "../include/restore.hpp"
#include "../include/status.hpp"
using namespace std;
void restoreFile(const string& filename, int commitID) {
    auto commitFiles = getCommitFiles(commitID);
    if (!commitFiles.count(filename)) {
        cout << "Error: File not found in commit " << commitID << endl;
        return;
    }
    string versionFile = commitFiles[filename];
    string path = ".mygit/objects/" + versionFile;
    ifstream in(path, ios::binary);
    if (!in) {
        cout << "Error: Cannot read stored version!" << endl;
        return;
    }
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    ofstream out(filename, ios::binary);
    out << content;
    out.close();
    cout << "Restored " << filename << " from commit " << commitID << endl;
}

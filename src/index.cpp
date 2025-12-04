#include <fstream>
#include <iostream>
#include "../include/index.hpp"
using namespace std;
void updateIndex(const string& filename, const string& uniqueID) {
    ofstream indexFile(".mygit/index", ios::app);
    indexFile << filename << " " << uniqueID << endl;
    indexFile.close();
}
vector<pair<string,string>> getStagedFiles() {
    vector<pair<string,string>> staged;
    ifstream indexFile(".mygit/index");
    string filename, uniqueID;
    while (indexFile >> filename >> uniqueID) {
        if (uniqueID == "DELETED") {
            staged.push_back({filename, "DELETED"});
        }
        else {
            staged.push_back({filename, uniqueID});
        }
    }
    indexFile.close();
    return staged;
}
void clearIndex() {
    ofstream indexFile(".mygit/index", ios::trunc);
    indexFile.close();
}
void removeFromIndex(const string& filename) {
    ifstream indexFile(".mygit/index");
    vector<pair<string, string>> staged;
    string file, id;
    while (indexFile >> file >> id) {
        if (file != filename) {
            staged.push_back({file, id});
        }
    }
    indexFile.close();
    ofstream newIndex(".mygit/index", ios::trunc);
    for (auto &entry : staged) {
        newIndex << entry.first << " " << entry.second << endl;
    }
    newIndex.close();
}





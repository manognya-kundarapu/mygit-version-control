#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include "../include/object.hpp"
using namespace std;
string readFileContent(const string& filename){
    ifstream file(filename, ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
string generateUniqueID(const string& content) {
    unsigned long hash = 5381;

    for (char c : content) {
        hash = ((hash << 5) + hash) + c;
    }
    // timestamp to avoid collisions
    long timestamp = chrono::system_clock::now().time_since_epoch().count();
    return to_string(hash) + "-" + to_string(timestamp);
}
bool saveObject(const string& content, const string& uniqueID) {
    string path = ".mygit/objects/" + uniqueID;
    ofstream out(path, ios::binary);
    if (!out) return false;
    out << content;
    out.close();
    return true;
}
string extractHash(const string& versionFilename) {
    size_t pos = versionFilename.find("-");
    if (pos == string::npos) return versionFilename;
    return versionFilename.substr(0, pos);
}



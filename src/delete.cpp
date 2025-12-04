#include <iostream>
#include <fstream>
#include <filesystem>
#include "../include/delete.hpp"
using namespace std;
namespace fs = std::filesystem;
void deleteFile(const string& filename) {
    // 1. Remove file from working directory
    if (fs::exists(filename)) {
        fs::remove(filename);
        cout << "Deleted: " << filename << endl;
    } else {
        cout << "File already deleted: " << filename << endl;
    }
    // 2) Add DELETED marker to index
    ofstream index(".mygit/index", ios::app);
    index << filename << " DELETED" << endl;
    index.close();
    cout << "Staged deletion for next commit." << endl;
}


#include <iostream>
#include <string.h>
#include <fstream>
#include "../include/repository.hpp"
#include <filesystem>
#include "../include/object.hpp"
#include "../include/index.hpp"
#include "../include/utils.hpp"
#include <vector>
#include "../include/status.hpp"
#include "../include/restore.hpp"
#include "../include/delete.hpp"
#include "../include/diff.hpp"
using namespace std;
namespace fs = std::filesystem;
int main(int argc, char* argv[]){
    if(argc<2){
        cout<<"Usage: mygit <command>"<<endl;
        return 1;
    }
    string command = argv[1];
    if (command == "init"){
        initRepository();
    }
    else if(command == "add"){
        if(argc<3){
            cout<<"Usage: mygit add <filename>"<<endl;
            return 1;
        }
        string filename = argv[2];
        if(!fs::exists(".mygit")){
            cout << "Error: Not a myGit repository! Run 'mygit init' first." << endl;
            return 1;
        }
         if (!fs::exists(filename)) {
            cout << "Error: File '" << filename << "' does not exist!" << endl;
            return 1;
        }
        cout<<"Adding file:"<<filename<<endl;
        string content = readFileContent(filename);
        string uniqueID = generateUniqueID(content);
        if (!saveObject(content, uniqueID)) {
        cout << "Error storing object!" << endl;
        return 1;
        }
        updateIndex(filename, uniqueID);
        cout << "Added: " << filename << endl;
        cout << "Hash: " << uniqueID << endl;
        cout << "Size: " << content.size() << " bytes" << endl;
        cout << "Status: Staged Successfully!" << endl;
    }
    else if (command == "commit") {
        if (argc < 3) {
            cout << "Usage: mygit commit \"message\"" << endl;
            return 1;
        }
        string message = argv[2];

        if (!fs::exists(".mygit")) {
            cout << "Error: Run 'mygit init' first!" << endl;
            return 1;
        }
        vector<pair<string,string>> staged = getStagedFiles();
        if (staged.empty()) {
            cout << "No changes to commit." << endl;
            return 1;
        }
        int commitID = generateCommitID();
        writeCommitLog(commitID, message, staged);
        clearIndex();
        cout << "Committed successfully as ID: " << commitID << endl;
    }
    else if (command == "log") {
        if (!fs::exists(".mygit")) {
            cout << "Error: Not a myGit repository! Run 'mygit init' first." << endl;
            return 1;
        }
        ifstream logFile(".mygit/log");
        string line;
        while (getline(logFile, line)) {
            cout << line << endl;
        }
        logFile.close();
    }
    else if (command == "unstage") {
        if (argc < 3) {
            cout << "Usage: mygit unstage <filename>" << endl;
            return 1;
        }
        string filename = argv[2];
        if (!fs::exists(".mygit")) {
            cout << "Error: Not a myGit repository! Run 'mygit init' first." << endl;
            return 1;
        }
        removeFromIndex(filename);
        cout << "Removed '" << filename << "' from staging area" << endl;
    }
    else if (command == "status") {
        if (!fs::exists(".mygit")) {
            cout << "Error: Not a myGit repository!" << endl;
            return 1;
        }
    showStatus();
    }
    else if (command == "restore") {
        if (argc < 4) {
            cout << "Usage: mygit restore <filename> <commitID>" << endl;
            return 1;
        }
        string filename = argv[2];
        int cid = stoi(argv[3]);
        restoreFile(filename, cid);
    }
    else if (command == "delete") {
        if (argc < 3) {
            cout << "Usage: mygit delete <filename>" << endl;
            return 1;
        }
        deleteFile(argv[2]);
    }
    else if (command == "diff") {
        if (argc < 5) {
            cout << "Usage: mygit diff <filename> <commit1> <commit2>" << endl;
            return 1;
        }
        string filename = argv[2];
        int c1 = stoi(argv[3]);
        int c2 = stoi(argv[4]);

        diffFile(filename, c1, c2);
    }
    else{
        cout<<"Unknown command: "<<command<<endl;
    }
    return 0; 
}
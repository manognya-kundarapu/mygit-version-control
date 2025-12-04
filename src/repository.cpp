#include <iostream>
#include <filesystem>
#include <fstream>
#include "../include/repository.hpp"
using namespace std;
namespace fs = std::filesystem;
void initRepository(){
    if(fs::exists(".mygit")){
        cout<<"Repository already exists"<<endl;
        return;
    }
    fs::create_directory(".mygit");
    fs::create_directory(".mygit/objects");
    ofstream indexFile(".mygit/index");
    indexFile.close();
    ofstream logFile(".mygit/log");
    logFile.close();
    cout<<"Initialized empty myGit repository in .mygit/"<<endl;
}

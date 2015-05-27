#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "Constant.h"

#include "FileSystem.h"

using namespace std;

int main() {
    FileSystem* fs = FileSystem::GetInstance();

    fs->Init();

    string cmd;
    vector<string> argv;

    cout << fs->Pwd() << " $: ";

    while (getline(cin, cmd))
    {
        stringstream ss(cmd);
        string word;
        while(ss >> word)
        {
            argv.push_back(word);
        }

        int argc = argv.size();

        switch (CMD_TABLE.at(argv[0]))
        {
            case CMD_ENUM::MKDIR : {
                if (argc != 2) {cout << "Usage: mkdir dir_name" << endl; break;}
                fs->Mkdir(argv[1].c_str());
                break;
            };

            case CMD_ENUM::RMDIR : {
                if (argc != 2) {cout << "Usage: rmdir dir_name" << endl; break;}
                fs->Rmdir(argv[1].c_str());
                break;
            };

            case CMD_ENUM::CREATE : {
                if (argc != 2) {cout << "Usage: create file_name" << endl; break;}
                fs->Create(argv[1].c_str());
                break;
            };

            case CMD_ENUM::DELETE : {
                if (argc != 2) {cout << "Usage: delete file_name" << endl; break;}
                fs->Delete(argv[1].c_str());
                break;
            };

            case CMD_ENUM::READ : {
                if (argc != 2) {cout << "Usage: read file_name" << endl; break;}
                fs->Read(argv[1].c_str());
                break;
            };

            case CMD_ENUM::WRITE : {
                if (argc != 3) {cout << "Usage: write file_name content" << endl; break;}
                fs->Write(argv[1].c_str(), argv[2].c_str());
                break;
            };

            case CMD_ENUM::CD : {
                if (argc != 2) {cout << "Usage: cd full_path" << endl; break;}
                fs->Cd(argv[1].c_str());
                break;
            };

            case CMD_ENUM::LS : {
                if (argc != 1) {cout << "Usage: ls" << endl; break;}
                fs->Ls();
                break;
            };

            case CMD_ENUM::PWD : {
                if (argc != 1) {cout << "Usage: pwd" << endl; break;}
                fs->Pwd();
                break;
            };

            case CMD_ENUM::PFS : {
                if (argc != 1) {cout << "Usage: pfs" << endl; break;}
                fs->PrintFileSystem();
                break;
            };

            case CMD_ENUM::EXIT : {
                if (argc != 1) {cout << "Usage: exit" << endl; break;}
                fs->DestroyInstance();
                exit(0);
            };

            default: { cout << "command not exist" << endl; break;}

        }

        argv.clear();
        cout << fs->Pwd() << " $: ";
    }

    return 0;
}
#include <iostream>

#include "FileSystem.h"

using namespace std;

int main() {
    FileSystem* fs = FileSystem::GetInstance();

    fs->Init();

    fs->Create("chen.c");

    fs->Mkdir("chen");

    fs->Cd("/chen/");

    fs->Create("chen.c");

    fs->Mkdir("chen");

    fs->Write("chen.c", "chenyixiao's filesystem");

    fs->Read("chen.c");

    fs->Ls();                  //打印当前目录下的所有文件

    fs->PrintFileSystem();     // 打印整个文件系统的所有文件以及目录

    fs->DestroyInstance();

    return 0;
}
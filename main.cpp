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

    fs->Ls();                  //��ӡ��ǰĿ¼�µ������ļ�

    fs->PrintFileSystem();     // ��ӡ�����ļ�ϵͳ�������ļ��Լ�Ŀ¼

    fs->DestroyInstance();

    return 0;
}
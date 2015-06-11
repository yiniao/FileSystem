//
// Created by yiniao on 2015/5/20.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

#include <iostream>
#include <map>
#include <string>


using namespace std;

class SuperBlock;
class BlockMap;
class InodeMap;
class Inode;


class FileSystem {
public:
    void Init();

    int Mkdir(const char* name);

    int Rmdir(const char* name);

    int Create(const char* name);

    int Write(const char* name, const char* content);

    int Read(const char* name);

    void Delete(const char* name);

    void Cd(const char* path);

    void Ls();

    string Pwd();

    void PrintBitMap();
    void PrintFileSystem();



private:

    int InitRootDir();

    void* GetBlockPointer(int index);
    void* GetInodeBlockPointer(int index);
    void* GetDataBlockPointer(int index);

    int ApplyInode();
    int ApplyDataBlock();

    void ReleaseInode(int index);
    void ReleaseDataBlock(int index);


    void PrintBlockMap();
    void PrintInodeMap();


    void* fs_;

    SuperBlock* super_block_;
    BlockMap* block_map_;
    InodeMap* inode_map_;

    string    pwd_;
    map<string, int> search_map_;

public:
    static FileSystem *GetInstance()
    {
        std::cout << "[INFO]--FileSystem is created\n";
        if (instance_ == nullptr)
            instance_ = new FileSystem();
        return instance_;
    }

    static void DestroyInstance()
    {
        if (instance_ != nullptr)
        {
            delete instance_;
            instance_ = nullptr;
        }
        std::cout << "[INFO]--FileSystem is destroied\n";
    }

private:
    FileSystem() {};
    static FileSystem *instance_;
};


#endif //FILESYSTEM_FILESYSTEM_H

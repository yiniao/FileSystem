//
// Created by yiniao on 2015/4/19.
//

#include "FileSystem.h"

#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "Constant.h"
#include "SuperBlock.h"
#include "BlockMap.h"
#include "InodeMap.h"
#include "Inode.h"
#include "Dir.h"
#include "File.h"

using namespace std;

FileSystem *FileSystem::instance_ = nullptr;

void FileSystem::Init() {
    fs_ = malloc(BLOCK_NUM * BLOCK_SIZE);

    super_block_ = new (GetBlockPointer(0)) SuperBlock();
    block_map_   = new (GetBlockPointer(1)) BlockMap();
    inode_map_   = new (GetBlockPointer(2)) InodeMap();

    InitRootDir();
}

int FileSystem::Mkdir(const char *name) {
    int parent_dir_id = search_map_[pwd_];


    string full_name = pwd_ + name + "/";

    int id = ApplyInode();
    if (id < 0) { return -1; }

    int dir_index = ApplyDataBlock();
    if (dir_index < 0) { return -1; }

    Inode* inode = new (GetInodeBlockPointer(id)) Inode();
    inode->id_ = id;
    inode->name_ = name;
    inode->block_array_[0] = dir_index;
    inode->type_ = DIR_TYPE;

    Dir * parent_dir = reinterpret_cast<Dir*>(GetDataBlockPointer(parent_dir_id));
    parent_dir->file_array_[parent_dir->inode_num_] = id;
    (parent_dir->inode_num_)++;

    Dir * dir = new (GetDataBlockPointer(dir_index)) Dir();
    dir->parent_id_ = parent_dir_id;

    search_map_.insert(pair<string, int>(full_name, id));
    return id;
}

int FileSystem::Rmdir(const char *name) {

    string full_dir_name = pwd_ + name + "/";



    for (auto iter = search_map_.begin(); iter != search_map_.end();)
    {
        auto map = *iter;
        if (map.first.find(full_dir_name) == 0)
        {
            int inode_id = map.second;
            Inode *inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(inode_id));
            if (inode->type_ == FILE_TYPE)
            {
                for (int j = 0; j < inode->size_; j++) {
                    ReleaseDataBlock(inode->block_array_[j]);
                }
            }

            ReleaseInode(inode_id);
            search_map_.erase(iter++);
        }
        else {
            iter++;
        }
    }

    return 0;
}


int FileSystem::Create(const char *name) {
    int parent_dir_id = search_map_[pwd_];


    string full_name = pwd_ + name;

    int id = ApplyInode();
    if (id < 0) { return -1; }

    Inode* inode = new (GetInodeBlockPointer(id)) Inode();
    inode->id_ = id;
    inode->name_ = name;
    inode->type_ = FILE_TYPE;

    Inode* dir_inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(parent_dir_id));
    int dir_data_id = dir_inode->block_array_[0];


    Dir* dir = reinterpret_cast<Dir*>(GetDataBlockPointer(dir_data_id));


    dir->file_array_[dir->inode_num_] = id;

    (dir->inode_num_)++;

    search_map_.insert(pair<string, int>(full_name, id));
    return id;
}

int FileSystem::Write(const char* name, const char* buffer) {
    string full_name = pwd_ + name;
    int id = search_map_[full_name];

    Inode* inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(id));
    if (inode->type_ == DIR_TYPE) { return -1; }

    int len = strlen(buffer);
    if (len > BLOCK_SIZE * MAX_BLOCK_NUM_PER_FILE) { return -1; }

    int data_block_num = len / BLOCK_SIZE;
    int data_remain = len % BLOCK_SIZE;
    if (data_block_num > block_map_->GetAllAvailableNum()) { return -1;}

    if (data_block_num > 0) {
        for (int i = 0; i < data_block_num; i++) {
            int index = ApplyDataBlock();
            if (index < 0) { return -1; }

            File *file = new(GetDataBlockPointer(index)) File();
            strncpy(file->content_, buffer + (i * BLOCK_SIZE), BLOCK_SIZE);

            inode->block_array_[i] = index;
        }

        if (data_remain != 0) {
            int index = ApplyDataBlock();
            if (index < 0) { return -1;}

            File* file = new (GetDataBlockPointer(index)) File();
            strncpy(file->content_, buffer + (data_block_num * BLOCK_SIZE) , data_remain);

            inode->block_array_[data_block_num] = index;

            inode->size_ = len;

        }
    }
    else {
        int index = ApplyDataBlock();
        if (index < 0) { return -1;}

        File* file = new (GetDataBlockPointer(index)) File();
        strncpy(file->content_, buffer + (data_block_num * BLOCK_SIZE) , data_remain);

        inode->block_array_[data_block_num] = index;

        inode->size_ = len;
    }

    return 0;
}


int FileSystem::Read(const char* name) {

    string full_name = pwd_ + name;
    int id = search_map_[full_name];

    Inode* inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(id));
    if (inode->type_ == DIR_TYPE) { return -1; }

    int len = inode->size_;
    int data_block_num = len / BLOCK_SIZE;
    int data_remain = len % BLOCK_SIZE;

    if (data_block_num > 0) {
        for (int i = 0; i < data_block_num; i++) {
            int index = inode->block_array_[i];
            File* file = reinterpret_cast<File*>(GetDataBlockPointer(index));
            cout << file->content_ << endl;
        }

        if (data_remain != 0) {
            int index = inode->block_array_[data_block_num];
            File* file = reinterpret_cast<File*>(GetDataBlockPointer(index));
            char s[data_remain];
            strncpy(s, file->content_, data_remain);
            cout << s << endl;
        }
    }
    else {
        int index = inode->block_array_[data_block_num];
        File* file = reinterpret_cast<File*>(GetDataBlockPointer(index));
        char s[data_remain];
        strncpy(s, file->content_, data_remain);
        cout << s << endl;
    }

}



void FileSystem::Delete(const char* name) {
    string full_name = pwd_ + name;
    int id = search_map_[full_name];
    search_map_.erase(full_name);

    Delete(id);
}

void FileSystem::Delete(int id) {
    int parent_dir_id = search_map_[pwd_];

    Inode* dir_inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(parent_dir_id));
    Dir* dir = reinterpret_cast<Dir*>(GetDataBlockPointer(dir_inode->block_array_[0]));

    for (int i = 0; i < dir->inode_num_; i++) {
        if (dir->file_array_[i] == id) {
            dir->inode_num_--;
            for ( int j = i; j < dir->inode_num_; j++) {
                dir->file_array_[j] = dir->file_array_[j + 1];
            }
        }
    }

    Inode* inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(id));

    int block_num = inode->size_ / BLOCK_SIZE;
    int data_remain = inode->size_ % BLOCK_SIZE;

    if (data_remain != 0) {
        block_num++;
    }

    for (int i = 0; i < block_num; i++) {
        ReleaseDataBlock(inode->block_array_[i]);
    }

    ReleaseInode(id);
}


void FileSystem::Cd(const char *path) {
    pwd_ = path;
}

void FileSystem::Ls() {
    int id = search_map_[pwd_];

    if (id < 0) {
        return;
    }
    Inode* inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(id));

    int dir_id = inode->block_array_[0];

    Dir* dir = reinterpret_cast<Dir*>(GetDataBlockPointer(dir_id));

    for (int i = 0; i < dir->inode_num_; i++) {
        int file_id = dir->file_array_[i];
        Inode* file_inode = reinterpret_cast<Inode*>(GetInodeBlockPointer(file_id));
        cout << file_inode->name_ << endl;
    }
}

void FileSystem::PrintBitMap() {
    PrintInodeMap();
    PrintBlockMap();
}

void FileSystem::PrintFileSystem() {
    for(auto m : search_map_) {
        cout  <<  m.second << " " << m.first << endl;
    }
}

/************************* private ****************************/


int FileSystem::InitRootDir() {
    int id = ApplyInode();
    if (id < 0) { return -1; }

    int dir_index = ApplyDataBlock();
    if (dir_index < 0) { return -1; }

    Inode* inode = new (GetInodeBlockPointer(id)) Inode();
    inode->id_ = id;
    inode->name_ = "/";
    inode->block_array_[0] = dir_index;
    inode->type_ = DIR_TYPE;

    Dir * dir = new (GetDataBlockPointer(dir_index)) Dir();

    search_map_.insert(pair<string, int>("/", id));
    pwd_ = "/";

    return id;
}


void *FileSystem::GetBlockPointer(int index) {
    if (index >= BLOCK_NUM) {
        return nullptr;
    }
    return reinterpret_cast<char *>(fs_) + (index * BLOCK_SIZE);
}

void *FileSystem::GetInodeBlockPointer(int index) {
    return GetBlockPointer(index + 3);
}

void *FileSystem::GetDataBlockPointer(int index) {
    return GetBlockPointer(index + 24);
}

int FileSystem::ApplyInode() {
    int index = inode_map_->GetFisrtAvailableIndex();
    if (index < 0) { return -1;}
    inode_map_->Set(index);
    return index;
}


int FileSystem::ApplyDataBlock() {
    int index = block_map_->GetFisrtAvailableIndex();
    if (index < 0) { return -1;}
    block_map_->Set(index);
    return index;
}


void FileSystem::ReleaseInode(int index) {
    inode_map_->Reset(index);
}

void FileSystem::ReleaseDataBlock(int index) {
    block_map_->Reset(index);
}

void FileSystem::PrintBlockMap() {
    block_map_->Print();
}

void FileSystem::PrintInodeMap() {
    inode_map_->Print();
}


string FileSystem::Pwd() {
    return pwd_;
}

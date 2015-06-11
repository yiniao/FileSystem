//
// Created by yiniao on 2015/5/20.
//

#ifndef FILESYSTEM_CONSTANT_H
#define FILESYSTEM_CONSTANT_H

#include <map>
#include <string>

using namespace std;

const int BLOCK_SIZE = 1024;
const int BLOCK_NUM = 1024;

const int SUPER_BLOCK_NUM = 1;
const int BLOCK_MAP_BLOCK_NUM = 1;
const int INODE_MAP_BLOCK_NUM = 1;
const int INODE_BLOCK_NUM = 21;
const int DATA_BLOCK_NUM = BLOCK_NUM - SUPER_BLOCK_NUM -
        BLOCK_MAP_BLOCK_NUM - INODE_MAP_BLOCK_NUM - INODE_BLOCK_NUM;

const int FILE_TYPE = 1;
const int DIR_TYPE = 2;

const int MAX_BLOCK_NUM_PER_FILE = 15;
const int MAX_FILE_NUM_PER_DIR = 10;

enum CMD_ENUM{
        MKDIR, RMDIR, CREATE, DELETE, READ, WRITE, CD, LS, PWD,
        PFS,                         /*print filesytem*/
        EXIT
};

const map<string, int> CMD_TABLE = {
        {"mkdir", CMD_ENUM::MKDIR },
        {"rmdir", CMD_ENUM::RMDIR },
        {"create", CMD_ENUM::CREATE },
        {"delete", CMD_ENUM::DELETE },
        {"read", CMD_ENUM::READ },
        {"write", CMD_ENUM::WRITE },
        {"cd", CMD_ENUM::CD },
        {"ls", CMD_ENUM::LS },
        {"pwd", CMD_ENUM::PWD },
        {"pfs", CMD_ENUM::PFS },
        {"exit", CMD_ENUM::EXIT }
};

#endif //FILESYSTEM_CONSTANT_H

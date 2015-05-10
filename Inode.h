//
// Created by yiniao on 2015/4/19.
//

#ifndef FILESYSTEM_INODE_H
#define FILESYSTEM_INODE_H


#include <string>

#include "Constant.h"

class Inode {
public:
    int             id_;
    int             type_;   //inode 节点类型  1：文件  2：目录
    std::string     name_;
    int             block_array_[MAX_BLOCK_NUM_PER_FILE];
    int             size_;
};


#endif //FILESYSTEM_INODE_H

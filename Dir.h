//
// Created by yiniao on 2015/5/20.
//

#ifndef FILESYSTEM_DIR_H
#define FILESYSTEM_DIR_H

#include "Constant.h"

class Dir {
public:
    int file_array_[MAX_FILE_NUM_PER_DIR];
    int inode_num_;
    int parent_id_;
};


#endif //FILESYSTEM_DIR_H

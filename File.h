//
// Created by yiniao on 2015/5/20.
//

#ifndef FILESYSTEM_FILE_H
#define FILESYSTEM_FILE_H


#include <string>
#include "Constant.h"

class File {
public:
    char content_[BLOCK_SIZE];
};


#endif //FILESYSTEM_FILE_H

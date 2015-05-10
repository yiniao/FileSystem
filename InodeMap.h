//
// Created by yiniao on 2015/4/19.
//

#ifndef FILESYSTEM_INODEMAP_H
#define FILESYSTEM_INODEMAP_H


#include <bitset>

#include "Constant.h"

class InodeMap {
public:
    std::bitset<INODE_BLOCK_NUM> bitmap_;

    void Set(int index) {
        bitmap_.set(index);
    }

    void Reset(int index) {
        bitmap_.reset(index);
    }

    int GetFisrtAvailableIndex();

    void Print();
};


#endif //FILESYSTEM_INODEMAP_H

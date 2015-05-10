//
// Created by yiniao on 2015/4/19.
//

#ifndef FILESYSTEM_BLOCKMAP_H
#define FILESYSTEM_BLOCKMAP_H


#include <bitset>

#include "Constant.h"

class BlockMap {
public:
    std::bitset<DATA_BLOCK_NUM> bitmap_;

    void Set(int index) {
        bitmap_.set(index);
    }

    void Reset(int index) {
        bitmap_.reset(index);
    }

    int GetFisrtAvailableIndex();

    int GetAllAvailableNum();

    void Print();
};


#endif //FILESYSTEM_BLOCKMAP_H
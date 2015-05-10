//
// Created by yiniao on 2015/4/19.
//

#include <iostream>
#include "InodeMap.h"

int InodeMap::GetFisrtAvailableIndex() {
    for (int i = 0; i < INODE_BLOCK_NUM; i++) {
        if (!bitmap_.test(i)) {
            return i;
        }
    }
    return -1;
}

void InodeMap::Print() {
    std::cout << "InodeMap:{";
    for (int i = 0; i < INODE_BLOCK_NUM; i++) {
        if (bitmap_.test(i)) {
            std::cout << i <<", ";
        }
    }
    std::cout << "}\n";
}

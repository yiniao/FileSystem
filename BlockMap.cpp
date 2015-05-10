//
// Created by yiniao on 2015/4/19.
//

#include <iostream>
#include "BlockMap.h"

int BlockMap::GetFisrtAvailableIndex() {
    for (int i = 0; i < DATA_BLOCK_NUM; i++) {
        if (!bitmap_.test(i)) {
            return i;
        }
    }
    return -1;
}

int BlockMap::GetAllAvailableNum() {
    int num = 0;
    for (int i = 0; i < DATA_BLOCK_NUM; i++) {
        if (!bitmap_.test(i)) {
            num++;
            continue;
        }
    }
    return num;
}

void BlockMap::Print() {
    std::cout << "BlockMap:{";
    for (int i = 0; i < DATA_BLOCK_NUM; i++) {
        if (bitmap_.test(i)) {
            std::cout << i <<", ";
        }
    }
    std::cout << "}\n";
}

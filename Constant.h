//
// Created by yiniao on 2015/4/19.
//

#ifndef FILESYSTEM_CONSTANT_H
#define FILESYSTEM_CONSTANT_H

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


#endif //FILESYSTEM_CONSTANT_H

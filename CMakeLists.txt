cmake_minimum_required(VERSION 3.1)
project(FileSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(FileSystem ${SOURCE_FILES} FileSystem.cpp FileSystem.h SuperBlock.cpp SuperBlock.h BlockMap.cpp BlockMap.h InodeMap.cpp InodeMap.h Inode.cpp Inode.h Dir.cpp Dir.h File.cpp File.h Constant.h)
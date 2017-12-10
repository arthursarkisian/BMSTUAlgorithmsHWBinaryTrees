cmake_minimum_required(VERSION 3.8)
project(BinarTrees)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AVL/AVLTree.cpp AVL/AVLTree.hpp AA/AATree.cpp AA/AATree.hpp)
add_executable(BinarTrees ${SOURCE_FILES})
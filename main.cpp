#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <ctime>

#include "AVL/AVLTree.hpp"
#include "AA/AATree.hpp"

bool LineIsOk(const std::string &str, const std::string &command) {
    std::istringstream iss(str);
    std::string tmp;

    iss >> tmp;
    if (tmp != command) {
        return false;
    }
    tmp.clear();
    iss >> tmp;

    if (tmp.empty()) {
        return false;
    }
    tmp.clear();
    iss >> tmp;

    if (tmp.empty()) {
        return false;
    }

    tmp.clear();
    iss >> tmp;

    return tmp.empty();
}

int FindKey(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    int key = atoi(tmp.c_str());
    return key;
}

int FindValue(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    tmp.clear();
    iss >> tmp;
    int value = atoi(tmp.c_str());
    return value;
}

bool FileIsEqual(const std::string &firstFileName, const std::string &secondFileName) {
    std::ifstream firstFile(firstFileName), secondFile(secondFileName);
    assert(firstFile);
    assert(secondFile);

    std::string buffer1((std::istreambuf_iterator<char>(firstFile)), std::istreambuf_iterator<char>());
    std::string buffer2((std::istreambuf_iterator<char>(secondFile)), std::istreambuf_iterator<char>());
    firstFile.close();
    secondFile.close();

    return (buffer1 == buffer2);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 0;
    }
    std::string line;
    std::ifstream fileIn(argv[1]);
    assert(fileIn);
    std::ofstream fileOut(argv[2]);
    assert(fileOut);

    //AVL tree tests

    AVLTree<int> avlTree;

    srand(time(0));

    while (getline(fileIn, line)) {
        if (line.find("delete") == 0) {
            if (LineIsOk(line, "delete")) {
                if (!avlTree.Delete(FindKey(line), FindValue(line))) {
                    fileOut << "error" << std::endl;
                } else {
                    fileOut << "Ok" << std::endl;
                }
            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line == "print") {
            avlTree.PrintInOrderTraversal(fileOut);
            fileOut << std::endl;
        }
        if (line.find("add") == 0) {
            if (LineIsOk(line, "add") != 0) {
                avlTree.Insert(FindKey(line), FindValue(line));
            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line.find("search") == 0) {
            if (LineIsOk(line, "search") != 0) {
                if (!avlTree.Search(FindKey(line), FindValue(line))) {
                    fileOut << "error" << std::endl;
                } else {
                    fileOut << "Ok" << std::endl;
                }

            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line == "min") {
            fileOut << avlTree.Min() << std::endl;
        }
        if (line == "max") {
            fileOut << avlTree.Max() << std::endl;
        }
        if (line == " ") {
            fileOut << "error" << std::endl;
        }
    }

    std::cout << "runtime = " << clock()/1000.0 << std::endl;

    if (FileIsEqual(argv[2], argv[3])) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Not correct" << std::endl;
    }


    fileIn.clear();
    fileIn.seekg(0);
    fileOut.clear();
    fileOut.seekp(0);

    //AA tree tests

    AATree<int> aaTree;

    srand(time(0));

    while (getline(fileIn, line)) {
        if (line.find("delete") == 0) {
            if (LineIsOk(line, "delete")) {
                if (!aaTree.Delete(FindKey(line), FindValue(line))) {
                    fileOut << "error" << std::endl;
                } else {
                    fileOut << "Ok" << std::endl;
                }
            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line == "print") {
            aaTree.PrintInOrderTraversal(fileOut);
            fileOut << std::endl;
        }
        if (line.find("add") == 0) {
            if (LineIsOk(line, "add") != 0) {
                aaTree.Insert(FindKey(line), FindValue(line));
            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line.find("search") == 0) {
            if (LineIsOk(line, "search") != 0) {
                if (!aaTree.Search(FindKey(line), FindValue(line))) {
                    fileOut << "error" << std::endl;
                } else {
                    fileOut << "Ok" << std::endl;
                }
            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line == "min") {
            fileOut << aaTree.Min() << std::endl;
        }
        if (line == "max") {
            fileOut << aaTree.Max() << std::endl;
        }
        if (line == " ") {
            fileOut << "error" << std::endl;
        }
    }

    std::cout << "runtime = " << clock()/1000.0 << std::endl;

    if (FileIsEqual(argv[2], argv[3])) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Not correct" << std::endl;
    }

    fileIn.close();
    fileOut.close();




//    AATree<int> aaTree;
//    aaTree.Insert(1, 2);
//    aaTree.Insert(2, 148);
//    aaTree.Insert(3, 45);
//    aaTree.Insert(4, 32);
//    aaTree.Insert(5, 16);
//    aaTree.Insert(6, 31);
//    aaTree.Insert(7, 8);
//    aaTree.Insert(8, 5);
//    aaTree.Insert(9, 3);
//    aaTree.PrintInOrderTraversal(std::cout);
//    std::cout << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(1, 2) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(2, 148) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(3, 45) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(4, 32) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(6, 16) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(6, 31) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(7, 8) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(8, 5) << std::endl;
//    std::cout << std::boolalpha << aaTree.Search(9, 3) << std::endl;


    return 0;
}
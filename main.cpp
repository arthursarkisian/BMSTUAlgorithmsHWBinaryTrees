#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>

#include <ctime>

//#include "AA/AATree.hpp"
#include "AVL/AVLTree.hpp"

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

    return tmp.empty();
}

int FindValue(const std::string &str) {
    std::istringstream iss(str);
    std::string tmp;
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

    AVLTree<int> avlTree;

    srand(time(0));

    while (getline(fileIn, line)) {
        if (line.find("delete") == 0) {
            if (LineIsOk(line, "delete")) {
                avlTree.Delete(FindValue(line));
            } else {
                fileOut << "error" << std::endl;
            }
        }
        if (line == "print") {
//            std::string buffer;
            avlTree.PrintInOrderTraversal(fileOut);
            fileOut << std::endl;
        }
        if (line.find("add") == 0) {
            if (LineIsOk(line, "add") != 0) {
                avlTree.Insert(FindValue(line));
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

    fileIn.close();
    fileOut.close();

    if (FileIsEqual(argv[2], argv[3])) {
        std::cout << "Correct" << std::endl;
    } else {
        std::cout << "Not correct" << std::endl;
    }


//    std::string line = "delete";
//    std::string line2 = "delete 13";
//    std::string line3 = "add 3";
//    std::string line4 = "add";
//
//    std::cout << LineIsOk(line, "delete") << std::endl;
//    std::cout << LineIsOk(line2, "delete") << std::endl;
//    std::cout << LineIsOk(line3, "add") << std::endl;
//    std::cout << LineIsOk(line4, "add") << std::endl;

    return 0;

}
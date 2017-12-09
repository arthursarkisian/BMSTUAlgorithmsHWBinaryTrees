#include <iostream>
//#include "AA/AATree.hpp"
#include "AVL/AVLTree.hpp"

int main() {
//    AATree<int> aaTree;
//    aaTree.Insert(3);
//    aaTree.Insert(43);
//    aaTree.Insert(146);
//    aaTree.Insert(5);
//    aaTree.Insert(50);
//    aaTree.Print(std::cout);
//    std::cout << "Min value: " << aaTree.Min() << std::endl;
//    std::cout << "Max value: " << aaTree.Max() << std::endl;
//    aaTree.Delete(43);
//    aaTree.Print(std::cout);

    AVLTree<int> avl;
    avl.Insert(5);
    avl.Insert(4);
    avl.Insert(8);
    avl.Insert(11);
    avl.Insert(15);
    avl.Insert(3);
    avl.Insert(2);
    avl.PrintInOrderTraversal(std::cout);
    avl.Delete(11);
    std::cout << std::endl;
    avl.PrintInOrderTraversal(std::cout);
    std::cout << std::endl;
    std::cout << "Min value: " << avl.Min();
    std::cout << std::endl;
    std::cout << "Max value: " << avl.Max();
    std::cout << std::endl;

    return 0;
}
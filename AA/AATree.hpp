//#include "AATree.hpp"
#include <iostream>
#include <fstream>

template <class T>
struct AANode {
    int count, level;
    T key;
    AANode *right;
    AANode *left;
    AANode *parent;
};

template <class T>
class AATree {
public:
    AATree();
    ~AATree();

    T Insert(T);
    bool Delete(T);

    T Min();
    T Max();
    bool Search(T value);
    void PrintInOrderTraversal(std::ostream &outputstream);
private:
    AANode<T> *root;

    void DeallocMemory(AANode<T> *N);
    void Skew(AANode<T> *);
    void Rebal(AANode<T> *);
    bool Split(AANode<T> *);
    void PrintInOrderTraversalHelper(std::ostream &, AANode<T> *);
    AANode<T> *InsertHelper(AANode<T> *, AANode<T> *);
    AANode<T> *SearchHelper(AANode<T> *, T);
    bool DeleteHelper(AANode<T> *, AANode<T> *, T);
};

template <class T>
AATree<T>::AATree(){
    root = new AANode<T>;
    root = nullptr;
}

template <class T>
void AATree<T>::DeallocMemory(AANode<T> *N) {
    if (N == nullptr) {
        return;
    }
    DeallocMemory(N->left);
    DeallocMemory(N->right);
    delete N;
}

template <class T>
AATree<T>::~AATree() {
    DeallocMemory(root);
}

template <class T>
AANode<T> *AATree<T>::InsertHelper(AANode<T> *temp, AANode<T> *ins) {
    if (root == nullptr) {
        ins->count = 1;
        ins->parent = nullptr;
        ins->left = nullptr;
        ins->right = nullptr;
        root = ins;

        return root;
    }
    if (ins->key < temp->key) {
        if (temp->left) {
            return InsertHelper(temp->left, ins);
        }
        temp->left = ins;
        ins->parent = temp;
        ins->count = 1;
        Rebal(ins);

        return ins;
    }
    if (ins->key > temp->key) {
        if (temp->right) {
            return InsertHelper(temp->right, ins);
        }
        temp->right = ins;
        ins->parent = temp;
        ins->count = 1;
        Rebal(ins);

        return ins;
    }
    temp->count++;

    delete ins;
    return temp;
}

template <class T>
T AATree<T>::Insert(T value) {
    AANode<T> *temp = new AANode<T>;
    temp->key = value;
    temp->level = 1;
    temp->count = 0;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = nullptr;
    temp = InsertHelper(root, temp);
    return temp->count;
}

template <class T>
bool AATree<T>::DeleteHelper(AANode<T> *parent, AANode<T> *current, T value) {
    if (!current) {
        return false;
    }
    if (current->key == value) {
        if (current->left == nullptr || current->right == nullptr) {
            AANode<T>* temp = current->left;
            if (current->right) {
                temp = current->right;
            }
            if (parent) {
                if (parent->left == current) {
                    parent->left = temp;
                } else {
                    parent->right = temp;
                }
            } else {
                root = temp;
            }
        } else {
            AANode<T>* validSubs = current->right;
            while (validSubs->left) {
                validSubs = validSubs->left;
            }
            T temp = current->key;
            current->key = validSubs->key;
            validSubs->key = temp;
            return DeleteHelper(current, current->right, temp);
        }
        delete current;
        return true;
    }
    return DeleteHelper(current, current->left, value) ||
           DeleteHelper(current, current->right, value);
}

template <class T>
bool AATree<T>::Delete(T value) {
    return this->DeleteHelper(nullptr, root, value);
}

template <class T>
void AATree<T>::Skew(AANode<T> *temp)
{
    AANode<T> *ptr = temp->left;
    if (temp->parent->left == temp)
        temp->parent->left = ptr;
    else
        temp->parent->right = ptr;
    ptr->parent = temp->parent;
    temp->parent = ptr;
    temp->left = ptr->right;
    if (temp->left != nullptr)
        temp->left->parent = temp;
    ptr->right = temp;
    temp->level = (temp->left ? temp->left->level + 1 : 1);
}

template <class T>
bool AATree<T>::Split(AANode<T> *temp)
{
    AANode<T>* ptr = temp->right;
    if (ptr && ptr->right && (ptr->right->level == temp->level)) {
        if (temp->parent->left == temp) {
            temp->parent->left = ptr;
        }
        else {
            temp->parent->right = ptr;
        }
        ptr->parent = temp->parent;
        temp->parent = ptr;
        temp->right = ptr->left;
        if (temp->right != nullptr) {
            temp->right->parent = temp;
        }
        ptr->left = temp;
        ptr->level = temp->level + 1;
        return true;
    }
    return false;
}

template <class T>
void AATree<T>::Rebal(AANode<T> *temp) {
    temp->left = nullptr;
    temp->right = nullptr;
    temp->level = 1;
    for (temp = temp->parent; temp != root; temp = temp->parent) {
        if (temp->level != (temp->left ? temp->left->level + 1 : 1 )) {
            Skew(temp);
            if (temp->right == nullptr) {
                temp = temp->parent;
            }
            else if (temp->level != temp->right->level) {
                temp = temp->parent;
            }
        }
        if (temp->parent != root) {
            if (!Split(temp->parent)) {
                break;
            }
        }
    }
}

template <class T>
void AATree<T>::PrintInOrderTraversalHelper(std::ostream &outputstream, AANode<T> *temp) {
    if (!temp) {
        return;
    }
    PrintInOrderTraversalHelper(outputstream, temp->left);
    outputstream << temp->key << " ";
    PrintInOrderTraversalHelper(outputstream, temp->right);
}

template <class T>
void AATree<T>::PrintInOrderTraversal(std::ostream &outputstream) {
    PrintInOrderTraversalHelper(outputstream, root);
}

template <class T>
T AATree<T>::Min() {
    AANode<T> *N = root;
    while (N->left != nullptr) {
        N = N->left;
    }
    return N->key;
}

template <class T>
T AATree<T>::Max() {
    AANode<T> *N = root;
    while (N->right != nullptr) {
        N = N->right;
    }
    return N->key;
}

template <class T>
AANode<T> *AATree<T>::SearchHelper(AANode<T> *temp, T value) {
    if (temp == nullptr) {
        return nullptr;
    }

    if (value == temp->key) {
        return temp;
    }
    else if (value < temp->key) {
        return SearchHelper(temp->left, value);
    }
    else if (value > temp->key) {
        return SearchHelper(temp->right, value);
    } else {
        return nullptr;
    }
}

template <class T>
bool AATree<T>::Search(T value) {
    return SearchHelper(root, value) != nullptr;
}

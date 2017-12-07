#include <iostream>
#include <fstream>

template <class T>
struct Node {
    int count, level;
    T key;
    Node *right;
    Node *left;
    Node *parent;
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
    void Print();

    Node<T> *Search(Node<T> *, T);

private:
    Node<T> *root;

    void DeallocMemory(Node<T> *N);
    void Skew(Node<T> *);
    void Rebal(Node<T> *);
    bool Split(Node<T> *);
    void PrintHelper(Node<T> *);
    Node<T> *InsertHelper(Node<T> *, Node<T> *);
    bool DeleteHelper(Node<T> *, Node<T> *, T);
};

template <class T>
AATree<T>::AATree(){
    root = new Node<T>;
    root = nullptr;
}

template <class T>
void AATree<T>::DeallocMemory(Node<T> *N) {
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
Node<T> *AATree<T>::InsertHelper(Node<T> *temp, Node<T> *ins) {
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
    Node<T> *temp = new Node<T>;
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
bool AATree<T>::DeleteHelper(Node<T> *parent, Node<T> *current, T value) {
    if (!current) {
        return false;
    }
    if (current->key == value) {
        if (current->left == nullptr || current->right == nullptr) {
            Node<T>* temp = current->left;
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
            Node<T>* validSubs = current->right;
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
void AATree<T>::Skew(Node<T> *temp)
{
    Node<T> *ptr = temp->left;
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
bool AATree<T>::Split(Node<T> *temp)
{
    Node<T>* ptr = temp->right;
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
void AATree<T>::Rebal(Node<T> *temp) {
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
void AATree<T>::PrintHelper(Node<T> *temp) {
    if (!temp) {
        return;
    }
    PrintHelper(temp->left);
//    std::cout <<"Value: "<<temp->key << "  Count:" << temp->count;
//    std::cout<<"  Level: "<<temp->level<<std::endl;
    std::cout << temp->key << " ";
    PrintHelper(temp->right);
}

template <class T>
void AATree<T>::Print() {
    PrintHelper(root);
    std::cout << std::endl;
}

template <class T>
T AATree<T>::Min() {
    Node<T> *N = root;
    while (N->left != nullptr) {
        N = N->left;
    }
    return N->key;
}

template <class T>
T AATree<T>::Max() {
    Node<T> *N = root;
    while (N->right != nullptr) {
        N = N->right;
    }
    return N->key;
}

template <class T>
Node<T> *AATree<T>::Search(Node<T> *temp, T value) {
    if (temp == nullptr) {
        return temp;
    }

    if (value == temp->key) {
        return temp;
    }
    else if (value < temp->key) {
        return Search(temp->left, value);
    }
    else if (value > temp->key) {
        return Search(temp->right, value);
    } else {
        return nullptr;
    }
}

int main() {
    AATree<int> aaTree;
    aaTree.Insert(3);
    aaTree.Insert(43);
    aaTree.Insert(146);
    aaTree.Insert(5);
    aaTree.Insert(50);
    aaTree.Print();
    std::cout << "Min value: " << aaTree.Min() << std::endl;
    std::cout << "Max value: " << aaTree.Max() << std::endl;
    aaTree.Delete(43);
    aaTree.Print();
    return 0;
}
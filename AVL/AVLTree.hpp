#include<iostream>

template<class T>
struct AVLNode {
    T value;
    int height;
    AVLNode *left;
    AVLNode *right;
};

template<class T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    bool Insert(T value);
    bool Delete(T value);

    T Max();
    T Min();

    bool Search(T value);

    void PrintInOrderTraversal(std::ostream &);
    void PrintPreOrderTraversal(std::ostream &);
    void PrintPostOrderTraversal(std::ostream &);

private:
    AVLNode<T> *root;
    AVLNode<T> *NIL;

    void GetHeight(AVLNode<T> *N);

    AVLNode<T>* SearchHelper(AVLNode<T> *temp, T value);
    AVLNode<T>* InsertHelper(AVLNode<T> *temp, T value);
    AVLNode<T>* DeleteHelper(AVLNode<T> *temp, T value);
    AVLNode<T>* RotateLeft(AVLNode<T> *temp);
    AVLNode<T>* RotateRight(AVLNode<T> *temp);
    AVLNode<T>* Balance(AVLNode<T> *temp);

    void PrintInOrderTraversalHelper(std::ostream &, AVLNode<T> *temp);
    void PrintPreOrderTraversalHelper(std::ostream &, AVLNode<T> *temp);
    void PrintPostOrderTraversalHelper(std::ostream &, AVLNode<T> *temp);

    void DeallocMemory(AVLNode<T> *temp);
};

template<typename T>
AVLTree<T>::AVLTree() {
    root = NIL = new AVLNode<T>;
    NIL->height = 0;
    NIL->left = NIL->right = nullptr;
}

template<typename T>
AVLTree<T>::~AVLTree() {
    DeallocMemory(root);
}

template<typename T>
AVLNode<T>* AVLTree<T>::SearchHelper(AVLNode<T> *temp, T value) {
    if (temp == NIL) {
        return nullptr;
    }

    if (temp->value == value) {
        return temp;
    }

    if (value < temp->value) {
        return SearchHelper(temp->left, value);
    } else {
        return SearchHelper(temp->right, value);
    }
}

template<typename T>
bool AVLTree<T>::Search(T value) {
    return SearchHelper(root, value) != nullptr;
}

template<typename T>
bool AVLTree<T>::Insert(T value) {
    root = InsertHelper(root, value);
    return true;
}

template<typename T>
bool AVLTree<T>::Delete(T value) {
    if (Search(value)) {
        root = DeleteHelper(root, value);
        return true;
    }
    return false;
}

template<typename T>
T AVLTree<T>::Max() {
    AVLNode<T> *N = root;
    while (N->right != NIL) {
        N = N->right;
    }
    return N->value;
}

template<typename T>
T AVLTree<T>::Min() {
    AVLNode<T> *N = root;
    while (N->left != NIL) N = N->left;
    return N->value;
}

template<typename T>
void AVLTree<T>::PrintInOrderTraversal(std::ostream &outputstream) {
    PrintInOrderTraversalHelper(outputstream, root);
}

template<typename T>
void AVLTree<T>::PrintPreOrderTraversal(std::ostream &outputstream) {
    PrintPreOrderTraversalHelper(outputstream, root);
}

template<typename T>
void AVLTree<T>::PrintPostOrderTraversal(std::ostream &outputstream) {
    PrintPostOrderTraversalHelper(outputstream, root);
}

template<typename T>
void AVLTree<T>::GetHeight(AVLNode<T> *N) {
    N->height = 1 + N->left->height > N->right->height ? N->left->height : N->right->height;
}

template<typename T>
AVLNode<T> *AVLTree<T>::RotateLeft(AVLNode<T> *temp) {
    AVLNode<T> *t = temp->left;
    temp->left = t->right;
    t->right = temp;
    GetHeight(temp);
    GetHeight(t);

    return t;
}

template<typename T>
AVLNode<T> *AVLTree<T>::RotateRight(AVLNode<T> *temp) {
    AVLNode<T> *N = temp->right;
    temp->right = N->left;
    N->left = temp;
    GetHeight(temp);
    GetHeight(N);

    return N;
}

template<typename T>
AVLNode<T> *AVLTree<T>::InsertHelper(AVLNode<T> *temp, T value) {
    if (temp == NIL) {
        temp = new AVLNode<T>;
        temp->value = value;
        temp->left = temp->right = NIL;
        temp->height = 1;

        return temp;
    }

    if (value <= temp->value) {
        temp->left = InsertHelper(temp->left, value);
    } else {
        temp->right = InsertHelper(temp->right, value);
    }

    return Balance(temp);
}

template<typename T>
AVLNode<T> *AVLTree<T>::DeleteHelper(AVLNode<T> *temp, T value) {
    AVLNode<T> *t;
    if (temp == NIL) {
        return temp;
    }
    if (temp->value == value) {
        if (temp->left == NIL || temp->right == NIL) {
            if (temp->left == NIL) {
                t = temp->right;
            } else {
                t = temp->left;
            }
            delete temp;
            return t;
        } else {
            for (t = temp->right; t->left != NIL; t = t->left);
            temp->value = t->value;
            temp->right = DeleteHelper(temp->right, t->value);
            return Balance(temp);
        }
    }

    if (value < temp->value) {
        temp->left = DeleteHelper(temp->left, value);
    } else {
        temp->right = DeleteHelper(temp->right, value);
    }

    return Balance(temp);
}

template<typename T>
AVLNode<T> *AVLTree<T>::Balance(AVLNode<T> *temp) {
    GetHeight(temp);

    if (temp->left->height > temp->right->height + 1) {
        if (temp->left->right->height > temp->left->left->height) {
            temp->left = RotateRight(temp->left);
        }
        temp = RotateLeft(temp);
    }
    else if (temp->right->height > temp->left->height + 1) {
        if (temp->right->left->height > temp->right->right->height) {
            temp->right = RotateLeft(temp->right);
        }
        temp = RotateRight(temp);
    }

    return temp;
}

template<typename T>
void AVLTree<T>::PrintInOrderTraversalHelper(std::ostream &outputstream, AVLNode<T> *temp) {
    if (temp == NIL) {
        return;
    }
    PrintInOrderTraversalHelper(outputstream, temp->left);
    outputstream << temp->value << " ";
    PrintInOrderTraversalHelper(outputstream, temp->right);
}

template<typename T>
void AVLTree<T>::PrintPreOrderTraversalHelper(std::ostream &outputstream, AVLNode<T> *temp) {
    if (temp == NIL) {
        return;
    }
    outputstream << temp->value << " ";
    PrintPreOrderTraversalHelper(outputstream, temp->left);
    PrintPreOrderTraversalHelper(outputstream, temp->right);
}

template<typename T>
void AVLTree<T>::PrintPostOrderTraversalHelper(std::ostream &outputstream, AVLNode<T> *temp) {
    if (temp == NIL) {
        return;
    }
    PrintPostOrderTraversalHelper(outputstream, temp->left);
    PrintPostOrderTraversalHelper(outputstream, temp->right);
    outputstream << temp->value << " ";
}

template<typename T>
void AVLTree<T>::DeallocMemory(AVLNode<T> *temp) {
    if (temp == NIL) {
        return;
    }
    DeallocMemory(temp->left);
    DeallocMemory(temp->right);
    delete temp;
}
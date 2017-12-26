#include<iostream>

template<class T>
struct AVLNode {
    T key;
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

    bool Insert(T, T);
    bool Delete(T key);

    T Max();
    T Min();

    T Search(T key);

    void PrintInOrderTraversal(std::ostream &);
    void PrintPreOrderTraversal(std::ostream &);
    void PrintPostOrderTraversal(std::ostream &);

private:
    AVLNode<T> *root;
    AVLNode<T> *NIL;

    void GetHeight(AVLNode<T> *N);

    T SearchHelper(AVLNode<T> *temp, T key);
    AVLNode<T>* Has(AVLNode<T> *temp, T key);
    AVLNode<T>* InsertHelper(AVLNode<T> *temp, T key, T value);
    AVLNode<T>* DeleteHelper(AVLNode<T> *temp, T key);
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
T AVLTree<T>::SearchHelper(AVLNode<T> *temp, T key) {
    if (temp == NIL) {
        return 0;
    }

    if (temp->key == key) {
        return temp->value;
    }

    if (key < temp->key) {
        return SearchHelper(temp->left, key);
    } else {
        return SearchHelper(temp->right, key);
    }
}

template<typename T>
T AVLTree<T>::Search(T key) {
    return SearchHelper(root, key);
}

template<typename T>
bool AVLTree<T>::Delete(T key) {
    if (Has(root, key)) {
        root = DeleteHelper(root, key);
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
AVLNode<T> *AVLTree<T>::InsertHelper(AVLNode<T> *temp, T key, T value) {
    if (temp == NIL) {
        temp = new AVLNode<T>;
        temp->key = key;
        temp->value = value;
        temp->left = temp->right = NIL;
        temp->height = 1;

        return temp;
    }

    if (key <= temp->key) {
        temp->left = InsertHelper(temp->left, key, value);
    } else {
        temp->right = InsertHelper(temp->right, key, value);
    }

    return Balance(temp);
}

template<typename T>
bool AVLTree<T>::Insert(T key, T value) {
    root = InsertHelper(root, key, value);
    return true;
}

template<typename T>
AVLNode<T> *AVLTree<T>::DeleteHelper(AVLNode<T> *temp, T key) {
    AVLNode<T> *t;
    if (temp == NIL) {
        return temp;
    }
    if (temp->key == key) {
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
            temp->key = t->key;
            temp->right = DeleteHelper(temp->right, t->key);
            return Balance(temp);
        }
    }

    if (key < temp->key) {
        temp->left = DeleteHelper(temp->left, key);
    } else {
        temp->right = DeleteHelper(temp->right, key);
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

template<typename T>
AVLNode<T> *AVLTree<T>::Has(AVLNode<T> *temp, T key) {
    if (temp == NIL) {
        return nullptr;
    }

    if (temp->key == key) {
        return temp;
    }

    if (key < temp->key) {
        return SearchHelper(temp->left, key);
    } else {
        return SearchHelper(temp->right, key);
    }
}

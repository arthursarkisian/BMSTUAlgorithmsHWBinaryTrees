#include<iostream>

template<typename T>
struct AVLNode {
    T key;
    T value;
    int height;
    AVLNode *left;
    AVLNode *right;
};

template<typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void Insert(T, T);
    bool Delete(T);
    T Search(T);

    T Min();
    T Max();

    void PrintInOrderTraversal(std::ostream &);
    void PrintPreOrderTraversal(std::ostream &);
    void PrintPostOrderTraversal(std::ostream &);

    int GetCountOfRatates();

private:
    AVLNode <T> *R;
    AVLNode <T> *NIL;

    int countOfRotates;

    AVLNode<T>* InsertHelper(AVLNode<T> *, T, T);
    AVLNode<T>* DeleteHelper(AVLNode<T> *, T);
    T SearchHelper(AVLNode<T> *, T);

    void GetHeight(AVLNode<T> *);
    AVLNode<T>* RotateLeft(AVLNode<T> *);
    AVLNode<T>* RotateRight(AVLNode<T> *);
    AVLNode<T>* Balance(AVLNode<T> *);

    void PrintInOrderTraversalHelper(std::ostream &, AVLNode<T> *);
    void PrintPreOrderTraversalHelper(std::ostream &, AVLNode<T> *);
    void PrintPostOrderTraversalHelper(std::ostream &, AVLNode<T> *);

    void ClearTree(AVLNode<T> *N);
};

template <typename T>
AVLTree<T>::AVLTree() {
    R = NIL = new AVLNode<T>;
    NIL->height = 0;
    NIL->left = NIL->right = nullptr;
    countOfRotates = 0;
}

template <typename T>
AVLTree<T>::~AVLTree() {
    ClearTree(R);
}

template <typename T>
void AVLTree<T>::GetHeight(AVLNode<T> *N) {
    N->height = 1 + (N->left->height > N->right->height ? N->left->height : N->right->height);
}

template <typename T>
AVLNode<T> *AVLTree<T>::RotateLeft(AVLNode<T> *N) {
//    std::cout << "RotateLeft" << std::endl;
    countOfRotates++;
    AVLNode<T> *t = N->left;
    N->left = t->right;
    t->right = N;
    GetHeight(N);
    GetHeight(t);

    return t;
}

template <typename T>
AVLNode<T> *AVLTree<T>::RotateRight(AVLNode<T> *N) {
    countOfRotates++;
//    std::cout << "RotateRight" << std::endl;
    AVLNode<T> *t = N->right;
    N->right = t->left;
    t->left = N;
    GetHeight(N);
    GetHeight(t);

    return t;
}

template <typename T>
AVLNode<T> *AVLTree<T>::Balance(AVLNode<T> *N) {
    GetHeight(N);

    if (N->left->height > N->right->height + 1) {
        if (N->left->right->height > N->left->left->height)
            N->left = RotateRight(N->left);
        N = RotateLeft(N);
    }
    else
    if (N->right->height > N->left->height + 1) {
        if (N->right->left->height > N->right->right->height)
            N->right = RotateLeft(N->right);
        N = RotateRight(N);
    }

    return N;
}

template <typename T>
void AVLTree<T>::Insert(T key, T value) {
    R = InsertHelper(R, key, value);
}

template <typename T>
AVLNode<T> *AVLTree<T>::InsertHelper(AVLNode<T> *N, T key, T value) {
    if (N == NIL) {
        N = new AVLNode<T>;
        N->key = key;
        N->value = value;
        N->left = N->right = NIL;
        N->height = 1;

        return N;
    }

    if (key <= N->key) {
        N->left = InsertHelper(N->left, key, value);
    }
    else {
        N->right = InsertHelper(N->right, key, value);
    }

    return Balance(N);
}

template <typename T>
bool AVLTree<T>::Delete(T key) {
    R = DeleteHelper(R, key);
    if (R != NIL) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
AVLNode<T> *AVLTree<T>::DeleteHelper(AVLNode<T> *N, T key) {
    AVLNode<T> *t;
    if (N == NIL) {
        return N;
    }
    if (N->key == key) {
        if (N->left == NIL || N->right == NIL) {
            if (N->left == NIL) {
                t = N->right;
            } else {
                t = N->left;
            }
            delete N;
            return t;
        } else {
            for (t = N->right; t->left != NIL; t = t->left);
            N->key = t->key;
            N->right = DeleteHelper(N->right, t->key);
            return Balance(N);
        }
    }

    if (key < N->key) {
        N->left = DeleteHelper(N->left, key);
    } else {
        N->right = DeleteHelper(N->right, key);
    }

    return Balance(N);
}

template <typename T>
T AVLTree<T>::Search(T key) {
    return SearchHelper(R, key);
}

template <typename T>
T AVLTree<T>::SearchHelper(AVLNode<T> *N, T key) {
    if (N == NIL) {
        return -1;
    }

    if (N->key == key) {
        return N->value;
    }

    if (key < N->key) {
        return SearchHelper(N->left, key);
    }
    else {
        return SearchHelper(N->right, key);
    }
}

template <typename T>
T AVLTree<T>::Min() {
    AVLNode<T> *N = R;
    while (N->left != NIL) N = N->left;
    return N->key;
}

template <typename T>
T AVLTree<T>::Max() {
    AVLNode<T> *N = R;
    while (N->right != NIL) N = N->right;
    return N->key;
}

template <typename T>
void AVLTree<T>::PrintInOrderTraversal(std::ostream &outputstream) {
    PrintInOrderTraversalHelper(outputstream, R);
}

template <typename T>
void AVLTree<T>::PrintInOrderTraversalHelper(std::ostream &outputstream, AVLNode<T> *N) {
    if (N == NIL) {
        return;
    }
    PrintInOrderTraversalHelper(outputstream, N->left);
    outputstream << N->value << " ";
    PrintInOrderTraversalHelper(outputstream, N->right);
}

template <typename T>
void AVLTree<T>::PrintPreOrderTraversal(std::ostream &outputstream) {
    PrintPreOrderTraversalHelper(outputstream, R);
}

template <typename T>
void AVLTree<T>::PrintPreOrderTraversalHelper(std::ostream &outputstream, AVLNode<T> *N) {
    if (N == NIL) {
        return;
    }
    outputstream << N->value << " ";
    PrintPreOrderTraversalHelper(outputstream, N->left);
    PrintPreOrderTraversalHelper(outputstream, N->right);
}

template <typename T>
void AVLTree<T>::PrintPostOrderTraversal(std::ostream &outputstream) {
    PrintPostOrderTraversalHelper(outputstream, R);
}

template <typename T>
void AVLTree<T>::PrintPostOrderTraversalHelper(std::ostream &outputstream, AVLNode<T> *N) {
    if (N == NIL) {
        return;
    }
    PrintPostOrderTraversalHelper(outputstream, N->left);
    PrintPostOrderTraversalHelper(outputstream, N->right);
    outputstream << N->value << " ";
}

template <typename T>
void AVLTree<T>::ClearTree(AVLNode<T> *N) {
    if (N == NIL) {
        return;
    }
    ClearTree(N->left);
    ClearTree(N->right);
    delete N;
}

template <typename T>
int AVLTree<T>::GetCountOfRatates() {
    return countOfRotates;
}

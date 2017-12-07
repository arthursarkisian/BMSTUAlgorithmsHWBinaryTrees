#include<iostream>

template<class T>
struct Node {
    T value;
    int height;
    Node *left;
    Node *right;
};

template<class T>
class AVL {
public:
    AVL();
    ~AVL();

    void Insert(T value);
    void Delete(T value);

    T Max();
    T Min();

    Node<T>* Search(T value);

    void PrintInOrderTraversal(std::ostream &outputstream);
    void PrintPreOrderTraversal(std::ostream &outputstream);
    void PrintPostOrderTraversal(std::ostream &outputstream);

private:
    Node<T> *root;
    Node<T> *NIL;

    void GetHeight(Node<T> *N);

    Node<T>* SearchHelper(Node<T> *temp, T value);
    Node<T>* InsertHelper(Node<T> *temp, T value);
    Node<T>* DeleteHelper(Node<T> *temp, T value);
    Node<T>* RotateLeft(Node<T> *temp);
    Node<T>* RotateRight(Node<T> *temp);
    Node<T>* Balance(Node<T> *temp);

    void PrintInOrderTraversalHelper(std::ostream &outputstream, Node<T> *temp);
    void PrintPreOrderTraversalHelper(std::ostream &outputstream, Node<T> *temp);
    void PrintPostOrderTraversalHelper(std::ostream &outputstream, Node<T> *temp);

    void DeallocMemory(Node<T> *temp);
};

template<typename T>
AVL<T>::AVL() {
    root = NIL = new Node<T>;
    NIL->height = 0;
    NIL->left = NIL->right = nullptr;
}

template<typename T>
AVL<T>::~AVL() {
    DeallocMemory(root);
}

template<typename T>
Node<T>* AVL<T>::Search(T value) {
    return SearchHelper(root, value);
}

template<typename T>
void AVL<T>::Insert(T value) {
    root = InsertHelper(root, value);
}

template<typename T>
void AVL<T>::Delete(T value) {
    root = DeleteHelper(root, value);
}

template<typename T>
T AVL<T>::Max() {
    Node<T> *N = root;
    while (N->right != NIL) {
        N = N->right;
    }
    return N->value;
}

template<typename T>
T AVL<T>::Min() {
    Node<T> *N = root;
    while (N->left != NIL) N = N->left;
    return N->value;
}

template<typename T>
void AVL<T>::PrintInOrderTraversal(std::ostream &outputstream) {
    PrintInOrderTraversalHelper(outputstream, root);
}

template<typename T>
void AVL<T>::PrintPreOrderTraversal(std::ostream &outputstream) {
    PrintPreOrderTraversalHelper(outputstream, root);
}

template<typename T>
void AVL<T>::PrintPostOrderTraversal(std::ostream &outputstream) {
    PrintPostOrderTraversalHelper(outputstream, root);
}

template<typename T>
Node<T>* AVL<T>::SearchHelper(Node<T> *temp, T value) {
    if (temp == NIL) {
        return false;
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
void AVL<T>::GetHeight(Node<T> *N) {
    N->height = 1 + N->left->height > N->right->height ? N->left->height : N->right->height;
}

template<typename T>
Node<T> *AVL<T>::RotateLeft(Node<T> *temp) {
    Node<T> *t = temp->left;
    temp->left = t->right;
    t->right = temp;
    GetHeight(temp);
    GetHeight(t);

    return t;
}

template<typename T>
Node<T> *AVL<T>::RotateRight(Node<T> *temp) {
    Node<T> *N = temp->right;
    temp->right = N->left;
    N->left = temp;
    GetHeight(temp);
    GetHeight(N);

    return N;
}

template<typename T>
Node<T> *AVL<T>::InsertHelper(Node<T> *temp, T value) {
    if (temp == NIL) {
        temp = new Node<T>;
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
Node<T> *AVL<T>::DeleteHelper(Node<T> *temp, T value) {
    Node<T> *t;
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
Node<T> *AVL<T>::Balance(Node<T> *temp) {
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
void AVL<T>::PrintInOrderTraversalHelper(std::ostream &outputstream, Node<T> *temp) {
    if (temp == NIL) {
        return;
    }
    PrintInOrderTraversalHelper(outputstream, temp->left);
    outputstream << temp->value << " ";
    PrintInOrderTraversalHelper(outputstream, temp->right);
}

template<typename T>
void AVL<T>::PrintPreOrderTraversalHelper(std::ostream &outputstream, Node<T> *temp) {
    if (temp == NIL) {
        return;
    }
    outputstream << temp->value << " ";
    PrintPreOrderTraversalHelper(outputstream, temp->left);
    PrintPreOrderTraversalHelper(outputstream, temp->right);
}

template<typename T>
void AVL<T>::PrintPostOrderTraversalHelper(std::ostream &outputstream, Node<T> *temp) {
    if (temp == NIL) {
        return;
    }
    PrintPostOrderTraversalHelper(outputstream, temp->left);
    PrintPostOrderTraversalHelper(outputstream, temp->right);
    outputstream << temp->value << " ";
}

template<typename T>
void AVL<T>::DeallocMemory(Node<T> *temp) {
    if (temp == NIL) {
        return;
    }
    DeallocMemory(temp->left);
    DeallocMemory(temp->right);
    delete temp;
}

int main() {
    AVL<int> avl;
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
    std::cout << "Min element: " << avl.Min();
    std::cout << std::endl;
    std::cout << "Max element: " << avl.Max();
    std::cout << std::endl;

    return 0;
}
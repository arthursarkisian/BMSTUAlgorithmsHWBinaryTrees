#include <iostream>
#include <fstream>

struct Node {
    int count, level;
    int key;
    Node *right;
    Node *left;
    Node *parent;
};

class AATree {
public:
    AATree();
    ~AATree();

    int Insert(int);
    bool Delete(int);

    int Min();
    int Max();
    void Print();

    Node *Search(Node *, int);

private:
    Node *root;
    Node *NIL;

    void DeallocMemory(Node *N);
    void Skew(Node *);
    void Rebal(Node *);
    bool Split(Node *);
    void PrintHelper(Node *);
    Node *InsertHelper(Node *, Node *);
    bool DeleteValueHelper(Node *, Node *, int);
};

AATree::AATree(){
    root = NIL = new Node;
    root = nullptr;
//    root->left = root->right = nullptr;
    NIL->left = NIL->right = nullptr;
}

void AATree::DeallocMemory(Node *N) {
    if (N == NIL) {
        return;
    }
    DeallocMemory(N->left);
    DeallocMemory(N->right);
    delete N;
}

AATree::~AATree() {
    DeallocMemory(root);
}

int AATree::Insert(int value) {
    Node *temp = new Node;
    temp->key = value;
    temp->level = 1;
    temp->count = 0;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = nullptr;
    temp = InsertHelper(root, temp);
    return temp->count;
}

Node* AATree::InsertHelper(Node *temp, Node *ins) {
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

void AATree::Skew(Node *temp)
{
    Node *ptr = temp->left;
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

bool AATree::Split(Node *temp)
{
    Node* ptr = temp->right;
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

void AATree::Rebal(Node *temp) {
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

void AATree::PrintHelper(Node *temp) {
    if (!temp) {
        return;
    }
    PrintHelper(temp->left);
    std::cout <<"Value: "<<temp->key << "  Count:" << temp->count;
    std::cout<<"  Level: "<<temp->level<<std::endl;
    PrintHelper(temp->right);
}

void AATree::Print() {
    PrintHelper(root);
}

bool AATree::DeleteValueHelper(Node *parent, Node *current, int value) {
    if (!current) {
        return false;
    }
    if (current->key == value) {
        if (current->left == nullptr || current->right == nullptr) {
            Node* temp = current->left;
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
            Node* validSubs = current->right;
            while (validSubs->left) {
                validSubs = validSubs->left;
            }
            int temp = current->key;
            current->key = validSubs->key;
            validSubs->key = temp;
            return DeleteValueHelper(current, current->right, temp);
        }
        delete current;
        return true;
    }
    return DeleteValueHelper(current, current->left, value) ||
            DeleteValueHelper(current, current->right, value);
}

bool AATree::Delete(int value) {
    return this->DeleteValueHelper(nullptr, root, value);
}

int AATree::Min() {
    Node *N = root;
    while (N->left != nullptr) {
        N = N->left;
    }
    return N->key;
}

int AATree::Max() {
    Node *N = root;
    while (N->right != nullptr) {
        N = N->right;
    }
    return N->key;
}

Node *AATree::Search(Node *temp, int value) {
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
    AATree aaTree;
    int command = 0;
    std::string str;
    int item = 0;
    std::ifstream fin ("test.txt");
    while (true) {
        std::cout<<"\n---------------------"<<std::endl;
        std::cout<<"\nOperations on AA Tree"<<std::endl;
        std::cout<<"\n---------------------"<<std::endl;
        std::cout<<"1.Insert String into the Tree"<<std::endl;
        std::cout<<"2.Print Tree Data"<<std::endl;
        std::cout<<"3.Delete value"<<std::endl;
        std::cout<<"4.Max value"<<std::endl;
        std::cout<<"5.Min value"<<std::endl;
        std::cout<<"6.Exit"<<std::endl;
        std::cout<<"Enter Your Choice: ";
        std::cin>>command;
        switch (command) {
            case 1:
                if (fin.is_open()) {
                    while (fin>>str) {
                        int value = atoi(str.c_str());
                        aaTree.Insert(value);
                    }
                    fin.close();
                }
                break;
            case 2:
                std::cout<<"Elemets of AA Tree"<<std::endl;
                aaTree.Print();
                break;
            case 3:
                std::cout<<"Value to delete: ";
                std::cin >> item;
                aaTree.Delete(item);
                break;
            case 4:
                std::cout << "Max Value: ";
                std::cout << aaTree.Max();
                break;
            case 5:
                std::cout << "Min Value: ";
                std::cout << aaTree.Min();
                break;
            case 6:
                std::cout<<"Exiting"<<std::endl;
                exit(1);
            default:
                std::cout<<"Wrong Choice"<<std::endl;
        }
    }

//    AATree aaTree;
//    aaTree.Insert();
//
//    return 0;
}
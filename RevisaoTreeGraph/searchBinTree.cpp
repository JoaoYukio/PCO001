#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node* lchild;
    Node* rchild;
    Node()
    {
        data = 0;
        lchild=nullptr;
        rchild=nullptr;
    }
    Node(int data)
    {
        this->data=data;
        lchild=nullptr;
        rchild=nullptr;
    }
};

class binTree{
    public:
        Node* root;
        binTree()
        {
            root = nullptr;
        }

        bool insert(int data);
        Node* rSearch(Node* t, int data);
        Node* Search(int data);
        void preorder(Node* t);
        void inorder(Node* t);
        void posorder(Node* t);
};

bool binTree::insert(int data)
{
    Node* t = new Node(data);
    if(root == nullptr)
    {
        root = t;
        return true;
    }
    Node* first = root;
    Node* sec = nullptr;
    while(first != nullptr)
    {
        sec = first;
        if(data < first->data)
        {
            first = first -> lchild;
        }else if(data > first->data)
        {
            first = first ->rchild;
        }else{
            cout << "Valor ja esta na BST\n";
            return false;
        }
    }
    if(data < sec->data)
    {
        sec->lchild = t;
    }else if(data > sec->data)
    {
        sec ->rchild = t;
    }else{
        cout << "Valor ja esta na BST\n";
        return false;   
    }
    return true;
}

Node* binTree::rSearch(Node* t, int data)
{
    if(t == nullptr)
    {
        return nullptr;
    }
    if(t->data == data)
    {
        cout << "Encontrei o valor " << data << "\n";
        return t;
    }
    if(data < t->data)
    {
        return rSearch(t->lchild, data);
    }
    if(data > t->data)
    {
        return rSearch(t->rchild, data);
    }
}

Node* binTree::Search(int data)
{
    Node* t = root;
    //Node* sec = nullptr;
    while(t != nullptr)
    {
        if(data == t->data)
        {
            cout << "Encontrei o valor: " << data << "\n";
            return t;
        }
        if(data < t->data)
        {
            t = t->lchild;
        }else{
            t = t->rchild;
        }
    }
    cout << "Nao encontrei o valor\n";
    return nullptr;
}

void binTree::inorder(Node* t)
{
    if(t == nullptr)
    {
        return;
    }
    inorder(t->lchild);
    cout << t->data << " ";
    inorder(t->rchild);
}

int main()
{
    binTree myTree = binTree();
    myTree.insert(10);
    myTree.insert(5);
    myTree.insert(7);
    myTree.insert(12);
    myTree.insert(15);

    myTree.inorder(myTree.root);

    cout << "\nPesquisando usando rSeach\n";
    cout << myTree.rSearch(myTree.root,12)->data << "\n";
    cout << "Pesquisando usando Search\n";
    cout << myTree.Search(7)->data;

    return 0;
}
#include<iostream>

using namespace std;

class node{
    private:
    int data;
    node* left;
    node* right;
    public:
    node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
    node(int data, node* l, node* r)
    {
        this->data = data;
        this->left = l;
        this->right = r;
    }
    void setData(int data)
    {
        this->data = data;
    }
    void setRight(node* r)
    {
        this->right = r;
    }
    void setLeft(node* l)
    {
        this->left = l;
    }
    int getData(void)
    {
        return this->data;
    }
    node* getLeft(void)
    {
        return this->left;
    }
    node* getRight()
    {
        return this->right;
    }
};

class BST{
    private:
        int altura;
    public:
        node* root;
        BST(node* r)
        {
            this->root = r;
            this->altura = 0;
        }
        void preorder(node* r)
        {
            if(r != nullptr)
            {
                cout << r->getData() << " ";
                preorder(r->getLeft());
                preorder(r->getRight());
            }
        }
        void inorder(node* r)
        {
            if(r != nullptr)
            {
                inorder(r->getLeft());
                cout << r->getData() << " ";
                inorder(r->getRight());
            }
        }
        void posorder(node* r)
        {
            if(r != nullptr)
            {
                posorder(r->getLeft());
                posorder(r->getRight());
                cout << r->getData() << " ";
            }
        }
        void insert(node* r,int data);
        void remove(int data);
        node* search(int data);
        int getAltura();
        void printTree();
};

void BST::insert(node* r,int data)
{
    if(r == nullptr)
    {
        r = new node(data);
    }else if(r->getData() > data)
    {
        insert(r->getLeft(),data);
    }
    else
    {
        insert(r->getRight(),data);
    }
}

void BST::remove(int data)
{
    node* aux = this->root;
    if(aux != nullptr)
    {
        if(data < aux->getData())
        {
            BST* left = new BST(aux->getLeft());
            left->remove(data);
        }
        else if(data > aux->getData())
        {
            BST* right = new BST(aux->getRight());
            right->remove(data);
        }
        else
        {
            if(aux->getLeft() == nullptr && aux->getRight() == nullptr)
            {
                this->root = nullptr;
            }
            else if(aux->getLeft() == nullptr)
            {
                this->root = aux->getRight();
            }
            else if(aux->getRight() == nullptr)
            {
                this->root = aux->getLeft();
            }
            else
            {
                node* aux2 = aux->getRight();
                while(aux2->getLeft() != nullptr)
                {
                    aux2 = aux2->getLeft();
                }
                aux->setData(aux2->getData());
                BST* right = new BST(aux->getRight());
                right->remove(aux2->getData());
            }
        }
    }
}

node* BST::search(int data)
{
    node* aux = this->root;
    if(aux != nullptr)
    {
        if(data < aux->getData())
        {
            BST* left = new BST(aux->getLeft());
            return left->search(data);
        }
        else if(data > aux->getData())
        {
            BST* right = new BST(aux->getRight());
            return right->search(data);
        }
        else
        {
            return aux;
        }
    }
    return nullptr;
}

int BST::getAltura()
{
    node* aux = this->root;
    if(aux != nullptr)
    {
        BST* left = new BST(aux->getLeft());
        BST* right = new BST(aux->getRight());
        int leftAltura = left->getAltura();
        int rightAltura = right->getAltura();
        if(leftAltura > rightAltura)
        {
            return leftAltura + 1;
        }
        else
        {
            return rightAltura + 1;
        }
    }
    return 0;
}

void BST::printTree()
{
    node* aux = this->root;
    if(aux != nullptr)
    {
        BST* left = new BST(aux->getLeft());
        left->printTree();
        cout << aux->getData() << " ";
        BST* right = new BST(aux->getRight());
        right->printTree();
    }
}

int main()
{
    node root = node(10);
    BST* tree = new BST(&root);

    tree->insert(tree->root,5);
    tree->insert(tree->root,15);
    tree->insert(tree->root,3);
    tree->insert(tree->root,7);
    tree->insert(tree->root,12);
    tree->insert(tree->root,17);
    tree->insert(tree->root,1);
    tree->insert(tree->root,4);
    tree->insert(tree->root,6);
    tree->insert(tree->root,8);

    cout << "Preorder: ";
    tree->preorder(tree->root);

    cout << endl << "Inorder: ";
    tree->inorder(tree->root);

    cout << endl << "Posorder: ";
    tree->posorder(tree->root);

    cout << endl << "Altura: " << tree->getAltura();

    cout << endl << "Busca: " << tree->search(4)->getData();

    cout << endl << "Remove: ";
    tree->remove(4);
    
    cout << endl << "Inorder: ";
    tree->inorder(tree->root);

    cout << endl << "Print: ";
    tree->printTree();


    return 0;
}
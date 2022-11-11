#include<iostream>
#include<queue>

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
    public:
        node* root;
        BST(node* r)
        {
            this->root = r;
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
        void remove(node* r,int data);
        node* search(node* r, int data);
        int Altura(node* r);
        void printTree();
};

void BST::insert(node* r, int data)
{
    if(data < r->getData())
    {
        if(r->getLeft() == nullptr)
        {
            r->setLeft(new node(data));
        }
        else
        {
            insert(r->getLeft(), data);
        }
    }
    else
    {
        if(r->getRight() == nullptr)
        {
            r->setRight(new node(data));
        }
        else
        {
            insert(r->getRight(), data);
        }
    }
}

// Remove um nó da árvore de forma recursiva
// ARRUMAR ISSO AQUI
void BST::remove(node* r, int data)
{
    if(r != nullptr)
    {
        if(data < r->getData())
        {
            remove(r->getLeft(), data);
        }
        else if(data > r->getData())
        {
            remove(r->getRight(), data);
        }
        else
        {
            if(r->getLeft() == nullptr && r->getRight() == nullptr)
            {
                delete r;
                r = nullptr;
            }
            else if(r->getLeft() == nullptr)
            {
                node* aux = r;
                r = r->getRight();
                delete aux;
            }
            else if(r->getRight() == nullptr)
            {
                node* aux = r;
                r = r->getLeft();
                delete aux;
            }
            else
            {
                node* aux = r->getRight();
                while(aux->getLeft() != nullptr)
                {
                    aux = aux->getLeft();
                }
                r->setData(aux->getData());
                remove(r->getRight(), aux->getData());
            }
        }
    }
}

node* BST::search(node* r,int data)
{
    if(r == nullptr)return nullptr;
    if(r->getData() == data)return r;

    if(data < r->getData())
    {
        return search(r->getLeft(), data);
    }
    else
    {
        return search(r->getRight(), data);
    }
}

// Retorna a altura da árvore
int BST::Altura(node* r)
{
    if(r == nullptr)return 0;
    int altEsq = Altura(r->getLeft());
    int altDir = Altura(r->getRight());
    return max(altEsq, altDir); // + 1
}

void printBT(const std::string& prefix, node* n, bool isLeft)
{
    if( n != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << n->getData() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), n->getLeft(), true);
        printBT( prefix + (isLeft ? "│   " : "    "), n->getRight(), false);
    }
}

int main()
{
    node* root = new node(8);
    BST tree(root);

    tree.insert(root, 5);
    tree.insert(root, 10);
    tree.insert(root, 2);
    tree.insert(root, 6);
    //tree.insert(root, 9);
    tree.insert(root, 11);
    

    cout << "inorder: ";
    tree.inorder(root);
    cout << endl;

    cout << tree.Altura(tree.root) << "\n";

    printBT("", root, false);

    return 0;
}
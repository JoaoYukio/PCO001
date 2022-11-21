#include<iostream>
#include<queue>
#include<list>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    void sleepSec(int sec)
    {
        Sleep(1000*sec);
        return;
    }
#else defined(__linux__) || defined(__unix__)
    #include <chrono>
    #include <thread>
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    void sleepSec(int sec)
    {
        sleep_for(seconds(sec));
        return;
    }
#endif

using namespace std;

class node{
    public:
    int data;
    node* left;
    node* right;
    node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

class BST{
    private:
        bool rootSet;
        node* root;
    public:
        int numNodes;
        list<int> nodes;
        //int* nodes;
        BST()
        {
            this->rootSet = false;
            this->root = nullptr;
            this->numNodes = 0;
        }
        void setRoot(node* r)
        {
            this->root = r;
            numNodes++;
        }
        // pre order
        void preOrder(node* r)
        {
            if(r == nullptr)
            {
                return;
            }
            cout << r->data << " ";
            preOrder(r->left);
            preOrder(r->right);
        }
        // in order

        void inOrder(node* r)
        {
            if(r == nullptr)
            {
                return;
            }
            inOrder(r->left);
            cout << r->data << " ";
            this->nodes.push_back(r->data);
            inOrder(r->right);
        }
        // post order
        void postOrder(node* r)
        {
            if(r == nullptr)
            {
                return;
            }
            postOrder(r->left);
            postOrder(r->right);
            cout << r->data << " ";
        }
        void insert(node* r,int data);
        bool remove(node* r,int data);
        node* search(node* r, int data);
        int Altura(node* r);
        void printBT(const std::string& prefix, node* n, bool isLeft);
        void balanceTree();
        void interfaceUser();
};

void BST::balanceTree()
{
    //nodes = new int[numNodes];
    this->inOrder(this->root);
    //print the nodes list
    for(auto it = this->nodes.begin(); it != this->nodes.end(); it++)
    {
        cout << *it << " ";
    }
    auto lfront = this->nodes.begin();
    auto it = this->nodes.begin();

    advance(it, this->nodes.size()/2);

    node* newRoot = new node(*it);
    //this->setRoot(newRoot);
    int i = this->nodes.size()/2;
    while(i>0)
    {
        advance(it, i/2);
        this->insert(newRoot, *it);
        i = i/2;
    }
    i = this->nodes.size()/2;
    int size = this->nodes.size();
    while(i < size)
    {
        advance(it, i + (i/2));
        this->insert(newRoot, *it);
        i = i + (i/2);
    }
    this->root = newRoot;
}

// Insert a node recursively
void BST::insert(node* r, int data)
{
    if(r == nullptr)
    {
        r = new node(data);
        numNodes++;
        return;
    }
    if(data < r->data)
    {
        if(r->left == nullptr)
        {
            r->left = new node(data);
            numNodes++;
            return;
        }
        insert(r->left,data);
    }
    else
    {
        if(r->right == nullptr)
        {
            r->right = new node(data);
            numNodes++;
            return;
        }
        insert(r->right,data);
    }
}
//Remove a node with the given data interatively
bool BST::remove(node* r, int data)
{
    if(r == nullptr)
    {
        return false;
    }
    node* temp = r;
    node* parent = nullptr;
    while(temp != nullptr)
    {
        if(data < temp->data)
        {
            parent = temp;
            temp = temp->left;
        }
        else if(data > temp->data)
        {
            parent = temp;
            temp = temp->right;
        }
        else
        {
            if(temp->left == nullptr and temp->right == nullptr)
            {
                if(parent == nullptr)
                {
                    r = nullptr;
                }
                else if(parent->left == temp)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
                delete temp;
                return true;
            }
            else if(temp->left == nullptr and temp->right != nullptr)
            {
                if(parent == nullptr)
                {
                    r = temp->right;
                }
                else if(parent->left == temp)
                {
                    parent->left = temp->right;
                }
                else
                {
                    parent->right = temp->right;
                }
                delete temp;
                return true;
            }
            else if(temp->right == nullptr and temp->left != nullptr)
            {
                if(parent == nullptr)
                {
                    r = temp->left;
                }
                else if(parent->left == temp)
                {
                    parent->left = temp->left;
                }
                else
                {
                    parent->right = temp->left;
                }
                delete temp;
                return true;
            }
            else
            {
                node* temp2 = temp->right;
                while(temp2->left != nullptr)
                {
                    temp2 = temp2->left;
                }
                temp->data = temp2->data;
                data = temp2->data;
                parent = temp;
                temp = temp->right;
            }
        }
    }
    return false;
}


// Search for a node with the given data
// Return the node if found
// Return nullptr if not found
node* BST::search(node* r, int data)
{
    if(r == nullptr)
    {
        return nullptr;
    }
    else if(data < r->data)
    {
        return search(r->left, data);
    }
    else if(data > r->data)
    {
        return search(r->right, data);
    }
    else
    {
        return r;
    }
}

// Retorna a altura da árvore
int BST::Altura(node* r)
{
    if(r == nullptr)return 0;
    int altEsq = Altura(r->left);
    int altDir = Altura(r->right);
    return max(altEsq, altDir) + 1; // + 1
}

void BST::printBT(const std::string& prefix, node* n, bool isLeft)
{
    if( n != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__" ); 

        // print the value of the node
        std::cout << n->data << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), n->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), n->right, false);
    }
}

void clearTerminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else defined(__linux__) || defined(__unix__)
        system("clear");
    #endif
    return;
}

void BST::interfaceUser()
{
    int op;
    int val = 0;
    int tempoAmostra = 5;
    node* p = nullptr;
    //int pos;
    for(;;)
    {
        if(this->rootSet == false)
        {
            cout << "Digite o valor da raiz: ";
            cin >> val;
            this->setRoot(new node(val));
            this->rootSet = true;
        }

        clearTerminal();
        cout << "Escolha o que quer fazer: \n";
        cout << "   (1) Inserir valor\n";
        cout << "   (2) Remover valor\n";
        cout << "   (3) Buscar\n";
        cout << "   (4) Altura da arvore\n";
        cout << "   (5) Imprimir\n";
        cout << "   (6) Definir tempo de amostra da lista na funcao (3), (4) e (5)\n";
        cout << "   (7) In order\n";
        cout << "   (-1) Sair\n";

        cin >> op;

        if(op == -1)
        {
            cout << "Obrigado por usar o programa\n";
            return;
        }
        switch (op)
        {
        case 1:
            clearTerminal();
            cout << "Digite o valor que gostaria de inserir\n";
            cin >> val;
            insert(root, val);
            cout << "Altura da arvore: " << Altura(root) - 1 << '\n';
            printBT("", root, false);
            sleepSec(tempoAmostra);
            break;
        case 2:
            clearTerminal();
            cout << "Digite o valor que gostaria de remover\n";
            cin >> val;
            remove(root, val);
            cout << "Altura da arvore: " << Altura(root) - 1 << '\n';
            printBT("", root, false);
            sleepSec(tempoAmostra);
            break;
        case 3:
            clearTerminal();
            cout << "Digite o valor que gostaria de buscar\n";
            cin >> val;
            p = search(root, val);
            if(p == nullptr)
            {
                cout << "Valor não encontrado\n";
            }
            else
            {
                cout << "Valor encontrado\n";
            }
            cout << "Altura da arvore: " << Altura(root) - 1 << '\n';
            printBT("", root, false);
            sleepSec(tempoAmostra);
            break;
        case 4:
            clearTerminal();
            cout << "Altura da arvore: "<< Altura(root) - 1 << "\n";
            sleepSec(tempoAmostra);
            break;
        case 5: 
            clearTerminal();
            cout << "Imprimindo arvore:\n";
            printBT("", root, false);
            sleepSec(tempoAmostra);
            break;
        case 6:
            clearTerminal();
            cout << "Digite o tempo de amostra da lista na função (1), (2), (3), (4) e (5)\n";
            cin >> tempoAmostra;
            break;
        case 7:
            clearTerminal();
            //cout << "Digite o tempo de amostra da lista na função (3), (4) e (5)\n";
            inOrder(root);
            sleepSec(tempoAmostra);
            break;
        case 8:
            //Balance tree
            balanceTree();
            sleepSec(tempoAmostra);
            break;
        default:
            clearTerminal();
            cout << "Opcao invalida\n";
            //sleep_for(seconds(2));
            sleepSec(2);
            break;
        }
    }
}

// Tentei essa forma recursiva, mas não consegui fazer funcionar
/*bool BST::remove(node* r, int data)
{
    if(r == nullptr)
    {
        return false;
    }
    else if(data < r->data)
    {
        return remove(r->left, data);
    }
    else if(data > r->data)
    {
        return remove(r->right, data);
    }
    else
    {
        if(r->left == nullptr and r->right == nullptr)
        {
            r = nullptr;
            return true;
        }
        else if(r->left == nullptr and r->right != nullptr)
        {
            node* temp = r;
            r = r->right;
            delete temp;
            return true;
        }
        else if(r->right == nullptr and r->left != nullptr)
        {
            node* temp = r;
            r = r->left;
            delete temp;
            return true;
        }else{
            node* temp = r->right;
            while(temp->left != nullptr)
            {
                temp = temp->left;
            }
            r->data = temp->data;
            return remove(r->right, temp->data);
        }
    }
}*/

int main()
{
    BST tree;
    tree.interfaceUser();

    return 0;
}
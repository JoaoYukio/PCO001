#include<iostream>
#include<queue>

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
        bool rootSet;
        node* root;
    public:
        BST()
        {
            this->rootSet = false;
            this->root = nullptr;
        }
        void setRoot(node* r)
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
        node* remove(node* r,int data);
        node* search(node* r, int data);
        int Altura(node* r);
        void printBT(const std::string& prefix, node* n, bool isLeft);
        void interfaceUser();
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

//remove a node recursively <- have a bug if there is not a sucessor
node* BST::remove(node* r, int data)
{
    // Procura o elemento
    if(r == nullptr)
    {
        return r;
    }
    else if(data < r->getData())
    {
        r->setLeft(remove(r->getLeft(), data));
    }
    else if(data > r->getData())
    {
        r->setRight(remove(r->getRight(), data));
    }
    else
    {
        // So entra aqui caso o elemento seja encontrado
        // Caso 1: No folha
        if(r->getLeft() == nullptr && r->getRight() == nullptr)
        {
            delete r;
            r = nullptr;
        }
        // Caso 2: So tem filho a direita
        else if(r->getLeft() == nullptr)
        {
            node* temp = r;
            r = r->getRight();
            delete temp;
        }
        // Caso 3: So tem filho a esquerda
        else if(r->getRight() == nullptr)
        {
            node* temp = r;
            r = r->getLeft();
            delete temp;
        }
        // Caso 4: Tem dois filhos
        else
        {
            //Encontra o primeiro sucessor do elemento
            node* temp = r->getRight();
            if(temp == nullptr)
            {
                // Nao tenha nenhum sucessor
                // Pega o predecessor
                temp = r->getLeft();
                while(temp->getRight() != nullptr)
                {
                    temp = temp->getRight();
                }
                r->setData(temp->getData());
                // Remove o sucessor
                r->setRight(remove(r->getRight(), temp->getData()));
            }else{
                while(temp->getLeft() != nullptr)
                {
                    temp = temp->getLeft();
                }
                // Troca o valor do elemento pelo do sucessor
                r->setData(temp->getData());
                // Remove o sucessor
                r->setRight(remove(r->getRight(), temp->getData()));
            }    
        }
    }
    return r;
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
    return max(altEsq, altDir) + 1; // + 1
}

void BST::printBT(const std::string& prefix, node* n, bool isLeft)
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
        cout << "   (6) Definir tempo de amostra da lista na função (3), (4) e (5)\n";
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
            break;
        case 2:
            clearTerminal();
            cout << "Digite o valor que gostaria de remover\n";
            cin >> val;
            remove(root, val);
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
            cout << "Digite o tempo de amostra da lista na função (3), (4) e (5)\n";
            cin >> tempoAmostra;
            break;
        default:
            clearTerminal();
            cout << "Opção invalida\n";
            //sleep_for(seconds(2));
            sleepSec(2);
            break;
        }
    }
}

int main()
{
    BST tree;
    tree.interfaceUser();

    return 0;
}
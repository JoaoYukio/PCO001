#include <iostream>
#include <queue>

using namespace std;

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

void clearTerminal()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else defined(__linux__) || defined(__unix__)
        system("clear");
    #endif
    return;
}

class Node{
    public:
        int data;
        Node* left;
        Node* right;
        Node(int data)
        {
            this->data = data;
            this->left = this->right = nullptr;
        }
};

class BST{
    public:
        Node* root;
        bool rootSet;
        BST()
        {
            this->root = nullptr;
            this->rootSet = false;
        }
        //Insert a node recursively
        void insert(Node* r, int data)
        {
            if(r == nullptr)
            {
                r = new Node(data);
                return;
            }
            if(data < r->data)
            {
                if(r->left == nullptr)
                {
                    r->left = new Node(data);
                    return;
                }
                insert(r->left, data);
            }
            else
            {
                if(r->right == nullptr)
                {
                    r->right = new Node(data);
                    return;
                }
                insert(r->right, data);
            }
        }
        //Remove a node recursively
        Node* remove(Node* r, int data)
        {
            if(r == nullptr)
            {
                return r;
            }
            if(data < r->data)
            {
                r->left = remove(r->left, data);
            }
            else if(data > r->data)
            {
                r->right = remove(r->right, data);
            }
            else
            {
                if(r->left == nullptr)
                {
                    Node* temp = r->right;
                    delete r;
                    return temp;
                }
                else if(r->right == nullptr)
                {
                    Node* temp = r->left;
                    delete r;
                    return temp;
                }
                Node* temp = r;
                r = r->right;
                while(r->left != nullptr)
                {
                    r = r->left;
                }
                r->data = temp->data;
                r->right = remove(r->right, temp->data);
            }
            return r;
        }


        //Search for a node recursively
        bool search(Node* r, int data)
        {
            if(r == nullptr)
            {
                return false;
            }
            if(data < r->data)
            {
                return search(r->left, data);
            }
            else if(data > r->data)
            {
                return search(r->right, data);
            }
            else
            {
                return true;
            }
        }
        //Print in order
        void printInOrder(Node* r)
        {
            if(r == nullptr)
            {
                return;
            }
            printInOrder(r->left);
            cout << r->data << " ";
            printInOrder(r->right);
        }
        //Print pre order
        void printPreOrder(Node* r)
        {
            if(r == nullptr)
            {
                return;
            }
            cout << r->data << " ";
            printPreOrder(r->left);
            printPreOrder(r->right);
        }
        //Print post order
        void printPostOrder(Node* r)
        {
            if(r == nullptr)
            {
                return;
            }
            printPostOrder(r->left);
            printPostOrder(r->right);
            cout << r->data << " ";
        }

        void printBT(const std::string& prefix, Node* n, bool isLeft)
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

        int Altura(Node* r)
        {
            if(r == nullptr)return 0;
            int altEsq = Altura(r->left);
            int altDir = Altura(r->right);
            return max(altEsq, altDir) + 1; // + 1
        }

        void interfaceUser()
        {
            int op;
            int val = 0;
            int tempoAmostra = 5;
            Node* p = nullptr;
            bool sig;
            //int pos;
            for(;;)
            {
                if(this->rootSet == false)
                {
                    cout << "Digite o valor da raiz: ";
                    cin >> val;
                    this->root = new Node(val);
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
                    sig = search(root, val);
                    if(sig == false)
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
                    cout << "Opcao invalida\n";
                    //sleep_for(seconds(2));
                    sleepSec(2);
                    break;
                }
            }
        }

};
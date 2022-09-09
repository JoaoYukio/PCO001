#include<iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


class Node{
    public:
        int data;
        Node* next;
        Node()
        {
            data = 0;
            next = nullptr;
        }
        Node(int data)
        {
            this->data = data;
            next = nullptr;
        }
        Node(int data, Node* next)
        {
            this->data = data;
            this->next = next;
        }
};

class ListaLinkada{
    public:
        Node* head;
        Node* tail;
        bool isEmpty();
        bool insertIni(int val);
        bool insertFinal(int val);
        int remove(int val);
        int removeIni();
        int search(int val);
        void display();
        void clear();
        void interface();
    ListaLinkada()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
};

bool ListaLinkada::isEmpty()
{
    return (head == nullptr)?true:false;
}

bool ListaLinkada::insertIni(int val)
{
    if(head == nullptr and tail == nullptr)// inserindo no primeiro elemento
    {
        Node* p = new Node(val);
        head = p;
        tail = p;
        return true;
    }
    Node* p = new Node(val, head);
    if(p != nullptr)// tem espaço na heap?
    {
        this->head = p;
        return true;
    }
    cout << "Sem memoria na heap\n";
    return false;
}

bool ListaLinkada::insertFinal(int val)
{
    if(head == nullptr and tail == nullptr)// inserindo no primeiro elemento
    {
        Node* p = new Node(val);
        head = p;
        tail = p;
        return true;
    }
    Node* p = new Node(val);
    if(p != nullptr)
    {
        this->tail->next = p;
        this->tail = p;
        return true;
    }
    return false;
}

void ListaLinkada::display()
{
    Node* p = head;
    while(p)
    {
        cout << p->data << "->";
        p = p->next;
    }
    cout<<"NULL"<<'\n';
}

void ListaLinkada::clear()
{
    Node* first = head;
    Node* second = nullptr;
    while(first)
    {
        second = first;
        first = first ->next;
        delete second;
    }
    head = tail = nullptr;
}

int ListaLinkada::search(int val)
{
    Node* p = head;
    //int i = 0;
    /*while(p) // O(n) <- poderia trocar para : for(int i = 0; p!= nullptr; i++)
    {
        if(p->data == val)
        {
            return i;
        }
        i++;
        p = p->next;
    }*/
    for(int i = 0; p!= nullptr; i++) // aqui a parte do incremento de i e sua inicialização estao implicitos no for
    {
        if(p->data == val)
        {
            return i;
        }
        p = p->next;
    }
    return -1; // Erro valor nao encontrado
}

int ListaLinkada::remove(int val)
{
    int indice = search(val);

    if(indice != -1 and head == tail)// encontrou o elemento e so tem ele
    {
        Node* p = head;
        int data = p->data;
        head = nullptr;
        tail = nullptr;
        delete p;
        return data;
    }

    if(indice == 0)//encontrou o elemento no primeiro elemento
    {
        Node* p = head;
        int data = p->data;
        head = head->next;
        delete p;
        return data;
    }

    if(indice != -1)//encontrou o valor
    {
        Node* p = head;
        Node* t = nullptr;
        for(int i = 0; i < indice and p != nullptr; i++)
        {
            t = p;
            p = p->next;
        }
        if(p == tail)// elemento no ultimo elemento da LL
        {
            tail = t;
        }
        t->next = p->next;
        int data = p->data;
        delete p;
        return data;
    }
    return -2; // Erro de elemento nao encontrado na remocao
}

int ListaLinkada::removeIni()
{
    Node* p = head;
    if(head == tail and not isEmpty())// somente um elemento
    {
        int data = head -> data;
        head = nullptr;
        tail = nullptr;
        delete p;
        return data;
    }
    if(not isEmpty())
    {
        //lista nao esta vazia
        int data = p ->data;
        head = head->next;
        delete p;
        return data;
    }
    cout << "LL underflow\n";
    return -3; // Erro de underflow
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

void ListaLinkada::interface()
{
    int op;
    int val = 0;
    int tempoAmostra = 5;
    int pos;
    for(;;)
    {
        clearTerminal();
        cout << "Escolha o que quer fazer: \n";
        cout << "   (1) Inserir no inicio\n";
        cout << "   (2) Inserir no final\n";
        cout << "   (3) Remover no inicio\n";
        cout << "   (4) Remover elemento n\n";
        cout << "   (5) Pesquisar na lista\n";
        cout << "   (6) Imprimir a lista\n";
        cout << "   (7) Limpar a lista\n";
        cout << "   (8) Definir tempo de amostra da lista na função (6)\n";
        cout << "   (9) Ver se a lista esta vazia\n";
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
            insertIni(val);
            break;
        case 2:
            clearTerminal();
            cout << "Digite o valor que gostaria de inserir\n";
            cin >> val;
            insertFinal(val);
            break;
        case 3:
            clearTerminal();
            removeIni();
            break;
        case 4:
            clearTerminal();
            cout << "Digite o valor que gostaria de remover\n";
            cin >> val;
            remove(val);
            break;
        case 5: 
            clearTerminal();
            cout << "Digite o valor que gostaria de pesquisar\n";
            cin >> val;
            pos = search(val);
            if(pos == -1)
            {
                cout << "Valor nao encontrado\n";
            }else{
                cout << "Valor encontrado em: " << pos << '\n';
            }
            sleep_for(seconds(2));
            break;
        case 6:
            clearTerminal();
            cout<< "Mostrando a lista por "<< tempoAmostra <<" segundos\n";
            display();
            sleep_for(seconds(tempoAmostra));
            break;
        case 7:
            clearTerminal();
            clear();
            break;
        case 8:
            clearTerminal();
            cout << "Por quantos segundos devo mostrar a lista?\n";
            cin >> tempoAmostra;
            if(tempoAmostra <= 0 or tempoAmostra > 1000)
            {
                cout << "Valor invalido, alterando para o default 5 segundos\n";
                tempoAmostra = 5;
            }
            break;
        case 9:
            clearTerminal();
            if(isEmpty())
            {
                cout << "Lista vazia\n";
            }else{
                cout << "Lista nao vazia\n";
            }
            sleep_for(seconds(2));
            break;
        default:
            clearTerminal();
            cout << "Opção invalida\n";
            sleep_for(seconds(2));
            break;
        }
    }
}

int main()
{
    ListaLinkada L = ListaLinkada();


    /*
    Testes iniciais

    cout << "Insirindo no inicio\n";
    for(int i = 0; i<10; i++)
    {
        L.insertIni(i+1);
    }
    L.display();
    L.clear();//Limpando a lista
    cout << "Insirindo no final\n";
    
    for(int i = 0; i<10; i++)
    {
        L.insertFinal(i+1);
    }
    L.display();
    cout << "Pesquisando o elemento 7: " << L.search(7) << "\n";
    cout << "Pesquisando o elemento 17: " << L.search(17) << "\n";


    cout << "Removendo um elemento no meio da lista, removendo o elemento 7: \n";
    L.remove(7);
    L.display();
    cout << "Removendo o elemento 12\n";
    cout << L.remove(12) << "\n";
    L.display();*/

    L.interface();


    return 0;
}
#include<iostream>

using namespace std;


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
        bool insertIni(int val);
        bool insertFinal(int val);
        int remove(int val);
        int removeIni();
        int removeFinal();
        int search(int val);
        void display();
        void clear();
    ListaLinkada()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
};

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
    if(p)// tem espaço na heap?
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
    if(p)
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
    if(p)
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

int ListaLinkada::removeFinal()
{
    Node* p = tail;
    //Eu nao consigo remover do final em O(1), precisaria ter um link de volta no Node
    Node* t = head;
    while(t->next != p)
    {
        t = t->next;
    }
    tail = t;
    int data = p->data;
    delete p;
    return data;
}

int main()
{
    ListaLinkada L = ListaLinkada();

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
    L.display();

    //TODO: criar a interface para testar as funções

    return 0;
}
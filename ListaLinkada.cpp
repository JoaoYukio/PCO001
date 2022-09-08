#include<iostream>

using namespace std;


class Node{
    int data;
    private:
        Node* next;
    public:
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
        bool insert(int val);
        int remove(int elem);
        int search(int val);
    ListaLinkada()
    {
        this->head = nullptr;
    };
    ListaLinkada(Node* head)
    {
        this->head = head;
    }
};

bool ListaLinkada::insert(int val)
{
    if(head == nullptr)// inserindo no primeiro elemento
    {
        Node* p = new Node(val);
        head = p;
        return true;
    }
}

int main()
{
    Node* n= new Node();

    return 0;
}
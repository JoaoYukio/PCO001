#include <iostream>
#include <string>

using namespace std;

class node{
    public:
        char data;
        node* next;
        node(){}
        node(char data)
        {
            this->data = data;
            this->next = nullptr;
        }
        node(char data, node* next)
        {
            this->data = data;
            this->next = next;
        }
};

class stack{
    private:
        node* topo;
    public:
        stack(){topo = nullptr;};
        bool push(char c);
        char pop();
        bool isEmpty();
        node* top();
        void clear();
        void display();
};

bool stack::isEmpty()
{
    return (topo == nullptr)? true: false;
}

void stack::display()
{
    node* t = topo;
    cout << "Topo\n";
    while(t!=nullptr)
    {
        cout << t->data << '\n';
        t = t->next;
    }
}

bool stack::push(char c)
{
    node* t = new node(c);
    if(t==nullptr)return false;
    if(isEmpty())
    {
        topo = t;
        return true;
    }
    t -> next = topo;
    topo = t;
    return true;
}

char stack::pop()
{
    if(isEmpty())
    {
        return '!';
    }
    char ret;
    node* p = topo;
    ret = p->data;
    topo = topo->next;
    delete p;
    return ret;
}

node* stack::top()
{
    return topo;
}

void stack::clear()
{
    while(!isEmpty())
    {
        pop();
    }
}

bool bemFormada(string str)
{
    stack st = stack();
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] == '(' or str[i] == '[' or str[i] == '{')
        {
            st.push(str[i]);
        }else if(str[i] == ')'){
            if(st.pop()!= '(')
            {
                return false;
            }
        }else if(str[i] == ']'){
            if(st.pop()!= '[')
            {
                return false;
            }
        }else if(str[i] == '}'){
            if(st.pop()!= '{')
            {
                return false;
            }
        }
    }
    return (st.isEmpty())?true:false;
}

int main()
{
    string str;
    for(;;)
    {
        cout << "Digite a sua expressao ('exit' para sair)\n";
        cin >> str;
        if(str == "exit")break;  
        (bemFormada(str))?cout<<"Sequencia correta\n":cout<<"Sequencia incorreta\n";
    }

    return 0;
}
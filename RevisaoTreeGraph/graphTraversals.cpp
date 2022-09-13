#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class node{
    public:
    int data;
    node* next;
    node(){};
    node(int val)
    {
        data = val;
        next = nullptr;
    }
};

class queueLinkedList{
    private:
        node* head;
    public:
        bool isEmpty();
        bool enqueue(int val);
        int dequeue();
        void display();
        queueLinkedList()
        {
            head = nullptr;
        }
};

bool queueLinkedList::isEmpty()
{
    return (head==nullptr)?true:false;
}
bool queueLinkedList::enqueue(int val)
{
    node* t = new node(val);

    if(t==nullptr)return false;
    
    if(isEmpty() == true)
    {
        head = t;
        return true;
    }
    t->next = head;
    head = t;
    return true;
}
int queueLinkedList::dequeue()
{
    node* p;
    int val = -1;
    if(isEmpty())return val;
    p = head;
    val = head->data;
    head = head->next;
    delete p;
    return val;
}
void queueLinkedList::display()
{
    node* p = head;
    while(p!=nullptr)
    {
        cout << p->data << "->";
        p = p->next;
    }
    cout << "NULL\n";
}


class graph{
    int numNodes;
    int** matAd; 
    public:
    bool addEdge(int v, int w);
    void clearEdges()
    {
        for(int i = 0; i<numNodes; i++)
        {
            for(int j = 0; j<numNodes; j++)
            {
                matAd[i][j] = 0;
            }
        }
    }
    void BFS(int stNode); 
    void DFS(int stNode);
    void resetVisited(){
        for(int i = 0; i<numNodes; i++){
            visited[i] = 0;
        }
    }
    void displayMat();
    int* visited;
    graph(int numNodes)
    {
        this->numNodes = numNodes;

        visited = new int[numNodes];

        matAd = new int*[numNodes];
        for(int i = 0; i<numNodes; i++)
        {
            matAd[i] = new int[numNodes];
            visited[i] = 0;
        }
        for(int i = 0; i<numNodes; i++)
        {
            for(int j = 0; j<numNodes; j++)
            {
                matAd[i][j] = 0;
            }
        }
    }
};
void graph::displayMat()
{
    for(int i = 0; i<numNodes; i++)
    {
        for(int j = 0; j<numNodes; j++)
        {
            cout << matAd[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool graph::addEdge(int v, int w)
{
    if(v < numNodes and w < numNodes)
    {
        matAd[v][w] = 1;
    }
    return false;
}

void graph::BFS(int stNode)
{
    queueLinkedList q = queueLinkedList();
    if(stNode < numNodes)
    {
        visited[stNode] = 1;
        cout << stNode << ' ';
        q.enqueue(stNode);
        while(!q.isEmpty())
        {
            int node = q.dequeue();
            if(visited[node] == 0)cout << node << ' ';
            visited[node] = 1;
            for(int i = 0; i< numNodes; i++)
            {
                if(matAd[node][i] == 1 and visited[i] == 0)
                {
                    q.enqueue(i);
                }
            }
        }
    }
    return;
}

void graph::DFS(int stNode)
{
    if(visited[stNode] == 0)
    {
        visited[stNode] = 1;
        cout << stNode << ' ';
        for(int i = 0; i < numNodes; i++)
        {
            if(matAd[stNode][i] == 1 and visited[i] == 0)
            {
                DFS(i);
            }
        }
    }
}

int main()
{
    graph g = graph(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    

    //g.displayMat();

    cout << '\n';

    //g.BFS(1);
    g.resetVisited();
    g.DFS(1);

    g.clearEdges();

    g.addEdge(2,0);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(0,1);
    g.addEdge(3,3);
    g.addEdge(1,3);

    cout << "\n";

    g.resetVisited();
    g.DFS(2);

    return 0;
}
#include <iostream>
#include <list>

using namespace std;

class graph{
    int numNodes;
    int** matAd; 
    public:
    list<int> lista;
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
    void DFS(int stNode);
    void DFS_EXP(int stNode);
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
                lista.push_front(stNode);
            }
        }
    }
}

void graph::DFS_EXP(int stNode)
{
    if(visited[stNode] == 0)
    {
        DFS(stNode);
    }
}


int main()
{
    graph grafo = graph(9);
    /*
    Definições:
        0 - cueca
        1 - relogio
        2 - meia
        3 - calça 
        4 - camisa
        5 - tenis
        6 - cinto
        7 - gravata
        8 - paleto
    */


    grafo.addEdge(0, 5);
    grafo.addEdge(0, 3);
    grafo.addEdge(1, -1); // estou usando -1 para simbolizar nenhuma conexao
    grafo.addEdge(2, 5);
    grafo.addEdge(3, 6);
    grafo.addEdge(3, 5);
    grafo.addEdge(4, 6);
    grafo.addEdge(4, 7);
    grafo.addEdge(6, 8);
    grafo.addEdge(7, 8);


    grafo.DFS_EXP(0);

    //print da lista
    for(auto i = grafo.lista.begin(); i != grafo.lista.end(); i++)
    {
        cout << *i << ' ';
    }
    return 0;
}
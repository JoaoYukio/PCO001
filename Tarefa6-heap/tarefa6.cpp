#include <iostream>
using namespace std;

class minHeap {
private:
    int* heap;
    int size;
    int capacity;
public:
    minHeap(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        heap = new int[capacity];
    }
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
    void heapfy(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < size && heap[l] < heap[i])
            smallest = l;
        if (r < size && heap[r] < heap[smallest])
            smallest = r;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);//Funcao swap embutida no C++
            heapfy(smallest);
        }
    }
    void push(int k)
    {
        if (size == capacity) {
            cout << "\nHeap cheia\n";
            return;
        }
        size++;
        int i = size - 1;
        heap[i] = k;
        while (i != 0 && heap[parent(i)] > heap[i]) {
            //Troca o pai com o filho até que o pai seja menor que o filho
            swap(heap[i], heap[parent(i)]);
            //Atualiza o índice do pai para o 'pai do pai'
            i = parent(i);
        }
        print();
    }
    int pop()
    {
        if (size <= 0)
            return -1;
        if (size == 1) {
            size--;
            return heap[0];
        }
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapfy(0);
        print();
        return root;
    }
    int top()
    {
        if (size <= 0)
            return -1;
        return heap[0];
    }
    bool empty()
    {
        return (size == 0);
    }
    bool full()
    {
        return (size == capacity);
    }
    void print()
    {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
    // Função para mostrar quem sao os filhos de cada nó
    void printFilhos()
    {
        for (int i = 0; i < size; i++) {
            cout << "Filhos de " << heap[i] << ": ";
            if (left(i) < size)
                cout << heap[left(i)] << " ";
            if (right(i) < size)
                cout << heap[right(i)] << " ";
            cout << endl;
        }
    }
};

int main()
{
    minHeap h(15);

    h.push(3);
    h.push(5);
    h.push(6);
    h.push(8);
    h.push(10);
    h.push(11);
    h.push(12);
    h.push(13);
    h.push(15);
    h.push(20);

    h.printFilhos();

    cout << "Pop de 3 valores\n";
    h.pop();
    h.pop();
    h.pop();

    return 0;
}


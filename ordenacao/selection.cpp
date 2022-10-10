#include <iostream>

using namespace std;

void selectionSort(int* arr, int n)
{
    cout<<"Array nao ordenado\n";
    for(int i =0;i<n;i++)
    {
        cout<< arr[i] << ' ';
    }
    int menorInd;
    for(int i =0; i<n; i++)
    {
        menorInd = i;
        for(int j = i+1; j < n; j++)
        {
            if(arr[menorInd] > arr[j])
            {
                menorInd = j;
            }
        }
        int temp = arr[menorInd];
        arr[menorInd] = arr[i];
        arr[i] = temp;
    }
    cout<<"Array ordenado\n";
    for(int i =0;i<n;i++)
    {
        cout<< arr[i] << ' ';
    }
}

int main()
{
    int arr[] = {3,2,5,1,7};

    selectionSort(arr, 5);

    return 0;
}
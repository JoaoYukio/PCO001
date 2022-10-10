#include <iostream>

using namespace std;

void bubbleSort(int* arr, int n)
{
    cout<<"Array nao ordenado\n";
    for(int i =0;i<n;i++)
    {
        cout<< arr[i] << ' ';
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n-1-i; j++)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
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

    bubbleSort(arr, 5);

    return 0;
}
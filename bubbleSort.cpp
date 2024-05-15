#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void bubbleSort(int arr[], int size)
{
    for(int i = 0; i < size - 1; ++i)
    {
        bool flag = false;
        for(int j = 0; j < size - 1 - i; ++j)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j+1]);
                flag = true;
            }
        }
        if(!flag)
        {
            return;
        }
    }
}

int main()
{
    int arr[10];
    srand(time(0));

    for(int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }
    int size = sizeof(arr) / sizeof(arr[0]);

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;

    bubbleSort(arr, size);

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
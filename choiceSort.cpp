#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
//O(n^2) 不稳定
void choiceSort(int arr[], int size)
{
    for(int i = 0; i < size - 1; ++i)
    {
        int min = arr[i];
        int k = i;
        for(int j = i + 1; j < size; ++j)
        {
            if(arr[j] < min)
            {
                min = arr[j];
                k = j;
            }
        }
        if(k != i)
        {
            swap(arr[i], arr[k]);
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

    clock_t startTime, endTime;
    startTime = clock();
    choiceSort(arr, size);
    endTime = clock();

    cout << "The time of sort is: " << (endTime - startTime) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
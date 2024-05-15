#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
//最差和平均时间复杂度O(n^2) -> O(n)最好 稳定
void insertSort(int arr[], int size)
{
    for(int i = 1; i < size; ++i)
    {
        int val = arr[i];
        int j = i - 1;
        for(; j >=0 && arr[j] > val; --j)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
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
    insertSort(arr, size);
    endTime = clock();

    cout << "The time of sort is: " << (endTime - startTime) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
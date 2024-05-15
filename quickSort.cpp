#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void medianOfThree(int arr[], int l, int r)
{
    int mid = l + (r - l) / 2;
    if(arr[mid] < arr[l]) swap(arr[mid], arr[l]);
    if(arr[r] < arr[l]) swap(arr[r], arr[l]);
    if(arr[r] < arr[mid]) swap(arr[r], arr[mid]);
    swap(arr[mid], arr[l]);
}

int partition(int arr[], int l, int r)
{
    medianOfThree(arr, l, r);
    int val = arr[l];
    while(l < r)
    {
        while(l < r && arr[r] > val)
        {
            --r;
        }
        if(l < r)
        {
            arr[l] = arr[r];
            ++l;
        }
        while(l < r && arr[l] < val)
        {
            ++l;
        }
        if(l < r)
        {
            arr[r] = arr[l];
            --r;
        }
    }
    arr[l] = val;
    return l;
}

void quickSort(int arr[], int l, int r)
{
    if(l >= r) return;
    int pos = partition(arr, l, r);
    quickSort(arr, l, pos - 1);
    quickSort(arr, pos + 1, r);
}


void quickSort(int arr[], int size)
{
    return quickSort(arr, 0, size - 1);
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
    quickSort(arr, size);
    endTime = clock();

    cout << "The time of sort is: " << (endTime - startTime) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
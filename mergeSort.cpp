#include <iostream>
using namespace std;

void merge(int arr[], int l, int mid, int r, int* p)
{
    int idx = 0;
    int i = l;
    int j = mid + 1;

    while(i <= mid & j <= r)
    {
        if(arr[i] <= arr[j])
        {
            p[idx++] = arr[i++];
        }
        else
        {
            p[idx++] = arr[j++];
        }
    }
    while(i <= mid)
    {
        p[idx++] = arr[i++];
    }
    while(j <= r)
    {
        p[idx++] = arr[j++];
    }
    for(int i = l, j = 0; i <= r; ++i, ++j)
    {
        arr[i] = p[j];
    }
}

void mergeSort(int arr[], int l, int r, int* p)
{
    if(l >= r)
    {
        return;
    }
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid, p);
    mergeSort(arr, mid + 1, r, p);
    merge(arr, l, mid, r, p);
}

void mergeSort(int arr[], int size)
{
    int* p = new int[size];
    mergeSort(arr, 0, size - 1, p);
    delete p;
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
    mergeSort(arr, size);
    endTime = clock();

    cout << "The time of sort is: " << (endTime - startTime) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}

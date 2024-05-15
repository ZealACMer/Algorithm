#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
void shellSort(int arr[], int size)
{
    for(int gap = size / 2; gap > 0; gap /= 2) //100w -> 19 1000w -> 24
    {
        for(int i = gap; i < size; ++i)
        {
            int val = arr[i];
            int j = i - gap;
            for(; j >= 0; j -= gap)
            {
                if(arr[j] <= val)
                {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = val;
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
    shellSort(arr, size);
    endTime = clock();

    cout << "The time of sort is: " << (endTime - startTime) * 1.0 / CLOCKS_PER_SEC << "s" << endl;

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
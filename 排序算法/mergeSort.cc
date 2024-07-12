//归并排序
#include <iostream>
//O(n)
void merge(int arr[], int l, int m, int r, int* p)
{
    int idx = 0;
    int i = l;
    int j = m + 1;
    while(i <= m && j <= r)
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

    while(i <= m)
    {
        p[idx++] = arr[i++];
    }

    while(j <= r)
    {
        p[idx++] = arr[j++];
    }
    //将合并好的结果，拷贝到原始数组arr中
    for(i = l, j = 0; i <= r; ++i, ++j)
    {
        arr[i] = p[j];
    }
}

//O(logn)
void mergeSort(int arr[], int l, int r, int* p)
{
    if(l >= r)
    {
        return;
    }
    int mid = l + (r - l) / 2;
    //递
    mergeSort(arr, l, mid, p);
    mergeSort(arr, mid + 1, r, p);
    //归
    merge(arr, l, mid, r, p);
}


void mergeSort(int arr[], int size)
{
    int* p = new int[size];
    mergeSort(arr, 0, size - 1, p);
    delete[] p;
}

void show(int arr[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    int arr[10]{};
    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100;
    }
    show(arr, 10);

    mergeSort(arr, 10);

    show(arr, 10);
    
    return 0;
}

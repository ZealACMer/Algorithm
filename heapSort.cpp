#include <iostream>
using namespace std;

//堆的下沉操作
void siftDown(int arr[], int i, int size)
{
    int val = arr[i];
    while(i < size / 2)
    {
        int child = 2 * i + 1;
        if(child + 1 < size && arr[child + 1] > arr[child])
        {
            child = child + 1;
        }
        if(arr[child] > val)
        {
            arr[i] = arr[child];
            i = child;
        }
        else
        {
            break;
        }
    }
    arr[i] = val;
}

void heapSort(int arr[], int size)
{
    int n = size - 1;
    //从第一个非叶节点开始，进行建堆操作
    for(int i = (n - 1) / 2; i >= 0; --i)
    {
        siftDown(arr, i, size);
    }

    //将堆顶元素与堆尾元素进行交换，开始进行排序, 逐渐缩小堆排序的范围
    for(int i = n; i > 0; --i)
    {
        swap(arr[0], arr[i]);
        siftDown(arr, 0, i); //i为参与调整的元素个数
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

    heapSort(arr, size);

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;


    return 0;
}
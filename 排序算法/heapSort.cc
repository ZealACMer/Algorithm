//堆排序
#include <iostream>

//堆的下沉调整
void siftDown(int arr[], int i, int size)
{
    int val = arr[i];
    while(i < size / 2)
    {
        int child = 2 * i + 1;
        if(child + 1 < size && arr[child + 1] > arr[child]) //从小到大进行排序(从大到小<)
        {
            child = child + 1;
        }

        if(arr[child] > val) //从小到大进行排序(从大到小<)
        {
            arr[i] = arr[child];
            i = child; //i指向其孩子，继续进行调整
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
    //从第一个非叶子节点开始调整
    for(int i = (n - 1) / 2; i >= 0; --i)
    {
        siftDown(arr, i, size);
    }

    //交换堆顶元素和末尾元素，从堆顶开始进行下沉操作
    //将堆的大小减1，排除已经排序好的最后一个节点
    for(int i = n; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        siftDown(arr, 0, i);
    }
}

int main(int argc, char** argv)
{
    srand(time(0));
    int arr[10]{};
    for(int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100;
    }

    for(auto v : arr)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    heapSort(arr, 10);

    for(auto v : arr)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}

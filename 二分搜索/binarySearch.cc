//二分查找算法
#include <iostream>
#include <algorithm>

//针对已排序的数组
int binarySearch(int arr[], int size, int val)
{
    int l = 0, r = size - 1;
    while(l <= r)
    {
        int mid = l + (r - l) / 2;
        if(arr[mid] == val)
        {
            return mid;
        }
        else if(arr[mid] < val)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return -1; //未找到指定元素
}

void show(int arr[], int size)
{
    //std::cout << sizeof(arr) / sizeof(int) << std::endl; => 2
    //数组传递过来的是指针，sizeof(arr)是指针的大小
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    srand(time(0));
    int arr[10]{};
    int size = sizeof(arr) / sizeof(int);
    show(arr, size);

    for(int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100;
    }
    show(arr, size);

    std::sort(arr, arr + 10);
    show(arr, size);

    std::cout << binarySearch(arr, 10, 5) << std::endl;

    std::cout << "====================" << std::endl;
    int brr[10]{1, 2, 4, 11, 22, 25, 100, 1000};
    std::cout << binarySearch(brr, 10, 11) << std::endl;
    std::cout << binarySearch(brr, 10, 100) << std::endl;
    std::cout << binarySearch(brr, 10, 5) << std::endl;

    return 0;
}

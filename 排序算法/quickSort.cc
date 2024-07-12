//快速排序 平均时间复杂度O(nlogn) 平均空间复杂度O(logn)，递归的深度占用的栈内存
#include <iostream>
#include <stdlib.h>
#include <time.h>

//获取三个数字的中位数的下标
int findMedian(int arr[], int l, int mid, int r)
{
    if((arr[l] >= arr[mid] && arr[l] <= arr[r]) || (arr[l] >= arr[r] && arr[l] <= arr[mid]))
    {
        return l;
    }
    else if((arr[mid] >= arr[l] && arr[mid] <= arr[r]) || (arr[mid] >= arr[r] && arr[mid] <= arr[l]))
    {
        return mid;
    }
    else
    {
        return r;
    }
}

int partition(int arr[], int l, int r)
{
    int mid = l + (r - l) / 2;
    int index = findMedian(arr, l, mid, r); //选择一次快排过程的基准数
    std::swap(arr[l], arr[index]);
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

    arr[l] = val; //基准元素的存放位置
    return l;

}

void quickSort(int arr[], int begin, int end)
{
    if(begin >= end) //递归结束条件
    {
        return;
    }

    //一次快排分割处理
    int pos = partition(arr, begin, end);
    quickSort(arr, begin, pos - 1);
    quickSort(arr, pos + 1, end);

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
    quickSort(arr, 0, 9);
    show(arr, 10);
    return 0;
}

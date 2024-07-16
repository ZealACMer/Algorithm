//快排分割求TopK元素
#include <iostream>

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

void selectTopK(int arr[], int l, int r, int k)
{
    int pos = partition(arr, l, r);
    if(pos == k - 1)
    {
        return;
    }
    else if(pos > k - 1)
    {
        selectTopK(arr, l, r - 1, k);
    }
    else
    {
        selectTopK(arr, pos + 1, r, k);
    }
}

int main(int argc, char** argv)
{
    int arr[] = {23, 36, 25, 88, 99, 103, 235, 778, 355, 991};
    int size = sizeof(arr) / sizeof(arr[0]);

    //求值最小的前3个元素
    int k = 3;
    selectTopK(arr, 0, size - 1, k);

    for(int i = 0; i < k; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

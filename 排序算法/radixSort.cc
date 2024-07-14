//基数排序
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

//时间复杂度O(nd),d为数字的最长位数 空间复杂度O(n) 稳定
void radixSort(int arr[], int size)
{
    int maxData = arr[0];
    for(int i = 1; i < size; ++i)
    {
        if(maxData < abs(arr[i]))
        {
            maxData = abs(arr[i]);
        }
    }

    int len = std::to_string(maxData).size();

    std::vector<std::vector<int>> vecs;
    int mod = 10;
    int dev = 1;

    for(int i = 0; i < len; mod *= 10, dev *= 10, ++i)
    {
        vecs.resize(20); //20个桶，为了能处理负数-9~9,vecs.clear()后size为0，需要重新resize
        for(int j = 0; j < size; ++j)
        {
            //元素第i个位置的数字
            int index = arr[j] % mod / dev + 10;
            vecs[index].push_back(arr[j]);
        }

        //遍历所有的桶，将元素拷贝回原始的数组中
        int idx = 0;
        for(auto vec : vecs) //O(20)
        {
            for(int v : vec) //O(n)
            {
                arr[idx++] = v;
            }
        }
        vecs.clear();
    }
}

int main(int argc, char** argv)
{
    int arr[10];
    srand(time(0));
    
    for(int i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    arr[9] = -123;
    arr[6] = -38;

    for(int v : arr)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    radixSort(arr, 10);
    for(int v : arr)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}

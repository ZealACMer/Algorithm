#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

//O(nd), n为元素的个数，d为数字的位数最大值，稳定
//空间复杂度O(n)
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

    int len = to_string(maxData).size();

    vector<vector<int>> vec;
    int mod = 10;
    int dev = 1;

    for(int i = 0; i < len; mod *= 10, dev *= 10, ++i)
    {
        vec.resize(20); //创建20个桶，为了能够处理-9~9
        for(int j = 0; j < size; ++j)
        {
            //计算当前元素第i位的数字
            int index = arr[j] % mod / dev + 10;
            vec[index].push_back(arr[j]);
        }

        //依次遍历所有的桶，把元素拷贝回原始的数组当中
        int idx = 0;
        for(auto subVec : vec) //O(20) -> O(1)
        {
            for(auto v : subVec) //O(n)
            {
                arr[idx++] = v;
            }
        }
        vec.clear();
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

    arr[4] = -125;
    arr[7] = -45;

    int size = sizeof(arr) / sizeof(arr[0]);

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;

    radixSort(arr, size);

    for(auto v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}
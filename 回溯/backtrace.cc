#include <iostream>
#include <cmath>
#include <vector>

int cnt = 0;
//子集树
void func(int arr[], int i, int len, int x[])
{
    if(i == len)
    {
        ++cnt;
        for(int j = 0; j < len; ++j)
        {
            if(x[j] == 1)
            {
                std::cout << arr[j] << " ";
            }
        }
        std::cout << std::endl;
    }
    else
    {
        x[i] = 1; //选择i节点
        func(arr, i + 1, len, x); //遍历i的左孩子

        x[i] = 0; //不选择i节点
        func(arr, i + 1, len, x); //遍历i的右孩子
    }
}

int main(int argc, char** argv)
{
    int arr[] = {1, 2, 3};
    int len = sizeof(arr) / sizeof(arr[0]);
    int x[3]{0};
    func(arr, 0, len, x);
    std::cout << "cnt: " << cnt << std::endl;
    return 0;
}

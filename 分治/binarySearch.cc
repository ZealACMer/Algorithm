#include <iostream>
#include <vector>
#include <algorithm>

//对有序的数组进行二分搜索
bool binarySearch(std::vector<int>& vec, int i, int j, int val)
{
    while(i <= j)
    {
        int mid = i + (j - i) / 2;
        if(vec[mid] == val)
        {
            return true;
        }
        else if(vec[mid] > val)
        {
            return binarySearch(vec, i, mid - 1, val);
        }
        else
        {
            return binarySearch(vec, mid + 1, j, val);
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    std::vector<int> vec;
    for(int i = 0; i < 11; ++i)
    {
        vec.emplace_back(rand() % 100);
    }
    vec.emplace_back(42);

    sort(vec.begin(), vec.end());
    
    for(auto v : vec)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    bool result = binarySearch(vec, 0, vec.size() - 1, 42);
    std::cout << std::boolalpha << result << std::endl;

    result = binarySearch(vec, 0, vec.size() - 1, 100);
    std::cout << std::boolalpha << result << std::endl;
    return 0;
}

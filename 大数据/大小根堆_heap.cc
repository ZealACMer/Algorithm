//最大(最小)的前N个元素，重复次数最大(最小)的前N个元素
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <functional>
#include <unordered_map>

int main(int argc, char** argv)
{
    srand(time(0));
    std::vector<int> vec;
    for(int i = 0; i < 10000; ++i)
    {
        vec.emplace_back(rand() % 10000);
    }

    //统计重复次数最小的三个数字
    int k = 3;
    std::unordered_map<int, int> m;
    for(auto key : vec)
    {
        m[key]++;
    }

    using type = std::pair<int, int>;
    using comp = std::function<bool(type&, type&)>;
    std::priority_queue<type, std::vector<type>, comp> maxHeap(
        [](type& a, type& b) -> bool {
            return a.second < b.second;
        }
    );

    auto it = m.begin();
    for(int i = 0; i < k; ++i, ++it)
    {
        maxHeap.push(*it);
    }

    for(; it != m.end(); ++it)
    {
        if(maxHeap.top().second > it->second)
        {
            maxHeap.pop();
            maxHeap.push(*it);
        }
    }

    while(!maxHeap.empty())
    {
        std::cout << "重复次数最小的三个数字为：" << std::endl;
        std::cout << "key: " << maxHeap.top().first << " cnt: " << maxHeap.top().second << std::endl;
        maxHeap.pop();
    }

    //统计重复次数最大的三个数字
    std::priority_queue<type, std::vector<type>, comp> minHeap(
        [](type& a, type& b) -> bool {
            return a.second > b.second;
        }
    );

    it = m.begin();
    for(int i = 0; i < k; ++i, ++it)
    {
        minHeap.push(*it);
    }

    for(; it != m.end(); ++it)
    {
        if(minHeap.top().second < it->second)
        {
            minHeap.pop();
            minHeap.push(*it);
        }
    }

    while(!minHeap.empty())
    {
        std::cout << "重复次数最大的三个数字为：" << std::endl; 
        std::cout << "key: " << minHeap.top().first << " cnt: " << minHeap.top().second << std::endl;
        minHeap.pop();
    }

    //求vec中值最小的前3个元素
    std::priority_queue<int> intMaxHeap;
    for(int i = 0; i < 3; ++i)
    {
        intMaxHeap.emplace(vec[i]);
    }
    int size = vec.size();
    for(int i = 3; i < size; ++i)
    {
        if(intMaxHeap.top() > vec[i])
        {
            intMaxHeap.pop();
            intMaxHeap.push(vec[i]);
        }
    }

    std::cout << "vec中值最小的前3个元素为: " << std::endl;
    while(!intMaxHeap.empty())
    {
        std::cout << intMaxHeap.top() << " ";
        intMaxHeap.pop();
    }
    std::cout << std::endl;

    //求vec中值最大的前3个元素
    std::priority_queue<int, std::vector<int>, std::greater<int>> intMinHeap;
    
    for(int i = 0; i < 3; ++i)
    {
        intMinHeap.push(vec[i]);
    }

    for(int i = 3; i < size; ++i)
    {
        if(intMinHeap.top() < vec[i])
        {
            intMinHeap.pop();
            intMinHeap.push(vec[i]);
        }
    }

    std::cout << "vec中值最大的前3个元素为: " << std::endl;
    while(!intMinHeap.empty())
    {
        std::cout << intMinHeap.top() << " ";
        intMinHeap.pop();
    }
    std::cout << std::endl;

    return 0;
}

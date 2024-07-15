//unordered_set unordered_map 大数据去重
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>
#include <string>

int main(int argc, char** argv)
{
    #if 0
    std::string src = "sjcjksljejlgfjsgiljgldjg";
    std::unordered_map<int, int> unorderedMap;
    for(char c : src)
    {
        unorderedMap[c]++;
    }

    for(char c : src)
    {
        if(unorderedMap[c] == 1)
        {
            std::cout << "第一个没有重复出现的字符是：" << c << std::endl;
            return 0;
        }
    }
    std::cout << "所有的字符都重复出现过" << std::endl;
    return 0;
    #endif

    #if 0
    srand(time(0));
    std::vector<int> vec;
    for(int i = 0; i < 10000; ++i)
    {
        vec.emplace_back(rand() % 10000);
    }

    //找出第一个重复出现的数字
    std::unordered_set<int> s1;
    for(auto key : vec)
    {
        auto it = s1.find(key);
        if(it == s1.end())
        {
            s1.insert(key);
        }
        else
        {
            std::cout << "第一个重复出现的数字是: " << key << std::endl;
            break; //continue 所有重复出现的数字
        }
    }
    #endif

    //统计重复的数字以及出现的次数
    srand(time(0));
    std::vector<int> vec;
    for(int i = 0; i < 10000; ++i)
    {
        vec.emplace_back(rand() % 10000);
    }

    std::unordered_map<int, int> m1;
    for(int key : vec)
    {
        // auto it = m1.find(key);
        // if(it == m1.end())
        // {
        //     m1.emplace(key, 1); //第一次插入元素
        // }
        // else
        // {
        //     it->second += 1;
        // }
        // 简化为
        m1[key]++;
    }

    for(auto pair : m1)
    {
        if(pair.second > 1)
        {
            std::cout << "数字" << pair.first << "重复出现, 重复出现的次数为：" << pair.second << std::endl; 
        }
    }

    //过滤掉重复的数字
    std::unordered_set<int> s1;
    for(auto key : vec)
    {
        s1.emplace(key);
    }
    for(auto v : s1)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}

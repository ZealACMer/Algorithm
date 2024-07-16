#include <iostream>
#include <memory>

// Brute Force算法，时间复杂度O(mn)，空间复杂度O(1)
int BF(std::string s, std::string t)
{
    int i = 0;
    int j = 0;
    
    while(i < s.size() && j < t.size()) //O(n)
    {
        if(s[i] == t[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 1; //指向之前开始匹配字符的下一个字符位置 O(m)
            j = 0;
        }
    }

    if(j == t.size()) //找到匹配的开始位置了
    {
        return i - j;
    }
    else
    {
        return -1; //没有找到
    }
}

//KMP算法中，子串next数组的求解方法
int* getNext(std::string str)
{
    int* next = new int[str.size()];
    int j = 0; //用来遍历数组
    int k = -1; //k表示公共前后缀的长度
    next[j] = k;

    while(j < str.size() - 1) //O(m)
    {
        if(k == -1 || str[k] == str[j])
        {
            ++j;
            ++k;
            if(str[k] == str[j])
            {
                //kmp算法的优化
                next[j] = next[k];
            }
            else
            {
                next[j] = k;
            }
        }
        else
        {
            k = next[k]; //k值回溯，继续找最长的公共前后缀
        }
    }
    return next;
}

//KMP算法 时间复杂度O(m) + O(n) = O(m + n) 空间复杂度O(m)
int KMP(std::string s, std::string t)
{
    int i = 0;
    int j = 0;

    //计算一个子串对应的next数组
    int* next = getNext(t);
    std::unique_ptr<int> ptr(next);

    // std::cout << t << ":";
    // for(int m = 0; m < t.size(); ++m)
    // {
    //     std::cout << next[m] << " ";
    // }
    // std::cout << std::endl;

    int sSize = s.size();
    int tSize = t.size();
    while(i < sSize && j < tSize) //O(n)
    {
        if(j == -1 || s[i] == t[j])
        {
            ++i;
            ++j;
        }
        else
        {
            //KMP的核心：不回退i，只回退j
            j = next[j]; //如果首字母匹配失败，j == -1
        }
    }

    if(j == tSize)
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

int main(int argc, char** argv)
{
    std::string s = "abcabdefabcabc";
    std::string t = "abcabc";

    int pos = KMP(s, t);
    std::cout << pos << std::endl;

    int pos1 = BF(s, t);
    std::cout << pos1 << std::endl;
    return 0;
}

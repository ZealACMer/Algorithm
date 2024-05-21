#include <iostream>
#include <vector>
#include <memory>

using namespace std;

//暴力解法 时间复杂度 O(n * m) 空间复杂度 O(1)
int BF(string s, string t)
{
    int i = 0;
    int j = 0;

    while(i < s.size() && j < t.size())
    {
        if(s[i] == t[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 1; //从上次开始匹配字符的下一个字符重新比较
            j = 0;
        }
    }

    if(j == t.size())
    {
        return i - j; //返回匹配成功的开始位置
    }
    else
    {
        return -1;
    }
}

//KMP算法求解子串的next数组
vector<int> computeNextArray(const string& str)
{
    int size = str.length();
    vector<int> next(size, 0);
    next[0] = -1;

    int j = -1; //j是前缀的尾部，-1表示空前缀
    for(int i = 1; i < size; ++i)
    {
        //当不匹配时，利用next数组回溯(j >= 0表示有部分匹配)
        while(j >= 0 && str[i] != str[j + 1]) 
        {
            j = next[j];
        }
        //当字符匹配时，前后缀长度都增加1
        if(str[i] == str[j + 1])
        {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

int KMP(string s, string t)
{
    int i = 0;
    int j = 0;

    vector<int> next = computeNextArray(t);
    for(auto val : next)
    {
        cout << val << " ";
    }
    cout << endl;

    int size1 = s.size(); //将s.size()的unsigned int转变为signed int，用于与j = -1进行比较
    int size2 = t.size();
    while(i < size1 && j < size2)
    {
        if(j == -1 || s[i] == t[j]) //如果首字母匹配失败，j = next[j] => j = next[0] => j = -1
        {
            ++i;
            ++j;
        }
        else
        {   //KMP的核心思想：不回退i，只回退j值
            j = next[j];
        }
    }
    if(j == t.size())
    {
        return i - j;
    }
    else
    {
        return -1;
    }
}

int main()
{
    string s = "bcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    string t = "mnop";

    int pos = KMP(s, t);
    cout << pos << endl;

    return 0;
}
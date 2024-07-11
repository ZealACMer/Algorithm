#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

class Array
{
public:
    Array(int size = 10) 
        : mCur(0)
        , mCap(size)
    {
        mpArr = new int[mCap](); //元素初始化为0
    }
    ~Array()
    {
        delete []mpArr;
        mpArr = nullptr;
    }

    //在数组末尾添加元素
    void push_back(int val)
    {
        if(mCur == mCap)
        {
            expand(2 * mCap); //O(n)
        }
        mpArr[mCur++] = val; //O(1)
    }

    //在数组末尾删除元素
    void pop_back()
    {
        if(mCur == 0) //数组中没有元素
        {
            return;
        }
        --mCur; //O(1)
    }

    //按照下标添加元素
    void insert(int pos, int val)
    {
        if(pos < 0 || pos > mCur) //下标不合法
        {
            throw "illegal insert index!";
        }
        
        if(mCur == mCap)
        {
            expand(2 * mCap); //O(n)
        }
        
        for(int i = mCur - 1; i >= pos; --i)
        {
            mpArr[i + 1] = mpArr[i];
        }
        mpArr[pos] = val;
        ++mCur;
    }

    //按照下标删除元素
    void erase(int pos)
    {
        if(pos < 0 || pos >= mCur) //下标不合法
        {
            throw "illegal erase index!";
        }
        
        for(int i = pos + 1; i < mCur; ++i)
        {
            mpArr[i - 1] = mpArr[i];
        }
        --mCur;
    }

    //查询元素，返回相应的下标
    int find(int val) const
    {
        for(int i = 0; i < mCur; ++i)
        {
            if(mpArr[i] == val)
            {
                return i;
            }
        }
        return -1; //未找到相应的元素，返回-1
    }

    //打印数组元素
    void show() const
    {
        for(int i = 0; i < mCur; ++i)
        {
            std::cout << mpArr[i] << " ";
        }
        std::cout << std::endl;
    }

    //返回数组元素的个数
    int size() const
    {
        return mCur;
    }

private:
    //对数组进行扩容 O(n)
    void expand(int size)
    {
        int *p = new int[size];
        memcpy(p, mpArr, sizeof(int) * mCur);
        delete[] mpArr;
        mpArr = p;
        mCap = size;
    }

private:
    int* mpArr; //指向可扩容的数据内存
    int mCap; //数组的容量
    int mCur; //数组有效元素的个数，指向数组末尾元素的下一个位置

};

void AdjustArray(int arr[], int size)
    {
        int* p = arr;
        int* q = arr + size - 1;
        while(p < q)
        {
            while(p < q && (*p & 0x1) == 1)
            {
                ++p;
            }
            while(p < q && (*q & 0x1) == 0)
            {
                --q;
            }
            if(p < q)
            {
                int tmp = *p;
                *p = *q;
                *q = tmp;
                ++p;
                --q;
            }
        }
    }

void Reverse(char arr[], int size)
{
    char* p = arr;
    char* q = arr + size - 1;
    while(p < q)
    {
        char ch = *p;
        *p = *q;
        *q = ch;
        ++p;
        --q;
    }
}

int main(int argc, char** argv)
{
    Array arr;
    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        arr.push_back(rand() % 100);
    }

    arr.show();
    arr.pop_back();
    arr.show();

    arr.insert(0, 100);
    arr.show();

    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if(pos != -1)
    {
        arr.erase(pos);
        arr.show();
    }

    std::cout << "-----------------------------" << std::endl;
    int b[6]{0};
    srand(time(0));
    for(int i = 0; i < 6; ++i)
    {
        b[i] = rand() % 10;
    }
    for(auto v : b)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    AdjustArray(b, sizeof(b) / sizeof(b[0]));

    for(auto v : b)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "-------------------------------" << std::endl;
    char c[] = "Hello World";
    Reverse(c, sizeof(c));
    for(auto ch : c)
    {
        std::cout << ch;
    }
    std::cout << std::endl;

    return 0;
}

#include <iostream>

using namespace std;

class myStack
{
public:
    myStack(int size = 10) : top_(0), cap_(size)
    {
        stack = new int[cap_];
    }
    ~myStack()
    {
        delete []stack;
        stack = nullptr;
    }

    //入栈，均摊时间复杂度为O(1)
    void push(int val)
    {
        if(top_ == cap_)
        {
            expand(2 * cap_);
        }
        stack[top_++] = val;
    }

    //出栈 O(1)
    void pop()
    {
        if(top_ == 0)
        {
            throw "stack is empty!";
        }
        --top_;
    }
    
    //返回栈顶元素 O(1)
    int top()
    {
        if(top_ == 0)
        {
            throw "stack is empty!";
        }
        return stack[top_ - 1];
    }

    //判断栈是否为空 O(1)
    bool empty() const
    {
        return top_ == 0;
    }

    //返回栈中元素的个数 O(1)
    int size() const
    {
        return top_;
    }

private:
    void expand(int size)
    {
        int* p = new int[size];
        memcpy(p, stack, sizeof(int) * top_);
        delete[] stack;
        stack = p;
        cap_ = size;
    }

private:
    int* stack;
    int top_;
    int cap_;
};

int main()
{
    int arr[] = {12, 11, 46, 7, 89, 21, 25, 77};
    myStack s;

    for(auto v : arr)
    {
        s.push(v);
    }

    cout << boolalpha << s.empty() << endl;
    cout << s.size() << endl;
    cout << s.top() << endl;

    cout << "==============" << endl;   

    s.pop();
    cout << s.size() << endl;
    cout << s.top() << endl;

    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    cout << endl;

    return 0;
}
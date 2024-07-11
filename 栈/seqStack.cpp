//顺序栈
#include <iostream>

class SeqStack
{
public:
    SeqStack(int size = 0)
        : mTop(0)
        , mCap(size)
    {
        mpStack = new int[mCap];
    }
    ~SeqStack()
    {
        delete[] mpStack;
        mpStack = nullptr; //***
    }

    void push(int val)
    {
        if(mTop == mCap)
        {
            expand(2 * mCap);
        }
        mpStack[mTop++] = val;
    }

    void pop()
    {
        if(mTop == 0)
        {
            throw "stack is empty";
        }
        mTop--;
    }

    int top() const
    {
        if(mTop == 0)
        {
            throw "stack is empty";
        }
        return mpStack[mTop - 1];
    }

    bool empty() const
    {
        return mTop == 0;
    }

    int size() const
    {
        return mTop;
    }
private:
    void expand(int size)
    {
        int* p = new int[size];
        memcpy(p, mpStack, sizeof(int) * mTop);
        delete[] mpStack;
        mpStack = p;
        mCap = size;
    }
private:
    int* mpStack; //指向顺序栈起始位置的指针
    int mTop; //栈顶位置
    int mCap; //栈的容量
};

int main(int argc, char** argv)
{
    SeqStack s;
    srand(time(0));
    for(int i = 0; i < 6; ++i)
    {
        s.push(rand() % 100);
    }
    std::cout << s.size() << " " << std::endl;
    while(!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
    return 0;
}

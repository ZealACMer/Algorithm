#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>

using namespace std;

class PriorityQueue
{
public:
    using Comp = function<bool(int, int)>;
    PriorityQueue(int cap = 20, Comp comp = greater<int>()) 
                : size_(0), cap_(cap), comp_(comp)
                {
                    que_ = new int[cap_];
                }
    PriorityQueue(Comp comp) : size_(0), cap_(20), comp_(comp)
    {
        que_ = new int[cap_];
    }
    ~PriorityQueue()
    {
        delete []que_;
        que_ = nullptr;
    }


    void push(int val)
    {
        if(size_ == cap_)
        {
            int* p = new int[2 * cap_];
            memcpy(p, que_, cap_ * sizeof(int));
            delete[] que_;
            que_ = p;
            cap_ *= 2;
        }

        if(size_ == 0) //插入第一个元素，不需要为了排序，进行元素调整
        {
            que_[size_] = val;
        }
        else
        {
            siftUp(size_, val);
        }
        ++size_;
    }

    void pop()
    {
        if(size_ == 0)
        {
            throw "container is empty!";
        }
        --size_;
        if(size_ > 0)
        {
            siftDown(0, que_[size_]);
        }
    }

    bool empty() const
    {
        return size_ == 0;
    }

    int top() const
    {
        if(size_ == 0)
        {
            throw "container is empty!";
        }
        return que_[0];
    }

    int size() const
    {
        return size_;
    }
private:
    //入堆元素向上调整 O(logn)，val要和之前的i个元素进行比较
    void siftUp(int i, int val)
    {
        while(i > 0)
        {
            int father = (i - 1) / 2; //计算到根节点
            if(comp_(val, que_[father]))
            {
                que_[i] = que_[father];
                i = father;
            }
            else
            {
                break;
            }
        }
        que_[i] = val;
    }

    void siftDown(int i, int val)
    {
        while(i < size_ / 2)
        {
            int child = 2 * i + 1; //第i个节点的左孩子
            if(child  + 1 < size_ && comp_(que_[child + 1], que_[child]))
            {
                //如果第i个节点的右孩子的值大于左孩子的值，child记录右孩子的下标
                child = child + 1;
            }
            if(comp_(que_[child], val))
            {
                que_[i] = que_[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        que_[i] = val;
    }

    int* que_;
    int size_;
    int cap_;
    Comp comp_;

};

int main()
{
    //PriorityQueue maxQue;
    PriorityQueue minQue([](int a, int b){return a < b;});
    cout << boolalpha << minQue.empty() << endl;
    cout << minQue.size() << endl;
    srand(time(0));

    for(int i = 0; i < 10; ++i)
    {
        minQue.push(rand() % 100);
    }

    cout << boolalpha << minQue.empty() << endl;
    cout << minQue.size() << endl;

    while(!minQue.empty())
    {
        cout << minQue.top() << " ";
        minQue.pop();
    }
    cout << endl;

    return 0;
}
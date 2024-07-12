//堆
#include <iostream>
#include <functional>
#include <stdlib.h>
#include <time.h>

class PriorityQueue
{
public:
    using Comp = std::function<bool(int, int)>;
    PriorityQueue(int cap = 20, Comp comp = std::greater<int>())
        : size_(0)
        , cap_(cap)
        , comp_(comp)
    {
        que_ = new int[cap_];
    }

   PriorityQueue(Comp comp)
        : size_(0)
        , cap_(20)
        , comp_(comp)
    {
        que_ = new int[cap_];
    }
    ~PriorityQueue()
    {
        delete[] que_;
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

        if(size_ == 0)
        {
            //只有一个元素，不用进行堆的上浮调整
            que_[size_] = val;
        }
        else
        {
            //堆里有多个元素，需要进行上浮调整
            siftUp(size_, val);
        }
        ++size_;
    }

    void pop()
    {
        if(size_ == 0)
        {
            throw "heap is empty";
        }
        --size_;
        if(size_ > 0)
        {
            //删除堆顶元素，还有剩余的元素，需要进行堆的下沉调整
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
            throw "heap is empty";
        }
        return que_[0];
    }

    int size() const
    {
        return size_;
    }
private:
    //入堆的上浮调整O(logn) 空复O(1)
    void siftUp(int i, int val)
    {
        while(i > 0) //最多计算到根节点(0号位)
        {
            int father = (i - 1) / 2;
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

    //出堆下沉调整O(logn) 空复O(1)
    void siftDown(int i, int val)
    {
        //下沉不能超过最后一个有孩子的节点
        while(i < size_ / 2)
        {
            int child = 2 * i + 1; //左孩子
            if(child + 1 < size_ && comp_(que_[child + 1], que_[child]))
            {
                //如果右孩子的值大于左孩子，child记录右孩子的下标
                child = child + 1;
            }
            if(comp_(que_[child], val))
            {
                que_[i] = que_[child];
                i = child;
            }
            else
            {
                break; //已经满足堆的性质，提前结束
            }
        }
        que_[i] = val;
    }
private:
    int* que_; //指向动态扩容的数组
    int size_; //数组元素的个数
    int cap_; //数组的总空间大小
    Comp comp_; //比较器对象
};

int main()
{
    //PriorityQueue que; //基于大根堆，实现的优先级队列

    PriorityQueue que([](int a, int b){return a < b;}); //基于小根堆，实现的优先级队列

    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        que.push(rand() % 100);
    }

    while(!que.empty())
    {
        std::cout << que.top() << std::endl;
        que.pop();
    }

    std::cout << std::endl;
    return 0;
}


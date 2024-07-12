//循环队列
#include <iostream>

class Queue
{
public:
    Queue(int size = 10)
        : cap_(size)
        , front_(0)
        , rear_(0)
        , size_(0)
    {
        pQue_ = new int[cap_];
    }
    ~Queue()
    {
        delete[] pQue_;
        pQue_ = nullptr;
    }

    //入队O(1)
    void push(int val)
    {
        if((rear_ + 1) % cap_ == front_)
        {
            expand(2 * cap_);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        ++size_;
    }

    //出队O(1)
    void pop()
    {
        if(front_ == rear_)
        {
            throw "queue is empty";
        }
        front_ = (front_ + 1) % cap_;
        --size_;
    }

    //取队头元素O(1)
    int front() const
    {
        if(front_ == rear_)
        {
            throw "queue is empty";
        }
        return pQue_[front_];
    }

    //取队尾元素O(1)
    int back() const
    {
        if(front_ == rear_)
        {
            throw "queue is empty";
        }
        return pQue_[(rear_ - 1 + cap_) % cap_];
    }

    //判空O(1)
    bool empty() const
    {
        return front_ == rear_;
    }

    //返回队列的元素个数O(1)
    int size() const 
    {
        return size_;
    }

    //遍历队列的元素O(n)
    void show() const
    {
        for(int i = front_; i != rear_; i = (i + 1) % cap_)
        {
            std::cout << pQue_[i] << " ";
        }
        std::cout << std::endl;
    }
private:
    void expand(int size)
    {
        int* p = new int[size];
        int i = 0; 
        for(int j = front_; j != rear_; j = (j + 1) % cap_)
        {
            p[i++] = pQue_[j];
        }

        delete[] pQue_;
        pQue_ = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }
private:
    int* pQue_;
    int cap_; //队列的容量
    int front_; //队头
    int rear_; //队尾
    int size_; //队列元素个数
};

int main(int argc, char** argv)
{
    srand(time(0));
    Queue q;
    for(int i = 0; i < 10; ++i)
    {
        q.push(rand() % 100);
    }
    q.show();
    std::cout << q.size() << std::endl;

    std::cout << q.front() << std::endl;
    std::cout << q.back() << std::endl;

    q.push(100);
    q.show();

    q.pop();
    q.show();

    while(!q.empty())
    {
        q.pop();
    }
    std::cout << q.size() << std::endl;
    q.show();
    return 0;
}

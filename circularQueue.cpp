#include <iostream>

using namespace std;

class CircularQueue
{
public:
    CircularQueue(int size = 10) : cap_(size), front_(0), rear_(0), size_(0)
    {
        cQue_ = new int[cap_];
    }

    ~CircularQueue()
    {
        delete[] cQue_;
        cQue_ = nullptr;
    }

    //入队 O(1)
    void push(int val)
    {
        if((rear_ + 1) % cap_ == front_)
        {
            expand(2 * cap_);
        }
        cQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        ++size_;
    }

    //出队 O(1)
    void pop()
    {
        if(front_ == rear_)
        {
            throw "queue is empty!";
        }
        front_ = (front_ + 1) % cap_;
        --size_;
    }

    //取队头元素 O(1)
    int front() const
    {
        if(front_ == rear_)
        {
            throw "queue is empty!";
        }
        return cQue_[front_];
    }

    //取队尾元素 O(1)
    int back() const
    {
        if(front_ == rear_)
        {
            throw "queue is empty!";
        }
        return cQue_[(rear_ - 1 + cap_) % cap_];
    }

    //判断队列是否为空 O(1)
    bool empty() const
    {
        return front_ == rear_;
    }

    //获取队列元素的个数 O(1)
    int size() const
    {
        return size_;
    }

    //打印队列的所有元素
    void show() const
    {
        for(int i = front_; i != rear_; i = (i + 1) % cap_)
        {
            cout << cQue_[i] << " ";
        }
        cout << endl;
    }

private:
    
    void expand(int size)
    {
        int* p = new int[size];
        int i = 0;
        int j = front_;
        for(; j != rear_; i++, j = (j + 1) % cap_)
        {
            p[i] = cQue_[j];
        }
        delete []cQue_;
        cQue_ = p;
        cap_ = size;
        front_ = 0;
        rear_ = i;
    }

private:
    int* cQue_;
    int cap_;
    int front_;
    int rear_;
    int size_;
};

int main()
{
    int arr[] = {12, 4, 25, 3, 35, 24, 8};
    CircularQueue cque;

    for(auto v : arr)
    {
        cque.push(v);
    }

    cout << "size: " << cque.size() << endl;
    cout << "if empty: "<<boolalpha << cque.empty() << endl;
    cout << "back element: " << cque.back() << endl;
    cout << "front element: " << cque.front() << endl;
    cque.show();

    cque.pop();
    cque.show();

    return 0;
}
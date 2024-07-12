//链式队列
#include <iostream>

class LinkQueue
{
public:
    LinkQueue(int size = 0)
        : size_(0)
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->prev_ = head_;
    }
    ~LinkQueue()
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            head_->next_ = p->next_;
            p->next_->prev_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

    //入队O(1)，队尾插入元素
    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_;
        node->prev_ = head_->prev_;
        head_->prev_->next_ = node;
        head_->prev_ = node;
        ++size_;
    }

    //出队O(1)，队头删除元素
    void pop()
    {
        Node* p = head_->next_;
        head_->next_ = p->next_;
        p->next_->prev_ = head_;
        delete p;
        --size_;
    }

    //获取队头元素O(1)
    int front() const
    {
        if(head_->next_ == head_)
        {
            throw "queue is empty";
        }
        return head_->next_->data_;
    }

    //获取队尾元素O(1)
    int back() const
    {
        if(head_->next_ == head_)
        {
            throw "queue is empty";
        }
        return head_->prev_->data_;
    }

    //判空O(1)
    bool empty() const
    {
        return head_->next_ == head_;
    }

    //队列元素个数O(1)
    int size() const
    {
        return size_;
    }

    //遍历元素O(n)
    void show() const
    {
        auto p = head_->next_;
        while(p != head_)
        {
            std::cout << p->data_ << " ";
            p = p->next_;
        }   
        std::cout << std::endl;
    }
private:
    struct Node
    {
        Node(int data = 0)
            : data_(data)
            , prev_(nullptr)
            , next_(nullptr)
        {}
        int data_;
        Node* prev_;
        Node* next_;
    };

    Node* head_; //指向头节点
    int size_; //元素个数
};

int main(int argc, char** argv)
{
    srand(time(0));
    LinkQueue q;
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

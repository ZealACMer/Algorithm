#include <iostream>

using namespace std;

class LinkQueue
{
public:
    LinkQueue()
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

    //入队 O(1)
    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_;
        node->prev_ = head_->prev_;
        head_->prev_->next_ = node;
        head_->prev_ = node;
    }

    //出队 O(1)
    void pop()
    {
        Node* p = head_->next_;
        head_->next_ = p->next_;
        p->next_->prev_ = head_;
        delete p;
    }
    
    //获取队头元素 O(1)
    int front() const
    {
        if(head_->next_ == head_)
        {
            throw "queue is empty!";
        }
        return head_->next_->data_;
    }

    //获取队尾元素 O(1)
    int back() const
    {
        if(head_->next_ == head_)
        {
            throw "queue is empty!";
        }
        return head_->prev_->data_;
    }

    //判空 O(1)
    bool empty() const
    {
        return head_->next_ == head_;
    }


private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr), prev_(nullptr){}
        int data_;
        Node* next_;
        Node* prev_;
    };
    Node* head_;
};

int main()
{
    int arr[] = {12, 24, 35, 33, 56, 88, 27, 83};
    LinkQueue lQue;

    for(int v : arr)
    {
        lQue.push(v);
    }
    
    cout << lQue.front() << endl;
    cout << lQue.back() << endl;
    cout << boolalpha << lQue.empty() << endl;

    while(!lQue.empty())
    {
        cout << lQue.front() << endl;
        lQue.pop();
    }
    cout << lQue.empty() << endl;

    return 0;
}
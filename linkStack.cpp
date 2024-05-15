#include <iostream>
#include <string>
#include <stack>
using namespace std;

class linkStack
{
public:
    linkStack() : size_(0)
    {
        head_ = new Node();
    }
    ~linkStack()
    {
        Node* p = head_;
        while(p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

    //入栈 O(1)
    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        ++size_;
    }

    //出栈 O(1)
    void pop()
    {
        if(head_->next_ == nullptr)
        {
            throw "stack is empty!";
        }
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        --size_;
    }

    //获取栈顶元素 O(1)
    int top() const
    {
        if(head_->next_ == nullptr)
        {
            throw "stack is empty!";
        }
        return head_->next_->data_;

    }

    //判断栈是否为空
    bool empty() const
    {
        return head_->next_ == nullptr;
    }

    //返回栈的元素个数 O(1)
    int size() const
    {
        return size_;
    }

private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr){}
        int data_;
        Node* next_;
    };
    Node* head_;
    int size_;
};

int main()
{
    int arr[] = {12, 43, 35, 78, 33, 43, 23};
    linkStack s;

    for(auto v : arr)
    {
        s.push(v);
    }

    cout << "stack size: " << s.size() << endl;
    cout << "top element: " << s.top() << endl;
    while(!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    cout << "stack size: " << s.size() << endl;
    return 0;
}
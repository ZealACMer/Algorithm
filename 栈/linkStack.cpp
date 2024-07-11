//链式栈
#include <iostream>
#include <string>
#include <stack>

class LinkStack
{
public:
    LinkStack()
        : size_(0)
    {
        head_ = new Node();
    }
    ~LinkStack()
    {
        Node* p = head_;
        while(p)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        ++size_;
    }

    void pop()
    {
        if(head_->next_ == nullptr)
        {
            throw "stack is empty";
        }
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        --size_;
    }

    int top() const
    {
        if(head_->next_ == nullptr)
        {
            throw "stack is empty";
        }
        return head_->next_->data_;
    }

    bool empty() const
    {
        return head_->next_ == nullptr;
    }

    int size() const
    {
        return size_;
    }
private:
    struct Node
    {
        Node(int data = 0)
            : data_(data)
            , next_(nullptr)
        {}
        int data_;
        Node* next_;
    };

    Node* head_;
    int size_;
};

int main()
{
    LinkStack s;
    srand(time(0));
    for(int i = 0; i < 6; ++i)
    {
        s.push(rand() % 100);
    }

    std::cout << s.size() << std::endl;

    while(!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
    std::cout << s.size() << std::endl;
}

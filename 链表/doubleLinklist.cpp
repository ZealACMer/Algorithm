//双向链表
#include <iostream>
#include <stdlib.h>
#include <time.h>

struct Node
{
    Node(int data = 0)
        : data_(data)
        , next_(nullptr)
        , prev_(nullptr)
    {}
    int data_;
    Node* next_;
    Node* prev_;
};

class doubleLinklist
{
public:
    doubleLinklist()
    {
        head_ = new Node();
    }
    ~doubleLinklist()
    {
        Node* p = head_;
        while(p)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

    //在头部插入元素O(1)
    void insertHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->prev_ = head_;
        if(head_->next_)
        {
            head_->next_->prev_ = node;
        }
        head_->next_ = node;
    }

    //在尾部插入元素O(n)
    void insertTail(int val)
    {
       Node* p= head_;
       while(p->next_)
       {
            p = p->next_;
       }
       Node* node = new Node(val);
       node->prev_ = p;
       p->next_ = node;
    }

    //删除元素O(n)
    void remove(int val)
    {
        Node* p = head_->next_;
        while(p)
        {
            if(p->data_ == val)
            {
                auto next = p->next_;
                p->prev_->next_ = p->next_;
                if(p->next_)
                {
                    p->next_->prev_ = p->prev_;
                }
                delete p;
                p = next;
            }
            else
            {
                p = p->next_;
            }
        }
    }

    //查找元素O(n)
    bool find(int val) const
    {
        Node* p = head_->next_;
        while(p)
        {
            if(p->data_ == val)
            {
                return true;
            }
            else
            {
                p = p->next_;
            }
        }
        return false;
    }

    //输出双向链表的元素
    void show() const 
    {
        Node* p = head_->next_;
        while(p)
        {
            std::cout << p->data_ << " ";
            p = p->next_;
        }
        std::cout << std::endl;
    }
private:
    Node* head_;
};

int main(int argc, char** argv)
{
    doubleLinklist dlist;
    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        dlist.insertTail(rand() % 100);
    }

    dlist.show();

    dlist.insertHead(100);
    dlist.insertHead(200);
    dlist.show();

    std::cout << std::boolalpha << dlist.find(100) << std::endl;

    dlist.remove(100);
    dlist.show();
    return 0;
}

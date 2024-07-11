//双向循环链表
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

class circularDoubleLinklist
{
public:
    circularDoubleLinklist()
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->prev_ = head_;
    }
    ~circularDoubleLinklist()
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
    }

    //头插法O(1)
    void insertHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->prev_ = head_;
        head_->next_->prev_ = node;
        head_->next_ = node;
    }

    //尾插法O(1)
    void insertTail(int val)
    {
        Node* node = new Node(val);
        Node* p = head_->prev_;
        node->prev_ = p;
        p->next_ = node;
        node->next_ = head_;
        head_->prev_ = node;
    }

    //删除元素O(n)
    void remove(int val)
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            if(p->data_ == val)
            {
                auto next = p->next_;
                p->prev_->next_ = p->next_;
                p->next_->prev_ = p->prev_;
                delete p;
                p = next;
            }
            else
            {
                p = p->next_;
            }
        }
    }
    
    //搜索元素O(n)
    bool find(int val)
    {
        Node* p = head_->next_;
        while(p != head_)
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

    //输出链表的元素
    void show()
    {
        Node* p = head_->next_;
        while(p != head_)
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
    circularDoubleLinklist cdlist;
    for(int i = 0; i < 10; ++i)
    {
        cdlist.insertTail(rand() % 100);
    }
    cdlist.show();

    cdlist.insertHead(100);
    cdlist.insertHead(200);
    cdlist.show();

    std::cout << std::boolalpha << cdlist.find(100) << std::endl;

    cdlist.remove(200);
    cdlist.show();
    return 0;
}

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr), prev_(nullptr){}
    int data_;
    Node* next_;
    Node* prev_;
};

//双向循环链表
class circularDoubleList
{
public:
    circularDoubleList()
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->prev_ = head_;
    }
    ~circularDoubleList()
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

    //头插法 O(1)
    void insertHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->prev_ = head_;
        head->next_->prev_ = node;
        head_->next_ = node;
    }

    //尾插法 O(1)
    void insertTail(int val)
    {
        Node* node = new Node(val);
        Node* p = head_->prev_;
        node->prev_ = p;
        p->next_ = node;
        node->next_ = head_;
        head_->prev_ = node;              
    }

    //删除元素 O(n)
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

    //搜索元素 O(n)
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
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    Node* head_;
};

int main(int argc, char* argv[])
{
    circularDoubleList cdlist;

    for(int i = 0; i < 10; ++i)
    {
        int val = rand() % 100;
        cdlist.insertTail(val);
    }
    cdlist.show();

    cdlist.insertHead(100);
    cdlist.insertHead(100);
    cdlist.show();

    cout << boolalpha << cdlist.find(100) << endl;

    cdlist.remove(100);
    cdlist.show();

    return 0;
}
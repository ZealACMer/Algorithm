#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//节点类型
struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr){}
    int data_;
    Node* next_;
};

//单链表代码实现
class Clist
{
public:
    Clist()
    {
        //初始化头节点
        head_ = new Node();
    }
    ~Clist()
    {
        Node* p = head_;
        while(p)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }

public:
    //在链表尾部插入元素O(n)
    void insertTail(int val)
    {
        Node* p = head_;
        while(p->next_)
        {
            p = p->next_;
        }

        Node* node = new Node(val);
        p->next_ = node;
    }

    //在链表头部插入元素O(1)
    void insertHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    //删除值为val的节点O(n)
    void remove(int val)
    {
        Node* q = head_;
        Node* p = head_->next_;
        while(p)
        {
            if(p->data_ == val)
            {
                q->next_ = p->next_;
                delete p;
                p = q->next_;
            }
            else
            {
                q = p;
                p = p->next_;
            }
        }
    }

    //判断是否有值为val的元素O(n)
    bool find(int val)
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

    Node* getHead()
    {
        return head_;
    }

private:
    Node* head_;
};

int main()
{
    Clist linklist;
    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        int val = rand() % 100;
        linklist.insertTail(val);
    }

    for(auto p = linklist.getHead(); p; p = p->next_)
    {
        cout << p->data_ << " ";
    }
    cout << endl;

    linklist.insertHead(1000);

    for(auto p = linklist.getHead(); p; p = p->next_)
    {
        cout << p->data_ << " ";
    }
    cout << endl;

    cout << boolalpha << linklist.find(1000) << endl;

    linklist.remove(1000);

    for(auto p = linklist.getHead(); p; p = p->next_)
    {
        cout << p->data_ << " ";
    }
    cout << endl;

}
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct Node
{
    Node(int data) : data_(data), left_(nullptr), right_(nullptr)
    {

    }
    int data_;
    Node* left_;
    Node* right_;
};

class BSTree
{
public:
    BSTree(Node* root = nullptr) : root_(root)
    {

    }

    ~BSTree()
    {
        if(root_)
        {
            queue<Node*> q;
            q.push(root_);
            while(!q.empty())
            {
                Node* front = q.front();
                q.pop();
                if(front->left_)
                {
                    q.push(front->left_);
                }
                if(front->right_)
                {
                    q.push(front->right_);
                }
                delete front;
            }
        }
    }

    void insert(const int& val)
    {
        if(!root_)
        {
            root_ = new Node(val);
            return;
        }

        Node* parent = nullptr;
        Node* cur = root_;
        while(cur)
        {
            if(cur->data_ == val) //不插入值相同的元素
            {
                return;
            }
            else if(cur->data_ < val)
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                parent = cur;
                cur = cur->left_;
            }
        }
        if(val < parent->data_)
        {
            parent->left_ = new Node(val);
        }
        else
        {
            parent->right_ = new Node(val);
        }
    }

    void remove(const int& val)
    {
        if(!root_)
        {
            return;
        }

        Node* parent = nullptr;
        Node* cur = root_;
        while(cur)
        {
            if(cur->data_ == val)
            {
                break;
            }
            else if(cur->data_ < val)
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                parent = cur;
                cur = cur->left_;
            }
        }

        //未找到相应的节点
        if(cur == nullptr)
        {
            return;
        }

        if(cur->left_ && cur->right_)
        {
            parent = cur;
            Node* pre = cur->left_;
            while(pre->right_)
            {
                parent = pre;
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre;
        }

        //cur指向需被删除节点，parent指向其父节点
        Node* child = cur->left_;
        if(!child)
        {
            child = cur->right_;
        }
        if(!parent) //特殊情况，表示删除的是根节点
        {
            root_ = child;
        }
        else
        {
            if(parent->left_ == cur)
            {
                parent->left_ = child;
            }
            else
            {
                parent->right_ = child;
            }
        }
        delete cur;
    }


    bool query(const int& val)
    {
        Node* cur = root_;
        while(cur)
        {
            if(cur->data_ == val)
            {
                return true;
            }
            else if(cur->data_ < val)
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
        }
        return false;
    }

    void preOrder()
    {
        cout << "非递归前序遍历：";
        if(!root_)
        {
            return;
        }
        stack<Node*> s;
        s.push(root_);
        while(!s.empty())
        {
            Node* top = s.top();
            s.pop();
            cout << top->data_ << " ";
            if(top->right_)
            {
                s.push(top->right_);
            }
            if(top->left_)
            {
                s.push(top->left_);
            }
        }
        cout << endl;
    }

    void inOrder()
    {
        cout << "非递归中序遍历：";
        if(!root_)
        {
            return;
        }
        stack<Node*> stk;
        Node* cur = root_;
        while(!stk.empty() || cur)
        {
            if(cur)
            {
                stk.push(cur);
                cur = cur->left_;
            }
            else
            {
                Node* top = stk.top();
                stk.pop();
                cout << top->data_ << " ";
                cur = top->right_;
            }
        }
        cout << endl;
    }

    void postOrder()
    {
        cout << "非递归后序遍历：" << endl;
        if(!root_)
        {
            return;
        }
        stack<Node*> stk1;
        stack<Node*> stk2;
        stk1.push(root_);
        while(!stk1.empty())
        {
            Node* top = stk1.top();
            stk1.pop();

            stk2.push(top);

            if(top->left_)
            {
                stk1.push(top->left_);
            }
            if(top->right_)
            {
                stk1.push(top->right_);
            }
        }
        while(!stk2.empty())
        {
            cout << stk2.top()->data_ << " ";
            stk2.pop();
        }
        cout << endl;
    }

    void levelOrder()
    {
        cout << "非递归层序遍历：";
        if(!root_)
        {
            return;
        }
        queue<Node*> q;
        q.push(root_);
        while(!q.empty())
        {
            Node* front = q.front();
            q.pop();
            cout << front->data_ << " ";
            if(front->left_)
            {
                q.push(front->left_);
            }
            if(front->right_)
            {
                q.push(front->right_);
            }
        }
        cout << endl;
    }

    //求二叉树的高度
    int height(Node* node)
    {
        if(!node) return 0;
        int l = height(node->left_);
        int r = height(node->right_);
        return l > r ? l + 1 : r + 1;
    }

    //求二叉树节点的个数
    int nodeTotalNum(Node* node)
    {
        if(!node) return 0;
        int l = nodeTotalNum(node->left_);
        int r = nodeTotalNum(node->right_);
        return l + r + 1;
    }

    //寻找BST树中节点值满足区间[i, j]的节点
    void findValues(Node* node, vector<int>& vec, int i, int j)
    {
        if(!node)
        {
            if(node->data_ > i)
            {
                findValues(node->left_, vec, i, j);
            }

            if(node->data_ >= i && node->data_ <= j)
            {
                vec.push_back(node->data_); //存储满足取值区间的节点
            }

            if(node->data_ < j)
            {
                findValues(node->right_, vec, i, j);
            }
        }
    }

    //判断二叉树是否为BST树
    bool isValidBST(Node* root) {
        return dfs(root, INT_MIN, INT_MAX);
    }

    bool dfs(Node* root, long long minv, long long maxv) {
        if(!root) return true;
        if(root->data_ < minv || root->data_ > maxv) return false;
        return dfs(root->left_, minv, root->data_ - 1ll) && dfs(root->right_, root->data_ + 1ll, maxv);
    }
    Node* root_;
};

int main()
{
    BSTree bst(new Node(40));
    Node* node1 = new Node(20);
    Node* node2 = new Node(60);
    Node* node3 = new Node(30);
    Node* node4 = new Node(40);

    bst.root_->left_ = node1;
    bst.root_->right_ = node2;
    node1->left_ = node3;
    node1->right_ = node4;

    cout << bst.height(bst.root_) << endl;

    bst.preOrder();
    return 0; 
}
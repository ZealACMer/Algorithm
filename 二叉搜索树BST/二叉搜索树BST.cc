/*
BST通常指的是二叉搜索树（Binary Search Tree），这是一种数据结构，它具有以下特性：
1. 若任意节点的左子树不为空，则左子树上所有节点的值均小于它的节点值。
2. 若任意节点的右子树不为空，则右子树上所有节点的值均大于它的节点值。
3. 任意节点的左、右子树也分别为二叉搜索树。
4. 没有键值相等的节点。

这种结构使得在树中查找、插入和删除操作都相对高效。二叉搜索树的查找操作平均时间复杂度为O(logn)，
但在最坏的情况下（树退化成链表）时间复杂度会退化到O(n)。为了提高效率，有时会使用平衡二叉搜索树，
如AVL树或红黑树，它们通过重新排列节点来保持树的平衡，从而保证操作的效率。
*/
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <string>

struct Node
{
    Node(int data) 
        : data_(data), left_(nullptr), right_(nullptr)
    {}
    int data_;
    Node* left_;
    Node* right_;
};

class BSTree
{
public:
    BSTree(Node* root = nullptr) 
        : root_(root)
    {}

    ~BSTree()
    {
        if(root_)
        {
            std::queue<Node*> q;
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
        delete cur; //1.待删除节点有左右孩子，转换成2和3 2.有左孩子 3.有右孩子 4.无孩子
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
        std::cout << "非递归前序遍历：";
        if(!root_)
        {
            return;
        }
        std::stack<Node*> s;
        s.push(root_);
        while(!s.empty())
        {
            Node* top = s.top();
            s.pop();
            std::cout << top->data_ << " ";
            if(top->right_)
            {
                s.push(top->right_);
            }
            if(top->left_)
            {
                s.push(top->left_);
            }
        }
        std::cout << std::endl;
    }

    void inOrder()
    {
        std::cout << "非递归中序遍历：";
        if(!root_)
        {
            return;
        }
        std::stack<Node*> stk;
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
                std::cout << top->data_ << " ";
                cur = top->right_;
            }
        }
        std::cout << std::endl;
    }

    void postOrder()
    {
        std::cout << "非递归后序遍历：" << std::endl;
        if(!root_)
        {
            return;
        }
        std::stack<Node*> stk1;
        std::stack<Node*> stk2;
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
            std::cout << stk2.top()->data_ << " ";
            stk2.pop();
        }
        std::cout << std::endl;
    }

    void levelOrder()
    {
        std::cout << "非递归层序遍历：";
        if(!root_)
        {
            return;
        }
        std::queue<Node*> q;
        q.push(root_);
        while(!q.empty())
        {
            Node* front = q.front();
            q.pop();
            std::cout << front->data_ << " ";
            if(front->left_)
            {
                q.push(front->left_);
            }
            if(front->right_)
            {
                q.push(front->right_);
            }
        }
        std::cout << std::endl;
    }

    //求二叉树的高度
    int height(Node* node)
    {
        if(!node) return 0;
        int l = height(node->left_);
        int r = height(node->right_);
        return std::max(l, r) + 1;
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
    void findValues(Node* node, std::vector<int>& vec, int i, int j)
    {
        if(node)
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
    Node* node3 = new Node(10);
    Node* node4 = new Node(30);
    /*
        40
        /\
      20  60
      /\
    10 30
    */

    bst.root_->left_ = node1;
    bst.root_->right_ = node2;
    node1->left_ = node3;
    node1->right_ = node4;

    std::cout << "isValidBST: " << std::endl;
    std::cout << std::boolalpha << bst.isValidBST(bst.root_) << std::endl;

    std::cout << "height: " << std::endl;
    std::cout << bst.height(bst.root_) << std::endl;

    std::cout << "preorder: " << std::endl;
    bst.preOrder();

    std::cout << "inorder: " << std::endl;
    bst.inOrder();

    std::cout << "postorder: " << std::endl;
    bst.postOrder();

    std::cout << "levelOrder: " << std::endl;
    bst.levelOrder();

    std::cout << "nodeTotalNum: " << bst.nodeTotalNum(bst.root_) << std::endl;

    std::vector<int> vc;
    bst.findValues(bst.root_, vc, 1, 50);
    std::cout << "值在1到50之间的节点为: " << std::endl;
    for(auto val : vc)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    bst.insert(100);
    bst.preOrder();

    std::cout << "查找元素100: " << std::endl;
    std::cout << std::boolalpha << bst.query(100) << std::endl;

    bst.remove(20);
    bst.preOrder();

    return 0; 
}

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// 定义AVL树的节点类型
struct Node
{
    Node(int data) : data_(data), left_(nullptr), right_(nullptr), height_(1) {}
    int data_;
    Node* left_;
    Node* right_;
    int height_; //记录节点的高度值
};

// AVL树 二叉平衡搜索树
template<typename T>
class AVLTree
{
public:
    // AVL树的初始化
    AVLTree() : root_(nullptr) {}
    // AVL树的插入操作
    void insert(const T& val)
    {
        root_ = insert(root_, val);
    }
    // AVL树的删除操作
    void remove(const T& val)
    {
        root_ = remove(root_, val);
    }


    // 返回节点的高度值
    int height(Node* node)
    {
        return node == nullptr ? 0 : node->height_;
    }

    // 右旋转操作 以参数node为轴，做右旋转操作，并把新的根节点返回
    Node* rightRotate(Node* node)
    {
        //节点旋转
        Node* child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;

        //高度更新
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        
        //返回旋转后的子树新的根节点
        return child;
    }

    //左旋转操作 以参数node为轴做左旋转操作，并把新的根节点返回
    Node* leftRotate(Node* node)
    {
        //节点旋转
        Node* child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;

        //高度更新
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;

        //返回旋转后的子树新的根节点
        return child;
    }

    //左平衡操作 以参数node为轴先左后右旋转，并把新的根节点返回
    Node* leftBalance(Node* node)
    {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }

    //右平衡操作 以参数node为轴先右后左旋转，并把新的根节点返回
    Node* rightBalance(Node* node)
    {
        node->right_ = rightRotate(node->right_);
        return leftRotate(node);
    }

    // AVL树的插入操作实现
    Node* insert(Node* node, const T& val)
    {
        //找到插入位置，递归结束
        if(!node)
        {
            return new Node(val);
        }
        if(node->data_ > val)
        {
            node->left_ = insert(node->left_, val);
            //在递归回溯时，判断节点是否失衡，node的左子树太高，node失衡了 
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    // 因为左孩子的左子树过高，引发节点失衡
                    node = rightRotate(node);
                }
                else
                {
                    //因为左孩子的右子树过高，引发节点失衡
                    node = leftBalance(node);
                }
            }
        }
        else if(node->data_ < val)
        {
            node->right_ = insert(node->right_, val);
            //在递归回溯时，判断节点是否失衡，node的右子树太高了，导致失衡
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    //因为右孩子的右子树过高，导致失衡
                    node = leftRotate(node);
                }
                else
                {
                    //由于右孩子的左子树过高，导致失衡
                    node = rightBalance(node);
                }
            }
        }
        else
        {
            ; //找到相同节点，无需向下递归，直接向上回溯
        }

        //因为子树中增加了新的节点，在递归回溯时检查更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        return node;
    }

    //删除操作
    Node* remove(Node* node, const T& val)
    {
        if(!node)
        {
            return nullptr;
        }

        if(node->data_ > val)
        {
            node->left_ = remove(node->left_, val);
            // 左子树删除节点，可能造成右子树过高
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    //右孩子的右子树过高
                    node = leftRotate(node);
                }
                else
                {
                    //右孩子的左子树过高
                    node = rightBalance(node);
                }
            }
        }
        else if(node->data_ < val)
        {
            node->right_ = remove(node->right_, val);
            //右子树删除节点，可能导致左子树过高
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    //左孩子的左子树过高
                    node = rightRotate(node);
                }
                else
                {
                    //左孩子的右子树过高
                    node = leftBalance(node);
                }
            }
        }
        else
        {
            //找到目标删除节点，先处理有左右孩子的情况
            if(node->left_ && node->right_)
            {
                //为了避免删除前驱或者后继节点造成节点失衡，优先删除高度较高的一侧
                if(height(node->left_) >= height(node->right_))
                {
                    //删除前驱节点
                    Node* pre = node->left_;
                    while(pre->right_)
                    {
                        pre = pre->right_;
                    }
                    node->data_ = pre->data_;
                    node->left_ = remove(node->left_, pre->data_); //删除前驱节点
                }
                else
                {
                    //删除后继节点
                    Node* post = node->right_;
                    while(post->left_)
                    {
                        post = post->left_;
                    }
                    node->data_ = post->data_;
                    node->right_ = remove(node->right_, post->data_); //删除后继节点
                }
            }
            else //删除的目标节点，最多有一个孩子
            {
                if(node->left_)
                {
                    Node* left = node->left_;
                    delete node;
                    return left;
                }
                else if(node->right_)
                {
                    Node* right = node->right_;
                    delete node;
                    return right;
                }
                else
                {
                    return nullptr;
                }
            }
        }
        //更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        return node;
    }

    //指向根节点
    Node* root_;
};

int main()
{
    AVLTree<int> avl;

    for(int i = 1; i <= 10; ++i)
    {
        avl.insert(new Node(i), i);
    }

    avl.remove(9);
    return 0;
}
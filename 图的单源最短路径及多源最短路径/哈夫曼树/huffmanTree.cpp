//哈夫曼树 - 带权路径长度最短的二叉树，常用于数据压缩
//树的带权路径长度 = 树中所有叶子节点的权值 * 其到根节点的路径长度
//哈夫曼编码采用的是变长编码，其中任意字符的编码，都不会是其他更长字符编码的前缀

/*
文件压缩与解压缩的过程：
发送方 => 读取文件的所有内容，按字节统计数据的权值，生成哈夫曼树 & 利用哈夫曼树生成哈夫曼编码 & 将文件中的数据按字节进行编码，
编码后的内容按位存储到磁盘文件中(除了存储0-1码，还要存储原始文件的字节数据及对应的权值)

接收方 => 使用原始文件的字节数据及对应的权值，生成哈夫曼树，然后还原出原始的文件内容。
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <functional>

using uint = unsigned int;

//哈夫曼树
class HuffmanTree
{
public:
    HuffmanTree() : minHeap_([](Node* n1, Node* n2) -> bool {
        return n1->weight_ > n2->weight_;
    })
    , root_(nullptr)
    {}
    ~HuffmanTree()
    {
        if(root_)
        {
            std::queue<Node*> q;
            q.push(root_);
            while(!q.empty())
            {
                auto front = q.front();
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
        std::cout << "finish destructor" << std::endl;
    }

    //创建哈夫曼树
    void create(std::string str)
    {
        //先统计字符的权值
        std::unordered_map<char, uint> dataMap;
        for(char ch : str)
        {
            dataMap[ch]++;
        }

        //生成节点，放入小根堆中
        for(auto& pair : dataMap)
        {
            minHeap_.push(new Node(pair.first, pair.second));
        }

        while(minHeap_.size() > 1)
        {
            //获取两个权值最小的节点
            Node* n1 = minHeap_.top();
            minHeap_.pop();

            Node* n2 = minHeap_.top();
            minHeap_.pop();

            //生成父节点
            Node* node = new Node('\0', n1->weight_ + n2->weight_);
            node->left_ = n1;
            node->right_ = n2;

            minHeap_.push(node);
        }

        root_ = minHeap_.top(); //哈夫曼树的根节点
        minHeap_.pop(); //清空小根堆
    }

    std::string encode(std::string str)
    {
        getHuffmanCode();

        std::string encode_str;
        for(char ch : str)
        {
            encode_str.append(codeMap_[ch]);
        }
        return encode_str;
    }

    std::string decode(std::string encode)
    {
        std::string decode_str;
        Node* cur = root_;

        for(char ch : encode)
        {
            if(ch == '0')
            {
                cur = cur->left_;
            }
            else
            {
                cur = cur->right_;
            }

            if(!cur->left_ && !cur->right_)
            {
                decode_str.push_back(cur->data_); //string没有emplace_back
                cur = root_;
            }
        }
        return decode_str;
    }
private:
    struct Node
    {
        Node(char data, uint weight)
            : data_(data)
            , weight_(weight)
            , left_(nullptr)
            , right_(nullptr)
        {}

        char data_; //字符数据
        uint weight_; //节点的权值
        Node* left_; //指向左孩子节点
        Node* right_; //指向右孩子节点
    };

    //输出哈夫曼编码
    void getHuffmanCode()
    {
        std::string code;
        getHuffmanCode(root_, code);
        // for(auto& pair : codeMap_)
        // {
        //     std::cout << pair.first << " : " << pair.second << std::endl;
        // }
        // std::cout << std::endl;
    }

    void getHuffmanCode(Node* root, std::string code)
    {
        if(!root->left_ && !root->right_)
        {
            codeMap_[root->data_] = code;
            return;
        }
        getHuffmanCode(root->left_, code + "0");
        getHuffmanCode(root->right_, code + "1");
    }
    Node* root_; //指向根节点
    std::unordered_map<char, std::string> codeMap_; //存储字符对应的哈夫曼编码
    using minHeap = std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>>; //对Node*指针的排序，默认使用地址排序，这里需要重新指定比较规则,如果使用Node的话，Node的生命周期由容器priority_queue指定
    minHeap minHeap_;
};

int main()
{
    std::string str = "ABACDAEFDEGGAHGNNMBHJGUTUYHBBNBNBJHGSUYTUYTRFHGTHJ";

    HuffmanTree htree;
    htree.create(str);

    std::string encode = htree.encode(str);
    std::cout << "encode str: " << encode << std::endl;

    std::string decode = htree.decode(encode);
    std::cout << "decode str: " << decode << std::endl;

    return 0;
}

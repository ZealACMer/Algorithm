#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <functional>

using namespace std;

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

    //创建哈夫曼树
    void create(string str)
    {
        //先统计字符的权值
        unordered_map<char, uint> dataMap;
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

        root_ = minHeap_.top();
        minHeap_.pop();
    }

    string encode(string str)
    {
        getHuffmanCode();

        string encode_str;
        for(char ch : str)
        {
            encode_str.append(codeMap_[ch]);
        }
        return encode_str;
    }

    string decode(string encode)
    {
        string decode_str;
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
                decode_str.push_back(cur->data_);
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
        string code;
        getHuffmanCode(root_, code);
    }

    void getHuffmanCode(Node* root, string code)
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
    unordered_map<char, string> codeMap_; //存储字符对应的哈夫曼编码
    using minHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;
    minHeap minHeap_;
};

int main()
{
    string str = "ABACDAEFDEGGAHGNNMBHJGUTUYHBBNBNBJHGSUYTUYTRFHGTHJ";

    HuffmanTree htree;
    htree.create(str);

    string encode = htree.encode(str);
    cout << "encode str: " << encode << endl;

    string decode = htree.decode(encode);
    cout << "decode str: " << decode << endl;

    return 0;
}
//线性探测哈希表
#include <iostream>

//桶的状态
enum class State
{
    STATE_UNUSE, //从未使用过
    STATE_USING, //正在使用
    STATE_DEL //元素被删除
};

struct Bucket
{
    Bucket(int key = 0, State state = State::STATE_UNUSE)
        : key_(key)
        , state_(state)
    {}

    int key_; //存储的数据
    State state_; //当前状态
};

//线性探测哈希表
class HashTable
{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
        //把用户传入的size调整到最近的比较大的素数上
        if(size != primes_[0])
        {
            for(; primeIdx_ < PRIME_SIZE; ++primeIdx_)
            {
                if(primes_[primeIdx_] >= size)
                {
                    break;
                }
            }
            if(primeIdx_ == PRIME_SIZE)
            {
                --primeIdx_; //传入的size过大，已超过最后一个素数，调整到最后一个素数
            }
        }
        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }
    ~HashTable()
    {
        delete[] table_;
        table_ = nullptr;
    }

    //插入元素
    bool insert(int key)
    {
        double factor = useBucketNum_ * 1.0 / tableSize_;
        if(factor > loadFactor_)
        {
            //扩容
            expand();
        }

        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if(table_[i].state_ != State::STATE_USING)
            {
                table_[i].state_ = State::STATE_USING;
                table_[i].key_ = key;
                ++useBucketNum_;
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (i != idx);
        return false; 
    }

    //删除元素
    bool erase(int key)
    {
        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if(table_[i].state_ == State::STATE_USING && table_[i].key_ == key)
            {
                table_[i].state_ = State::STATE_DEL;
                --useBucketNum_;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != State::STATE_UNUSE && i != idx);
        return true;
    }

    //查询
    bool find(int key)
    {
        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if(table_[i].state_ == State::STATE_USING && table_[i].key_ == key)
            {
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != State::STATE_UNUSE && i != idx);
        return false;
    }
private:
    void expand()
    {
        ++primeIdx_;
        if(primeIdx_ == PRIME_SIZE)
        {
            throw "can't expand";
        }

        int newSize = primes_[primeIdx_];
        Bucket* newTable = new Bucket[newSize];
        for(int i = 0; i < tableSize_; ++i)
        {
            if(table_[i].state_ == State::STATE_USING)
            {
                int idx = table_[i].key_ % newSize;
                int k = idx;
                do
                {
                    if(newTable[k].state_ != State::STATE_USING)
                    {
                        newTable[k].state_ = State::STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % newSize;
                } while (k != idx); 
            }
        }
        delete[] table_;
        table_ = newTable;
        tableSize_ = newSize;
    }
private:
    Bucket* table_; //指向动态开辟的哈希表
    int tableSize_; //哈希表当前的长度
    int useBucketNum_; //已经使用的桶的个数
    double loadFactor_; //哈希表的装载因子

    static const int PRIME_SIZE = 10; //素数表的大小，PRIME_SIZE是一个常量，因此它不需要初始化，因为它的值是编译时常量表达式
    static int primes_[PRIME_SIZE]; //素数表，类外初始化
    int primeIdx_; //当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main(int argc, char** argv)
{
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);

    std::cout << htable.find(32) << std::endl;

    htable.erase(32);
    std::cout << htable.find(32) << std::endl;
    return 0;
}

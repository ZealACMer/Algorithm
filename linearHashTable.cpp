#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//桶的状态
enum State
{
    STATE_UNUSE, //从未使用过的桶
    STATE_USING, //正在使用的桶
    STATE_DEL, //桶的状态为：元素已被删除
};

//桶的类型
struct Bucket
{
    Bucket(int key = 0, State state = STATE_UNUSE) : key_(key), state_(state){}

    int key_;
    State state_;
};

//线性探测哈希表
class HashTable
{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75) 
            : usedBucketNum_(0)
            , loadFactor_(loadFactor)
            , primeIdx_(0)
    {
        //将传入的数字size调整为距离最近的较大素数上
        if(size != primes_[0])
        {
            for(; primeIdx_ < PRIME_SIZE; ++primeIdx_)
            {
                if(primes_[primeIdx_] >= size)
                {
                    break;
                }
            }
            //如果传入的数字过大，超过了最后一个素数，直接使用最后一个素数
            if(primeIdx_ == PRIME_SIZE)
            {
                --primeIdx_;
            }
        }
        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }

    ~HashTable()
    {
        delete []table_;
        table_ = nullptr;
    }

    bool insert(int key)
    {
        double factor = usedBucketNum_ * 1.0 / tableSize_;
        if(factor > loadFactor_)
        {
            expand();
        }

        int idx = key % tableSize_;

        int i = idx;
        do
        {
            if(table_[i].state_ != STATE_USING)
            {
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                ++usedBucketNum_;
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (i != idx);
        
        return false;
    }

    bool erase(int key)
    {
        int idx = key % tableSize_;

        int i = idx;
        do
        {
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                table_[i].state_ = STATE_DEL;
                --usedBucketNum_;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);
        return true;
    }
    
    bool find(int key)
    {
        int idx = key % tableSize_;
        int i = idx;

        do
        {
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);
        return false;
    }

    void show()
    {
        for(int i = 0; i < tableSize_; ++i)
        {
            if(table_[i].state_ == STATE_USING)
            {
                cout << table_[i].key_ << " ";
            }
        }
        cout << endl;
    }

private:
    void expand()
    {
        ++primeIdx_;
        if(primeIdx_ == PRIME_SIZE)
        {
            throw "hashTable is too large, can not expand anymore!";
        }

        int newTableSize = primes_[primeIdx_];
        Bucket* newTable = new Bucket[newTableSize];
        for(int i = 0; i < tableSize_; ++i)
        {
            if(table_[i].state_ == STATE_USING)
            {
                int idx = table_[i].key_ % newTableSize;
                int k = idx;
                do
                {
                    if(newTable[k].state_ != STATE_USING)
                    {
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % newTableSize;
                } while (k != idx);
                
            }
        }
        delete []table_;
        table_ = newTable;
        tableSize_ = newTableSize;
    }

    Bucket* table_;
    int tableSize_;
    int usedBucketNum_;
    double loadFactor_; 

    static const int PRIME_SIZE = 10;
    static int primes_[PRIME_SIZE];
    int primeIdx_; //当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    HashTable hashTable;

    for(int i = 0; i < 10; ++i)
    {
        hashTable.insert(rand() % 100 + 1);
    }
    hashTable.insert(99);

    hashTable.show();

    cout << endl;
    cout << boolalpha << hashTable.find(99) << endl;
    hashTable.erase(99);
    cout << boolalpha << hashTable.find(99) << endl;

    hashTable.show();

    return 0;
}
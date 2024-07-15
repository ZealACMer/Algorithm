//链式哈希表
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class HashTable
{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
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
                --primeIdx_;
            }
        }
        tableSize_ = primes_[primeIdx_];
        table_.resize(tableSize_);
    }

    //增加元素，不能重复插入key
    void insert(int key)
    {
        double factor = useBucketNum_ * 1.0 / tableSize_;
        if(factor > loadFactor_)
        {
            expand();
        }
        int idx = key % tableSize_;
        if(table_[idx].empty())
        {
            ++useBucketNum_;
            table_[idx].emplace_front(key);
        }
        else
        {
            //使用全局的::find泛型算法
            auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
            if(it == table_[idx].end())
            {
                table_[idx].emplace_front(key);
            }
        }
    }

    //删除元素
    void erase(int key)
    {
        int idx = key % tableSize_;
        auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
        if(it != table_[idx].end())
        {
            table_[idx].erase(it);
            if(table_[idx].empty())
            {
                --useBucketNum_;
            }
        }
    }

    //搜索元素
    bool find(int key)
    {
        int idx = key % tableSize_;
        auto it = std::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }
private:
    void expand()
    {
        if(primeIdx_ + 1 == PRIME_SIZE)
        {
            throw "can't expand";
        }
        ++primeIdx_;
        useBucketNum_ = 0;

        std::vector<std::list<int>> oldTable;
        table_.swap(oldTable);
        tableSize_ = primes_[primeIdx_];
        table_.resize(tableSize_);

        for(auto list : oldTable)
        {
            for(auto key : list)
            {
                int idx = key % tableSize_;
                if(table_[idx].empty())
                {
                    ++useBucketNum_;
                }
                table_[idx].emplace_front(key);
            }
        }
    }

private:
    std::vector<std::list<int>> table_;
    int useBucketNum_;
    double loadFactor_; //哈希表的装载因子
    int tableSize_; //哈希表当前的大小

    static const int PRIME_SIZE = 10;
    static int primes_[PRIME_SIZE];
    int primeIdx_;
};

int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main(int argc, char** argv)
{
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);
    htable.insert(1471);

    std::cout << htable.find(1471) << std::endl;

    htable.erase(1471);
    std::cout << htable.find(1471) << std::endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

class LinkHashTable
{
public:
    LinkHashTable(int size = primes_[0], double loadFactor = 0.75)
                : usedBucketNum_(0)
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
        table_.resize(primes_[primeIdx_]);
    }

    void insert(int key)
    {
        double factor = usedBucketNum_ * 1.0 / table_.size();
        if(factor > loadFactor_)
        {
            expand();
        }

        int idx = key % table_.size();
        if(table_[idx].empty())
        {
            ++usedBucketNum_;
            table_[idx].emplace_front(key);
        }
        else
        {
            //使用全局的find函数，非成员函数find
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if(it == table_[idx].end())
            {
                table_[idx].emplace_front(key);
            }
        }
    }

    void erase(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if(it != table_[idx].end())
        {
            table_[idx].erase(it);
            if(table_[idx].empty())
            {
                --usedBucketNum_;
            }
        }
    }

    bool find(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }
private:
    void expand()
    {
        if(primeIdx_ + 1 == PRIME_SIZE)
        {
            throw "linkHashTable can not expand anymore!";
        }
        ++primeIdx_;
        usedBucketNum_ = 0;
        vector<list<int>> oldTable;
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);

        for(auto list : oldTable)
        {
            for(auto key : list)
            {
                int idx = key % table_.size();
                if(table_[idx].empty())
                {
                    ++usedBucketNum_;
                }
                table_[idx].emplace_front(key);
            }
        }
    }

private:
    vector<list<int>> table_;
    int usedBucketNum_;
    double loadFactor_;

    static const int PRIME_SIZE = 10;
    static int primes_[PRIME_SIZE];
    int primeIdx_;
};

int LinkHashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    LinkHashTable linkHashTable;
    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        linkHashTable.insert(rand() % 100 + 1);
    }

    linkHashTable.insert(200);
    linkHashTable.insert(400);
    linkHashTable.insert(200);
    cout << boolalpha << linkHashTable.find(200) << endl;

    linkHashTable.erase(200);
    cout << boolalpha << linkHashTable.find(200) << endl;

    return 0; 
}
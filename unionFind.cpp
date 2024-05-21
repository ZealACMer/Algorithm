#include <iostream>
using namespace std;

const int SIZE = 9;
int parent[SIZE]; //记录每个节点的父节点,进一步优化后，记录树的根节点编号
int level[SIZE]; //记录节点的层高

//并查集查询方法， 返回参数x节点所在树的根节点的编号
int find(int x)
{
    int pos = x;
    while(x != parent[x])
    {
        //更新x为其父节点的编号
        x = parent[x];
    }
    //执行查询操作的时候，将访问过的每个节点的父节点修改成树根x
    parent[pos] = x;
    return x;
}

//并查集合并方法，x和y不在一个集合中，才需要合并，如果已经在一个集合中，不需要合并
void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x != y)
    {
        if(level[x] > level[y])
        {
            parent[y] = x;
        }
        else
        {
            if(level[x] == level[y])
            {
                //y作为合并后的集合树的树根，rank值要加1
                level[y]++;
            }
            parent[x] = y;
        }
    }
}

int main()
{
    for(int i = 0; i < SIZE; ++i)
    {
        parent[i] = i;
        level[i] = 1;
    }

    int x, y;
    for(int i = 0; i < SIZE - 1; ++i)
    {
        merge(i, i + 1);
    }

    cout << boolalpha << (find(2) == find(4)) << endl;

    return 0;
}
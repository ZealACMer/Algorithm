#include <iostream>

const int SIZE = 9;
int parent[SIZE]; //记录每个节点的父节点(经过优化后记录树的根节点的编号)
int height[SIZE]; //记录节点的层高

//并查集查找方法(非递归实现)，返回x节点所在树的根节点的编号
int nonRecursiveFind(int x)
{
    while(x != parent[x])
    {
        x = parent[x];
    }
    return x;
}

//并查集查找方法(递归实现)，返回x节点所在树的根节点的编号
int recursiveFind(int x)
{
    if(x == parent[x])
    {
        return x;
    }
    //将访问过的每个节点的父节点修改成根节点
    return parent[x] = recursiveFind(parent[x]);
}

//并查集合并方法
void merge(int x, int y)
{
    x = recursiveFind(x);
    y = recursiveFind(y);
    if(height[x] > height[y])
    {
        parent[y] = x;
    }
    else
    {
        if(height[x] == height[y])
        {
            height[y]++; //更新合并后的树的高度
        }
        parent[x] = y;
    }
}

int main(int argc, char** argv)
{
    for(int i = 0; i < SIZE; ++i)
    {
        parent[i] = i;
        height[i] = 1;
    }

    int x, y;
    for(int i = 0; i < 6; ++i)
    {
        std::cin >> x >> y;
        merge(x, y);
    }

    std::cout << (recursiveFind(2) == recursiveFind(4) ? "YES" : "NO") << std::endl;
}
/*
1 3
1 2
5 4
2 4
6 8
8 7
YES
*/

/**
 * 使用Kruskal算法求最小生成树
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//边类型定义
struct Edge
{
  Edge(int s, int e, int c)
    : start(s)
    , end(e)
    , cost(c)
  {}
  int start; //边的起点
  int end; //边的终点
  int cost; //边的权值  
};

const int SIZE = 1000;
int parent[SIZE];
int height[SIZE];

//并查集查询算法
int find(int x)
{
    if(x == parent[x])
    {
        return x;
    }
    return parent[x] = find(parent[x]);
}

int main(int argc, char** argv)
{
    for(int i = 0; i < SIZE; ++i)
    {
        parent[i] = i;
        height[i] = 1;
    }

    vector<Edge> edges;
    int n;
    cin >> n;

    char s, e;
    int c;
    for(int i = 0; i < n; ++i)
    {
        std::cin >> s >> e >> c;
        edges.emplace_back(s, e, c);

    }
 
    //将所有的边按照权值由小到大排序
    std::sort(edges.begin(), edges.end(),[](Edge& a, Edge& b) -> bool {
        return a.cost < b.cost;
    });

    //按照权值从小到大开始选择边
    for(int i = 0; i < edges.size(); ++i)
    {
        int x = find(edges[i].start);
        int y = find(edges[i].end);
        if(x != y)
        {
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
            printf("%c -> %c cost:%d\n", edges[i].start, edges[i].end, edges[i].cost);
        }
    }
    return 0;
}

/*
10
A B 6
A C 1
A D 5
B C 5
C D 5
B E 3
C E 6
C F 4
E F 6
D F 2
A -> C cost:1
D -> F cost:2
B -> E cost:3
C -> F cost:4
B -> C cost:5
*/




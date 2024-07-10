#include <iostream>
#include <vector>
#include <algorithm>

struct Road
{
    Road(int a, int b, int c)
        : u(a)
        , v(b)
        , w(c)
    {}
    int u;
    int v;
    int w;
};

const int SIZE = 10005;
int parent[SIZE];
int height[SIZE];

int find(int x)
{
    if(x == parent[x])
    {
        return x;
    }
    return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
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
                height[y]++;
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
        height[i] = 1;
    }
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    std::vector<Road> roads;
    int u, v, w;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        roads.emplace_back(u, v, w);
    }

    sort(roads.begin(), roads.end(), [](Road& a, Road& b){
        return a.w < b.w;
    });

    for(int i = 0; i < roads.size(); ++i)
    {
        merge(roads[i].u, roads[i].v);
        //s区域和t区域第一次有通路了
        //使得经过道路的拥挤度的最大值最小
        if(find(s) == find(t))
        {
            std::cout << roads[i].w << std::endl;
            break;
        }
    }
    return 0;
}
/*
3 3 1 3
1 2 2
2 3 1
1 3 3 
2
*/

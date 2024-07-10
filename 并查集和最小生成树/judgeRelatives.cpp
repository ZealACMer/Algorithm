#include <iostream>

int n, m, p;
const int SIZE = 5001;
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

int main(int argc, char** argv)
{
    std::cin >> n >> m >> p;
    for(int i = 0; i < n; ++i)
    {
        parent[i] = i;
        height[i] = 1;
    }

    int x, y;
    for(int i = 0; i < m; ++i)
    {
        std::cin >> x >> y;
        merge(x, y);
    }

    for(int i = 0; i < p; ++i)
    {
        std::cin >> x >> y;
        x = find(x);
        y = find(y);
        if(x == y)
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }
    }
    return 0;
}
/*
8 6 6
1 3
1 2
5 4
2 4
6 8
8 7
2 4
YES
2 7
NO
*/

//Floyd弗洛伊德算法 - 支持负权边 求解多源最短路径(所有顶点到其他所有顶点的最短路径) O(n^3)
#include <iostream>
#include <vector>

using uint = unsigned int;
const uint INF = INT_MAX; //设置为无符号整数，上限为40多亿，防止有符号整数INT_MAX的运算溢出

int main(int argc, char* argv[])
{
    //图的邻接矩阵存储
    std::vector<std::vector<uint>> graph = 
    {
        {0, 6, 3, INF, INF, INF},
        {6, 0, 2, 5, INF, INF},
        {3, 2, 0, 3, 4, INF},
        {INF, 5, 3, 0, 2, 3},
        {INF, INF, 4, 2, 0, 5},
        {INF, INF, INF, 3, 5, 0},
    };

    //加入新的顶点
    for(int k = 0; k < graph.size(); ++k)
    {
        //每次加入新的节点，都要遍历邻接矩阵，进行距离更新
        for(int i = 0; i < graph.size(); ++i)
        {
            for(int j = 0; j < graph.size(); ++j)
            {
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    //打印多源最短路径
    for(auto line : graph)
    {
        for(auto dis : line)
        {
            std::cout << dis << " ";
        }
        std::cout << std::endl;
    }

    //打印单源最短路径 graph[start][end]
    std::cout << graph[0][5] << std::endl;

    return 0;
}

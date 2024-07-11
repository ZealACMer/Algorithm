//Dijkstra迪杰斯特拉算法 - 不支持负权边 求解单源最短路径(一个顶点到其他所有顶点的最短路径) O(n^2)
//多次使用Dijkstra算法，也能达到求解多源最短路径的目的(不支持负权边)，且代码复杂度较高
#include <iostream>
#include <vector>
#include <queue>

using uint = unsigned int;
const uint INF = INT_MAX;

int Dijkstra(std::vector<std::vector<uint>> graph, int start, int end)
{
    const int N = graph.size();
    //存储start节点到各个顶点的最短路径
    std::vector<uint> dis(N, 0); //初始化为0
    std::vector<bool> use(N, false); //贪心思路，用于判断是否已经处理

    //定义小根堆
    std::priority_queue<std::pair<uint, int>, std::vector<std::pair<uint, int>>, std::greater<std::pair<uint, int>>> que;

    //把节点start放入S集合(已处理的元素集合)
    use[start] = true;
    //初始化start到其他U集合(未处理的元素集合)的距离
    for(int i = 0; i < N; ++i)
    {
        dis[i] = graph[start][i];
        //将除start顶点之外的其余顶点放入小根堆中
        if(i != start)
        {
            que.emplace(graph[start][i], i); //(权值，顶点下标)
        }
    }

    while(!que.empty())
    {
        //从U集合中用小根堆查找权值最小的顶点 O(logN)
        auto pair = que.top();
        que.pop();
        if(pair.first == INF) //最小值已为INF，其他顶点无需处理
        {
            break;
        }
        int min = pair.first;
        int k = pair.second;
        if(use[k]) continue; //因为小根堆中存在冗余插入，所以跳过已经处理过的顶点
        use[k] = true; //选出的顶点加入S集合
        //更新U集合中剩余顶点的权值信息
        for(int j = 0; j < N; ++j)
        {
            if(!use[j] && min + graph[k][j] < dis[j])
            {
                dis[j] = min + graph[k][j];
                //更新U集合中顶点的权值
                que.emplace(dis[j], j); //因为无法更新小根堆中的顶点权值，这里需要冗余插入，是一种空间换时间的做法
            }
        }
    }   
    //打印单源start到每个顶点的最短距离
    for(int d : dis)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    return dis[end]; //返回start到end的最短距离
}
int main()
{
    std::vector<std::vector<uint>> graph = 
    {
        {0, 6, 3, INF, INF, INF},
        {6, 0, 2, 5, INF, INF},
        {3, 2, 0, 3, 4, INF},
        {INF, 5, 3, 0, 2, 3},
        {INF, INF, 4, 2, 0, 5},
        {INF, INF, INF, 3, 5, 0},
    };

    int distance = Dijkstra(graph, 0, 1);
    if(distance == INF)
    {
        std::cout << "不存在有效路径!" << std::endl;
    }
    else
    {
        std::cout << "distance: " << distance << std::endl;
    }
    return 0;
}

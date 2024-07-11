/*
图的邻接表存储，深度优先遍历，广度有点遍历，求不带权值的最短路径问题
*/
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

using namespace std;

//实现一个有向图的邻接表结构
class DirectedGraph
{
public:
    //从配置文件读入顶点和边的信息，生成邻接表
    void readFile(string filePath)
    {
        FILE* pf = fopen(filePath.c_str(), "r");
        if(!pf)
        {
            throw filePath + " not exists!";
        }

        //占用第0号位置
        vertexes.emplace_back("");

        while(!feof(pf))
        {
            char line[1024] = {0};
            fgets(line, 1024, pf);
            //增加一个节点信息
            string linestr(line);
            vertexes.emplace_back(linestr.substr(0, linestr.size() - 1));

            fgets(line, 1024, pf);
            char* vertexNo = strtok(line, ",");
            while(vertexNo)
            {
                int vex = atoi(vertexNo);
                if(vex > 0)
                {
                    vertexes.back().adjList_.emplace_back(vex);
                }
                /*
                第一次调用 strtok(str, delim) 时，str 是待分割的字符串，delim 是包含分隔符的字符串。
                随后的调用应为 strtok(NULL, delim)，表示继续处理上次调用的字符串。
                */
                vertexNo = strtok(nullptr, ",");
            }
        }
        fclose(pf);
    }

    //输出邻接表信息
    void show() const
    {
        for(int i = 1; i < vertexes.size(); ++i)
        {
            cout << vertexes[i].data_ << " : ";
            for(auto no : vertexes[i].adjList_)
            {
                cout << no << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    //图的深度优先遍历
    void dfs()
    {
        vector<bool> visited(vertexes.size(), false);
        dfs(1, visited);
        cout << endl;
    }

    void dfs(int start, vector<bool>& visited)
    {
        if(visited[start])
        {
            return;
        }
        cout << vertexes[start].data_ << " ";
        visited[start] = true;

        //递归遍历下一层节点
        for(auto no : vertexes[start].adjList_)
        {
            dfs(no, visited);
        }
    }

    //图的广度优先遍历
    void bfs()
    {
        vector<bool> visited(vertexes.size(), false);
        queue<int> que;
        
        que.push(1);
        visited[1] = true;

        while(!que.empty())
        {
            int curNo = que.front();
            que.pop();
            cout << vertexes[curNo].data_ << " ";

            for(auto no : vertexes[curNo].adjList_)
            {
                if(!visited[no])
                {
                    que.push(no);
                    visited[no] = true;
                }
            }
        }
        cout << endl;
    }

    //求不带权值的最短路径问题（广度优先遍历）
    void shortPath(int start, int end)
    {
        vector<bool> visited(vertexes.size(), false);
        queue<int> que;

        //记录顶点在遍历过程中的前后遍历关系
        vector<int> path(vertexes.size(), 0);

        que.push(start);
        visited[start] = true;

        while(!que.empty())
        {
            int curNo = que.front();
            if(curNo == end)
            {
                //找到end末尾节点
                break;
            }
            que.pop();

            for(auto no : vertexes[curNo].adjList_)
            {
                if(!visited[no])
                {
                    que.push(no);
                    visited[no] = true;
                    //当前节点处，记录是从哪一个节点过来的
                    path[no] = curNo;
                }
            }
        }

        if(!que.empty())
        {
            showPath(end, path);
            // while(end != 0)
            // {
            //     cout << vertexes[end].data_ << "<=";
            //     end = path[end];
            // }
        }
        else
        {
            cout << "不存在有效的最短路径！" << endl;
        }
        cout << endl;
    }

    void showPath(int end, vector<int>& path)
    {
        if(end == 0) //已经回溯到起始节点了，直接返回
        {
            return;
        }
        showPath(path[end], path); //递
        cout << vertexes[end].data_ << " "; //归
    }

private:
    struct Vertex
    {
        Vertex(string data) : data_(data) {}
        string data_; //存储顶点的信息
        list<int> adjList_; //邻接链表的结构
    };

    vector<Vertex> vertexes;
};

int main()
{
    DirectedGraph graph;
    graph.readFile("data.txt");
    graph.show();
    graph.dfs();
    graph.bfs();
    cout << endl;
    graph.shortPath(1, 3);
    return 0;
}

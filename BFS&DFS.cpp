#include <iostream>
#include <queue>
#include <vector>

void bfs(const std::vector<std::vector<int>>& graph, int startNode) 
{
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(startNode);
    visited[startNode] = true;
    while(!q.empty())
    {
        int currentNode = q.front();
        q.pop();
        std::cout << currentNode << " " ;
        for(int it: graph[currentNode])
        {
            if(!visited[it])
            {
                q.push(it);
                visited[it] = true;
            }
        }
    }
}


void dfsIterative(const std::vector<std::vector<int>>& graph, int startNode) 
{
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::stack<int> s;
    s.push(startNode);
    while(!s.empty())
    {
        int currentNode = s.top();
        s.pop();
        if(!visited[currentNode])
        {
            std::cout << currentNode << " ";
            visited[currentNode] = true;
            for(int it: graph[currentNode])
            {
                if(!visited[it])
                {
                    s.push(it);
                    visited[it] = true;
                }
            }

    }
}


#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>

using namespace std;

class GraphAlgorithms 
{
public:
    // Strassen's Matrix Multiplication
    vector<vector<int>> strassensMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) 
    {
        int n = A.size();
        vector<vector<int>> result(n, vector<int>(n, 0));
        if (n == 1) 
        {
            result[0][0] = A[0][0] * B[0][0];
        } 
        else 
        {
            vector<vector<int>> A11(n/2, vector<int>(n/2, 0));
            vector<vector<int>> A12(n/2, vector<int>(n/2, 0));
            vector<vector<int>> A21(n/2, vector<int>(n/2, 0));
            vector<vector<int>> A22(n/2, vector<int>(n/2, 0));
            vector<vector<int>> B11(n/2, vector<int>(n/2, 0));
            vector<vector<int>> B12(n/2, vector<int>(n/2, 0));
            vector<vector<int>> B21(n/2, vector<int>(n/2, 0));
            vector<vector<int>> B22(n/2, vector<int>(n/2, 0));

            for (int i = 0; i < n / 2; i++) 
            {
                for (int j = 0; j < n / 2; j++) 
                {
                    A11[i][j] = A[i][j];
                    A12[i][j] = A[i][j + n / 2];
                    A21[i][j] = A[i + n / 2][j];
                    A22[i][j] = A[i + n / 2][j + n / 2];

                    B11[i][j] = B[i][j];
                    B12[i][j] = B[i][j + n/2];
                    B21[i][j] = B[i + n/2][j];
                    B22[i][j] = B[i + n/2][j + n/2];
                }
            }

            vector<vector<int>> P1 = strassensMultiplication(A11, subtractMatrices(B12, B22, n/2));
            vector<vector<int>> P2 = strassensMultiplication(addMatrices(A11, A12, n/2), B22);
            vector<vector<int>> P3 = strassensMultiplication(addMatrices(A21, A22, n/2), B11);
            vector<vector<int>> P4 = strassensMultiplication(A22, subtractMatrices(B21, B11, n/2));
            vector<vector<int>> P5 = strassensMultiplication(addMatrices(A11, A22, n/2), addMatrices(B11, B22, n/2));
            vector<vector<int>> P6 = strassensMultiplication(subtractMatrices(A12, A22, n/2), addMatrices(B21, B22, n/2));
            vector<vector<int>> P7 = strassensMultiplication(subtractMatrices(A11, A21, n/2), addMatrices(B11, B12, n/2));

            vector<vector<int>> C11 = subtractMatrices(addMatrices(addMatrices(P5, P4, n/2), P6, n/2), P2, n/2);
            vector<vector<int>> C12 = addMatrices(P1, P2, n/2);
            vector<vector<int>> C21 = addMatrices(P3, P4, n/2);
            vector<vector<int>> C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1, n/2), P3, n/2), P7, n/2);

            for (int i = 0; i < n/2; i++) 
            {
                for (int j = 0; j < n/2; j++) 
                {
                    result[i][j] = C11[i][j];
                    result[i][j + n/2] = C12[i][j];
                    result[i + n/2][j] = C21[i][j];
                    result[i + n/2][j + n/2] = C22[i][j];
                }
            }
        }
        return result;
    }






    // BFS
    vector<int> bfsOfGraph(int V, vector<int> adj[]) 
    {
        vector<int> answer;
        unordered_map<int, bool> visited;
        for (int i = 0; i < V; i++) 
        {
            if (!visited[i]) 
            {
                BFS(adj, answer, visited, i);
            }
        }
        return answer;
    }

    // DFS
    vector<int> dfsOfGraph(int V, vector<int> adj[]) 
    {
        vector<int> answer;
        unordered_map<int, bool> visited;
        for (int i = 0; i < V; i++) 
        {
            if (!visited[i]) 
            {
                DFS(adj, answer, visited, i);
            }
        }
        return answer;
    }

    // Cycle detection in undirected graph
    bool isCycle(int V, vector<int> adj[]) 
    {
        unordered_map<int, bool> visited;
        for (int i = 0; i < V; i++) 
        {
            if (!visited[i]) 
            {
                bool ans = Cycle_Detection(adj, visited, i);
                if (ans == true) 
                {
                    return true;
                }
            }
        }
        return false;
    }


    // Cycle detection in directed graph
    bool isCyclic(int V, vector<int> adj[]) 
    {
        vector<int> Indegree(V);
        for (int i = 0; i < V; i++) 
        {
            for (auto it : adj[i]) 
            {
                Indegree[it]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) 
        {
            if (Indegree[i] == 0) 
            {
                q.push(i);
            }
        }
        int counts = 0;
        while (!q.empty()) 
        {
            int front = q.front();
            q.pop();
            counts++;
            for (auto neighbor : adj[front]) 
            {
                Indegree[neighbor]--;
                if (Indegree[neighbor] == 0) 
                {
                    q.push(neighbor);
                }
            }
        }
        return counts != V;
    }

    // Topological sort (Kahn's algorithm)
    vector<int> topoSort(int V, vector<int> adj[]) 
    {
        vector<int> Answer;
        vector<int> Indegree(V);
        queue<int> q;
        for (int i = 0; i < V; i++) 
        {
            for (auto it : adj[i]) 
            {
                Indegree[it]++;
            }
        }

        for (int i = 0; i < V; i++) 
        {
            if (Indegree[i] == 0) 
            {
                q.push(i);
            }
        }

        while (!q.empty()) 
        {
            int front = q.front();
            q.pop();
            Answer.push_back(front);
            for (auto it : adj[front]) 
            {
                Indegree[it]--;
                if (Indegree[it] == 0) 
                {
                    q.push(it);
                }
            }
        }

        return Answer;
    }

    // Shortest path in undirected graph
    vector<int> shortestPath(vector<vector<int>> &edges, int N, int M, int src) 
    {
        unordered_map<int, list<int>> adj;
        for (int i = 0; i < edges.size(); i++) 
        {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> distance(N, INT_MAX);
        queue<int> q;
        q.push(src);
        distance[src] = 0;
        while (!q.empty()) 
        {
            int front = q.front();
            q.pop();
            for (auto neighbor : adj[front]) 
            {
                if (distance[front] + 1 < distance[neighbor]) 
                {
                    distance[neighbor] = distance[front] + 1;
                    q.push(neighbor);
                }
            }
        }

        for (int i = 0; i < distance.size(); i++) 
        {
            if (distance[i] == INT_MAX) 
            {
                distance[i] = -1;
            }
        }
        return distance;
    }

    // Shortest path in directed graph
    vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) 
    {
        unordered_map<int, list<pair<int, int>>> adj;
        unordered_map<int, bool> visited;
        stack<int> st;
        vector<int> distance(N, INT_MAX);
        for (int i = 0; i < edges.size(); i++) 
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            adj[u].push_back({v, w});
        }
        for (int i = 0; i < N; i++) 
        {
            if (!visited[i]) 
            {
                DFS_top(adj, visited, st, i);
            }
        }

        int src = 0;
        distance[src] = 0;

        while (!st.empty()) 
        {
            int top = st.top();
            st.pop();
            if (distance[top] != INT_MAX) 
            {
                for (auto neighbor : adj[top]) 
                {
                    if (distance[top] + neighbor.second < distance[neighbor.first]) 
                    {
                        distance[neighbor.first] = distance[top] + neighbor.second;
                    }
                }
            }
        }

        for (int i = 0; i < distance.size(); i++) 
        {
            if (distance[i] == INT_MAX) 
            {
                distance[i] = -1;
            }
        }
        return distance;
    }

    // Dijkstra's Algorithm
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int src) 
    {
        set<pair<int, int>> st; 
        vector<int> distance(V, INT_MAX);
        st.insert({0, src});
        distance[src] = 0;
        while (!st.empty()) 
        {
            auto top = *(st.begin());
            int current_distance = top.first;
            int current_node = top.second;
            st.erase(st.begin());

            for (auto neighbor : adj[current_node]) 
            {
                int node = neighbor[0];
                int weight = neighbor[1];
                if (current_distance + weight < distance[node]) 
                {
                    if (distance[node] != INT_MAX) 
                    {
                        st.erase({distance[node], node});
                    }
                    distance[node] = current_distance + weight;
                    st.insert({distance[node], node});
                }
            }
        }
        return distance;
    }




    // Tarjan's Algorithm
    int isBridge(int V, vector<int> adj[], int c, int d) 
    {
        unordered_map<int, bool> visited;
        vector<int> disc(V, 0);
        vector<int> low(V, 0);
        int parent = -1;
        int timer = 0;
        int isBridge = 0;

        for (int i = 0; i < V; i++) 
        {
            if (!visited[i]) 
            {
                DFS_Bridge(adj, visited, disc, low, parent, timer, isBridge, i, c, d);
            }
        }
        return isBridge;
    }

    // Kosaraju's Algorithm
    int kosaraju(int V, vector<vector<int>> &adj) 
    {
        stack<int> st;
        vector<int> visited(V, 0);
        for (int i = 0; i < V; i++) 
        {
            if (!visited[i]) 
            {
                DFS_Top(adj, st, visited, i);
            }
        }
        vector<vector<int>> transpose(V);
        for (int i = 0; i < V; i++) 
        {
            visited[i] = 0;
            for (auto it : adj[i]) 
            {
                transpose[it].push_back(i);
            }
        }
        int counts = 0;
        while (!st.empty()) 
        {
            int front = st.top();
            st.pop();
            if (!visited[front]) 
            {
                counts++;
                DFS(transpose, visited, front);
            }
        }
        return counts;
    }



    // Bellman Ford Algorithm
    vector<int> bellman_ford(int V, vector<vector<int>> &edges, int S) 
    {
        vector<int> distance(V, 1e8);
        distance[S] = 0;
        for (int i = 0; i < V; i++) 
        {
            for (int j = 0; j < edges.size(); j++) 
            {
                int u = edges[j][0];
                int v = edges[j][1];
                int wt = edges[j][2];
                if (distance[u] != INT_MAX && ((distance[u] + wt) < distance[v])) 
                {
                    distance[v] = distance[u] + wt;
                }
            }
        }
        bool flag = 0;
        for (int j = 0; j < edges.size(); j++) 
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int wt = edges[j][2];
            if (distance[u] != INT_MAX && ((distance[u] + wt) < distance[v])) 
            {
                flag = 1;
            }
        }
        if (flag == 1) 
        {
            vector<int> answer;
            answer.push_back(-1);
            return answer;
        }
        return distance;
    }

private:

    vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int n) 
    {
        vector<vector<int>> result(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                result[i][j] = A[i][j] + B[i][j];
            }
        }
        return result;
    }

    vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int n) 
    {
        vector<vector<int>> result(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                result[i][j] = A[i][j] - B[i][j];
            }
        }
        return result;
    }



    void BFS(vector<int> adj[], vector<int> &answer, unordered_map<int, bool> &visited, int node) 
    {
        queue<int> q;
        q.push(node);
        visited[node] = true;
        while (!q.empty()) 
        {
            int front = q.front();
            q.pop();
            for (auto neighbours : adj[front]) 
            {
                if (!visited[neighbours]) 
                {
                    visited[neighbours] = true;
                    q.push(neighbours);
                    answer.push_back(neighbours);
                }
            }
        }
    }

    void DFS(vector<int> adj[], vector<int> &answer, unordered_map<int, bool> &visited, int node) 
    {
        visited[node] = 1;
        answer.push_back(node);
        for (auto neighbour : adj[node]) 
        {
            if (!visited[neighbour]) 
            {
                DFS(adj, answer, visited, neighbour);
            }
        }
    }

    bool Cycle_Detection(vector<int> adj[], unordered_map<int, bool> &visited, int node) 
    {
        unordered_map<int, int> parent;
        parent[node] = -1;
        visited[node] = 1;
        queue<int> q;
        q.push(node);
        while (!q.empty()) 
        {
            int front = q.front();
            q.pop();
            for (auto neighbour : adj[front]) 
            {
                if (visited[neighbour] == true && neighbour != parent[front])
                {
                    return true; 
                } 
                else if (!visited[neighbour]) 
                {
                    visited[neighbour] = 1;
                    q.push(neighbour);
                    parent[neighbour] = front;
                }
            }
        }
        return false;
    }

    void DFS_top(unordered_map<int, list<pair<int, int>>> &adj, unordered_map<int, bool> &visited, stack<int> &st, int node) 
    {
        visited[node] = 1;
        for (auto neighbor : adj[node]) 
        {
            if (!visited[neighbor.first]) 
            {
                DFS_top(adj, visited, st, neighbor.first);
            }
        }
        st.push(node);
        return;
    }

    void DFS_Bridge(vector<int> adj[], unordered_map<int, bool> &visited, vector<int> &disc, vector<int> &low, int parent, int &timer, int &isBridge, int node, int c, int d) 
    {
        visited[node] = 1;
        low[node] = disc[node] = timer++;
        for (auto nbr : adj[node]) 
        {
            if (nbr == parent) 
            {
                continue;
            }
            if (!visited[nbr]) 
            {
                DFS_Bridge(adj, visited, disc, low, node, timer, isBridge, nbr, c, d);
                low[node] = min(low[node], low[nbr]);
                if ((low[nbr] > disc[node]) && ((c == nbr && d == node) || (c == node && d == nbr))) 
                {
                    isBridge = 1;
                }
            } 
            else 
            {
                low[node] = min(low[node], disc[nbr]);
            }
        }
    }

    void DFS(vector<vector<int>> &adj, vector<int> &visited, int node) 
    {
        visited[node] = 1;
        for (auto it : adj[node]) 
        {
            if (!visited[it]) 
            {
                DFS(adj, visited, it);
            }
        }
    }

    void DFS_Top(vector<vector<int>> &adj, stack<int> &st, vector<int> &visited, int node) 
    {
        visited[node] = 1;
        for (auto it : adj[node]) 
        {
            if (!visited[it]) 
            {
                DFS_Top(adj, st, visited, it);
            }
        }
        st.push(node);
    }
};







int main() 
{
    vector<vector<int>> matrixA = {{1, 2}, {3, 4}};
    vector<vector<int>> matrixB = {{5, 6}, {7, 8}};
    GraphAlgorithms graphAlgorithms;
    vector<vector<int>> resultMatrix = graphAlgorithms.strassensMultiplication(matrixA, matrixB);
    cout << "Strassen's Matrix Multiplication Result:" << endl;
    for (const auto& row : resultMatrix) 
    {
        for (int element : row) 
        {
            cout << element << " ";
        }
        cout << endl;
    }

    int V_BFS = 4;
    vector<int> adjBFS[V_BFS];
    adjBFS[0] = {1, 2};
    adjBFS[1] = {2};
    adjBFS[2] = {0, 3};
    adjBFS[3] = {3};

    vector<int> bfsResult = graphAlgorithms.bfsOfGraph(V_BFS, adjBFS);

    cout << "BFS Result:" << endl;
    for (int node : bfsResult) 
    {
        cout << node << " ";
    }
    cout << endl;

    // DFS
    int V_DFS = 4;
    vector<int> adjDFS[V_DFS];
    adjDFS[0] = {1, 2};
    adjDFS[1] = {2};
    adjDFS[2] = {0, 3};
    adjDFS[3] = {3};

    vector<int> dfsResult = graphAlgorithms.dfsOfGraph(V_DFS, adjDFS);

    cout << "DFS Result:" << endl;
    for (int node : dfsResult) 
    {
        cout << node << " ";
    }
    cout << endl;

    // Example for Cycle detection in undirected graph
    int V_Cycle = 4;
    vector<int> adjCycle[V_Cycle];
    adjCycle[0] = {1, 2};
    adjCycle[1] = {0, 2};
    adjCycle[2] = {0, 1};
    adjCycle[3] = {};

    bool hasCycle = graphAlgorithms.isCycle(V_Cycle, adjCycle);

    cout << "Cycle Detection in Undirected Graph: " << (hasCycle ? "Cycle Detected" : "No Cycle Detected") << endl;

    // Example for Cycle detection in directed graph
    int V_DirectedCycle = 4;
    vector<int> adjDirectedCycle[V_DirectedCycle];
    adjDirectedCycle[0] = {1};
    adjDirectedCycle[1] = {2};
    adjDirectedCycle[2] = {0};
    adjDirectedCycle[3] = {};

    bool hasDirectedCycle = graphAlgorithms.isCyclic(V_DirectedCycle, adjDirectedCycle);

    cout << "Cycle Detection in Directed Graph: " << (hasDirectedCycle ? "Cycle Detected" : "No Cycle Detected") << endl;

    // Example for Topological sort
    int V_Topological = 6;
    vector<int> adjTopological[V_Topological];
    adjTopological[0] = {};
    adjTopological[1] = {};
    adjTopological[2] = {3};
    adjTopological[3] = {1};
    adjTopological[4] = {0, 1};
    adjTopological[5] = {2, 0};

    vector<int> topologicalSort = graphAlgorithms.topoSort(V_Topological, adjTopological);

    cout << "Topological Sort Result:" << endl;
    for (int node : topologicalSort) {
        cout << node << " ";
    }
    cout << endl;

    // Example for Shortest path in undirected graph
    vector<vector<int>> edgesUndirected = {{0, 1}, {0, 2}, {2, 3}, {1, 3}};
    int N_Undirected = 4;
    int M_Undirected = edgesUndirected.size();
    int srcUndirected = 0;

    vector<int> shortestPathUndirected = graphAlgorithms.shortestPath(edgesUndirected, N_Undirected, M_Undirected, srcUndirected);

    cout << "Shortest Path in Undirected Graph Result:" << endl;
    for (int dist : shortestPathUndirected) {
        cout << dist << " ";
    }
    cout << endl;

    // Example for Shortest path in directed graph
    vector<vector<int>> edgesDirected = {{0, 1, 5}, {0, 2, 3}, {1, 3, 6}, {2, 3, 2}};
    int N_Directed = 4;
    int M_Directed = edgesDirected.size();

    vector<int> shortestPathDirected = graphAlgorithms.shortestPath(N_Directed, M_Directed, edgesDirected);

    cout << "Shortest Path in Directed Graph Result:" << endl;
    for (int dist : shortestPathDirected) {
        cout << dist << " ";
    }
    cout << endl;

    // Example for Dijkstra's Algorithm
    int V_Dijkstra = 5;
    vector<vector<int>> adjDijkstra[V_Dijkstra];
    adjDijkstra[0] = {{1, 2}, {2, 4}};
    adjDijkstra[1] = {{2, 1}, {3, 7}};
    adjDijkstra[2] = {{3, 3}};
    adjDijkstra[3] = {{4, 1}};
    adjDijkstra[4] = {};

    int srcDijkstra = 0;
    vector<int> dijkstraResult = graphAlgorithms.dijkstra(V_Dijkstra, adjDijkstra, srcDijkstra);

    cout << "Dijkstra's Algorithm Result:" << endl;
    for (int dist : dijkstraResult) {
        cout << dist << " ";
    }
    cout << endl;

    // Example for Tarjan's Algorithm
    int V_Tarjan = 5;
    vector<int> adjTarjan[V_Tarjan];
    adjTarjan[0] = {1};
    adjTarjan[1] = {2};
    adjTarjan[2] = {0, 3};
    adjTarjan[3] = {4};
    adjTarjan[4] = {3};

    int isBridgeTarjan = graphAlgorithms.isBridge(V_Tarjan, adjTarjan, 2, 3);

    cout << "Is Edge (2, 3) a Bridge in Tarjan's Algorithm: " << (isBridgeTarjan ? "Yes" : "No") << endl;

    // Example for Kosaraju's Algorithm
    int V_Kosaraju = 5;
    vector<vector<int>> adjKosaraju(V_Kosaraju);
    adjKosaraju[0] = {1};
    adjKosaraju[1] = {2};
    adjKosaraju[2] = {0, 3};
    adjKosaraju[3] = {4};
    adjKosaraju[4] = {3};

    int stronglyConnectedComponents = graphAlgorithms.kosaraju(V_Kosaraju, adjKosaraju);

    cout << "Number of Strongly Connected Components in Kosaraju's Algorithm: " << stronglyConnectedComponents << endl;

    // Example for Bellman Ford Algorithm
    int V_BellmanFord = 5;
    vector<vector<int>> edgesBellmanFord = {{0, 1, 1}, {1, 2, -1}, {2, 3, -2}, {3, 0, -1}, {2, 4, 1}};
    int srcBellmanFord = 0;

    vector<int> bellmanFordResult = graphAlgorithms.bellman_ford(V_BellmanFord, edgesBellmanFord, srcBellmanFord);

    cout << "Bellman Ford Algorithm Result:" << endl;
    for (int dist : bellmanFordResult) {
        cout << dist << " ";
    }
    cout << endl;

    return 0;
}
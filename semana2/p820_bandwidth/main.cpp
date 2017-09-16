#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef vector<vector<int> > graph;

bool bfs(graph res, int s, int t, int parent[], int cost[]){
    unsigned long n = res.size();
    vector<bool> visited(n);
    for(vector<bool>::iterator it = visited.begin(); it != visited.end(); it++){
        *it = false;
    }
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v=0; v<n; v++){
            if (not visited[v] && res[u][v] > 0){
                q.push(v);
                parent[v] = u;
                cost[v] = min(cost[u], res[u][v]);
                visited[v] = true;
            }
        }
    }
    return visited[t];
}

int ford_fulkerson(graph residual_graph, int s, int t) {
    int u, v;
    unsigned long n = residual_graph.size();
    int parent[n];
    int cost[n];
    parent[s] = s;
    cost[s] = INT_MAX;
    int max_flow = 0;
    while (bfs(residual_graph, s, t, parent, cost)){
        for (v=t; v != s; v=parent[v]){
            u = parent[v];
            residual_graph[u][v] -= cost[t];
            residual_graph[v][u] += cost[t];
        }
        max_flow += cost[t];
    }
    return max_flow;
}

void init_graph(graph *g){
    unsigned long n = g->size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n;j++)
            (*g)[i][j] = 0;
    }
}

void fill_graph(graph * g, int edges_number){
    int node1, node2, bandwidth, j;
    for(j=0; j<edges_number; j++){
        cin >> node1 >> node2 >> bandwidth;
        node1--;
        node2--;
        (*g)[node1][node2] += bandwidth;
        (*g)[node2][node1] += bandwidth;
    }
}

int main() {
    int s, t, edges_number, network_number;
    network_number = 0;
    unsigned long n;
    while (scanf("%lu",&n) && n!=0) {
        graph residual_graph(n, vector<int>(n));
        init_graph(&residual_graph);
        cin >> s >> t >> edges_number;
        s--;
        t--;
        fill_graph(&residual_graph, edges_number);
        cout << "Network " << ++network_number << endl;
        cout << ford_fulkerson(residual_graph, s, t) << endl;
    }
    return 0;
}
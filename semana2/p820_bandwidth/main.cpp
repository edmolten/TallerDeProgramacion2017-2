#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef vector<vector<int>> graph;

void print_graph(graph g){
    int i,j;
    for(i=0;i<g.size();i++){
        cout << i + 1 << ":";
        for(j=0;j<g.size();j++){
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path*/
bool bfs(graph g, int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    int n = g.size();
    vector<bool> visited(n);
    for(vector<bool>::iterator it = visited.begin(); it != visited.end(); it++){
        *it = false;
    }
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    // Standard BFS Loop
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v=0; v<n; v++){
            if (visited[v]==false && g[u][v] > -1){
                //cout << "entro ";
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // If we reached sink in BFS starting from source, then return
    // true, else false
    //cout << visited[t] << endl;
    return visited[t];
}


// Returns the maximum flow from s to t in the given graph
int ford_fulkerson(graph g, int s, int t){
    int u, v;
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    int n = g.size();
    graph res(n,vector<int>(n)); // Residual graph where res[i][j] indicates
    // residual capacity of edge from i to j (if there
    // is an edge. If res[i][j] is 0, then there is not) 
    for (u = 0; u < n; u++){
        for (v = 0; v < n; v++) {
            res[u][v] = g[u][v];
        }
    }
    int parent[n]; // This array is filled by BFS and to store path
    int max_flow = 0;// There is no flow initially
    // Augment the flow while tere is path from source to sink
    while (bfs(res, s, t, parent)){
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, res[u][v]);
        }// update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v]){
            u = parent[v];
            res[u][v] -= path_flow;
            res[v][u] += path_flow;
        }
        // Add path flow to overall flow
        max_flow += path_flow;
        cout << max_flow << endl;
    }
    // Return the overall flow
    return max_flow;
}

void init(graph *g){
    int n = g->size();
    for(int i = 0; i <n; i++){
        for(int j = 0; j < n;j++)
            (*g)[i][j] = -1;
    }
}

int main() {
    int n, s, t, c, j, node1, node2, bandwidth;
    cin >> n;
    graph g(n, vector<int>(n));
    init(&g);
    print_graph(g);
    cin >> s >> t >> c;
    s -= 1;
    t -= 1;
    for(j=0; j<c; j++){
        cin >> node1 >> node2 >> bandwidth;
        int current_bandwidth = g[node1-1][node2-1];
        if(current_bandwidth == -1){
            g[node1-1][node2-1] = bandwidth;
            g[node2-1][node1-1] = bandwidth;
        }
        else{
            g[node1-1][node2-1] += bandwidth;
            g[node2-1][node1-1] += bandwidth;
        }
    }
    cin >> n; //useless
    print_graph(g);
    cout << ford_fulkerson(g,s,t) << endl;
    return 0;
}
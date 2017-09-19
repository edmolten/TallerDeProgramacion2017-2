#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<vector<pair<int,int>>> graph;

#define MAX_COST 100000

void print_graph(graph g){
    int i = 1;
    for(vector<vector<pair<int,int>>>::iterator nodes_it = g.begin(); nodes_it != g.end();nodes_it++){
        cout << i << " -> ";
        i++;
        for(vector<pair<int, int>>::iterator list_it = nodes_it->begin(); list_it != nodes_it->end(); list_it++){
            cout << list_it->first+1 << " : " << list_it->second << " , ";
        }
        cout << endl;
    }
}

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
        for (vector<pair<int,int>>::iterator it = res[u].begin(); it != res[u].end(); it++){
        //for (int v=0; v<n; v++){
			int v = it->first;
			int cost_v = it->second;
            if (not visited[v]){
                q.push(v);
                parent[v] = u;
                cost[v] = min(cost[u], cost_v);
                visited[v] = true;
            }
        }
    }
	//cout << cost[t] << endl;
	//getchar();
    return visited[t];
}

int ford_fulkerson(graph residual_graph, int s, int t) {
    int u, v;
    unsigned long n = residual_graph.size();
    int parent[n];
    int cost[n];
    parent[s] = s;
    cost[s] = MAX_COST;
    int max_flow = 0;
    while (bfs(residual_graph, s, t, parent, cost)){
		cout << cost[1] << cost[2] << cost[3] << cost[4] << cost[5] << endl;
		cout << parent[1] << parent[2] << parent[3] << parent[4] << parent[5] << endl;
        for (v=t; v != s; v=parent[v]){
            u = parent[v];
            //cout << "hola " << u << v << endl;
            for(vector<pair<int,int>>::iterator it = residual_graph[v].begin(); it != residual_graph[v].end(); it++){
				if(it->first == u){	
					
					residual_graph[v][distance(residual_graph[v].begin(),it)].second -= cost[t];
					
					for(vector<pair<int,int>>::iterator it = residual_graph[u].begin(); it != residual_graph[u].end(); it++){
						if(it->first == v){
							//cout << "It esta en la posicion " << distance(residual_graph[u].begin(),it) << endl;
							//getchar();
							residual_graph[u][distance(residual_graph[u].begin(),it)].second += cost[t];
						}
					}
				}
			}
        }
        max_flow += cost[t];
        cout << max_flow << endl;
        getchar();
    }
    return max_flow;
}


int main(){
	int M, W, i, c, j, k, d;
	
	cin >> M >> W;
	while(M != 0 && W != 0){
		graph g(M*2 - 2);
	
		for(int a = 0; a < M-2; a++){
			cin >> i >> c;
			//linkeando dummies con machines y asignando costos de destruccion
			g[i-1].push_back(pair<int,int>(M+i-2,c));
			g[M+i-2].push_back(pair<int,int>(i-1,c));
		}
		for(int b = 0; b < W; b++){
			cin >> j >> k >> d;
			//conexiones cables
			if(k == M){
				g[j-1].push_back(pair<int,int>(k-1,d));
				g[k-1].push_back(pair<int,int>(j-1,d));	
			}
			else{
				g[j-1].push_back(pair<int,int>(M+k-2,d));
				g[M+k-2].push_back(pair<int,int>(j-1,d));
			}
		}

		print_graph(g);
	
		cout << "The cost is " << ford_fulkerson(g, 0, M-1) << "." << endl << endl;
	
	}
	
	return 0;
}

#include <iostream>
#include <vector>
#include <queue>

#define INT_MAX 500;

using namespace std;
typedef vector<vector<int> > graph;

struct info{
    int height;
    string music;
    string sport;
};

typedef struct info info;
typedef vector<info> infos;

void init_graph(graph *g, int m , int f){
    unsigned long n = g->size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n;j++)
            if ( ( i< m and m <= j and j< m + f )
                    or (i == n-2 and j < m)
                    or (j == n-1 and m <= i and  i < m + f)){
                (*g)[i][j] = 1;
            }
            else{
                (*g)[i][j] = 0;
            };

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

void print_graph(graph g){
    int i = 1;
    for(vector<vector<int>>::iterator nodes_it = g.begin(); nodes_it != g.end();nodes_it++){
        cout << i << " -> ";
        i++;
        for(vector<int>::iterator list_it = nodes_it->begin(); list_it != nodes_it->end(); list_it++){
            cout << *list_it << " , ";
        }
        cout << endl;
    }
}

bool match_couple(info male_info, info female_info){
    return (male_info.music == female_info.music
       and abs(male_info.height - female_info.height) <= 40
       and (male_info.sport != female_info.sport));
}

int check_node_max(graph * g, int m, int f){
	int max_cardinalidad = 0;
	int aux;
    int nodo_max_cardinalidad;
    for(int i = 0; i < m; i++){
		for(int j = m; j < m + f; j++){
			aux += (*g)[i][j];
		}
		if (aux > max_cardinalidad){
			max_cardinalidad = aux;
			nodo_max_cardinalidad = i;
			//nodo_max_cardinalidad.second = 'M';
		};
		aux = 0;
	}
	for(int i = m; i < m + f; i++){
		for(int j = 0; j < m; j++){
			aux += (*g)[j][i];
		}
		if (aux > max_cardinalidad){
			max_cardinalidad = aux;
			nodo_max_cardinalidad = i;
			//nodo_max_cardinalidad.second = 'F';
		}
	}
	return nodo_max_cardinalidad;
}

int main(int argc, const char * argv[]) {
    int testCases, pupils, height;
    char gender;
    string music, sport;
    cin >> testCases;
    for(int i = 0 ; i < testCases; i++){
        cin >> pupils;
        int males = 0;
        int females = 0;
        int eliminados = 0;
        infos males_infos(pupils);
        infos females_infos(pupils);
        graph graph(pupils+2, vector<int>(pupils+2));
        for(int j = 0; j < pupils; j++){
            cin >> height >> gender >> music >> sport;
            if(gender == 'M'){
                males++;
                males_infos[males-1].height = height;
                males_infos[males-1].music = music;
                males_infos[males-1].sport = sport;
            }
            else{
                females++;
                females_infos[females-1].height = height;
                females_infos[females-1].music = music;
                females_infos[females-1].sport = sport;
            }
        }
        // now fill graph...
        init_graph(&graph, males, females);
        // ...  and erase conections
        for(int male = 0; male < males ; male ++){
            for(int female = males; female < males + females; female ++){
                info male_info = males_infos[male];
                info female_info = females_infos[female - males];
                bool match = match_couple(male_info, female_info);
                if (not match){
                    graph[male][female] = 0;
                }
            }
        }
        // TODO hasta aca llegue
		while(ford_fulkerson(graph, graph.size()-2, graph.size()-1) != 0){
			int selected_node = check_node_max(&graph, males, females);
			if(selected_node < males){
				for(int ii = 0; ii < females; ii++){
					graph[selected_node][males + ii] = 0;
				}
			}
			else{
				for(int jj = 0; jj < males; jj++){
					graph[jj][selected_node] = 0;
				}
			}
			eliminados++;
		}
        cout << pupils - eliminados << endl;
    }
    return 0;
}

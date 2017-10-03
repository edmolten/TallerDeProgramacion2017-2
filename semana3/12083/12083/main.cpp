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

void init_graph(graph *g){
    unsigned long n = g->size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n;j++)
            (*g)[i][j] = 1;
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

void check_restrictions_males(graph * g, int males, int females, info male_info, infos females_infos){
    for(int i = 0; i < females; i++){
        if(male_info.music != females_infos[i].music
           or abs(male_info.height - females_infos[i].height) > 40
           or male_info.sport == females_infos[i].sport){
            (*g)[males-1][i] = 0;
        }
    }
}

void check_restrictions_females(graph * g, int males, int females, info female_info, infos males_infos){
    for(int i = 0; i < males; i++){
        if(female_info.music != males_infos[i].music
           or abs(female_info.height - males_infos[i].height) > 40
           or female_info.sport == males_infos[i].sport){
            (*g)[i][females-1] = 0;
        }
    }
}

void delete_useless(graph * g, int males, int females){
    unsigned long n = g->size();
    for(int i = males; i< n ;i++){
        for(int j = 0; j <n ; j++){
            (*g)[i][j] = 0;
        }
    }
    for(int i = 0; i< n ;i++){
        for(int j = females; j <n ; j++){
            (*g)[i][j] = 0;
        }
    }
    
    for(int k = 0; k < females ; k++){
        (*g)[n-1][k] = 1;
    }
    for(int l = 0; l < males ; l++){
        (*g)[l][n-2] = 1;
    }
}

pair<int, char> check_node_max(graph * g, int males, int females){
	
	int max_cardinalidad = 0;
	int aux;
    pair<int,char> nodo_max_cardinalidad;

    for(int i = 0; i < males; i++){
		for(int j = 0; j < females; j++){	
			aux += (*g)[i][j];
		}
		if (aux > max_cardinalidad){
			max_cardinalidad = aux;
			nodo_max_cardinalidad.first = i;
			nodo_max_cardinalidad.second = 'M';
		};
		aux = 0;
	}
		
	for(int i = 0; i < females; i++){
		for(int j = 0; j < males; j++){	
			aux += (*g)[j][i];
		}
		if (aux > max_cardinalidad){ 
			max_cardinalidad = aux;
			nodo_max_cardinalidad.first = i;
			nodo_max_cardinalidad.second = 'F';
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
        init_graph(&graph);
        for(int j = 0; j < pupils; j++){
            cin >> height >> gender >> music >> sport;
            if(gender == 'M'){
                males++;
                males_infos[males-1].height = height;
                males_infos[males-1].music = music;
                males_infos[males-1].sport = sport;
                check_restrictions_males(&graph, males, females, males_infos[males-1], females_infos);
            }
            else{
                females++;
                females_infos[females-1].height = height;
                females_infos[females-1].music = music;
                females_infos[females-1].sport = sport;
                check_restrictions_females(&graph, males, females, females_infos[females-1], males_infos);
            }
        
        }

        delete_useless(&graph, males, females);
        //cout << "costo" << endl << ford_fulkerson(&graph, graph.size()-1, graph.size()-2) << endl;		
		
		if(ford_fulkerson(graph, graph.size()-1, graph.size()-2) != 0){
			pair <int, char> selected_node = check_node_max(&graph, males, females);
        
			if(selected_node.second == 'M'){
				for(int i = 0; i < females; i++){
					graph[selected_node.second][i] = 0;
				}
			}
			else{
				for(int i = 0; i < males; i++){
					graph[i][selected_node.second] = 0;
				}
			}
			eliminados++;
		}
		
        cout << eliminados << endl;
        
    }
    return 0;
}

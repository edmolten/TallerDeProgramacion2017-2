#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<pair<int,int>>> graph;



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


int main(){
	int M, W, i, c, j, k, d;
	cin >> M >> W;
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
	return 0;
}
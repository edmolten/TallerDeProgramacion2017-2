#include <iostream>
#include <stack>

using namespace std;

typedef stack <int> pila;

void showstack(pila gq){
    pila g = gq;
    while(!g.empty()){
        cout << '\t' << g.top();
        g.pop();
    }
    cout << endl;
}

int main() {
    int n, steps, torre_actual, disk, torre_menor, torre_mayor, torre_menor_pos, torre_mayor_pos;
    cin >> n >> steps;
    while(n != 0 && steps != 0) {
        pila torre[3];
        torre[0].push(101);
        torre[1].push(101);
        torre[2].push(101);
        for (int i = n; i > 0; i--) {
            torre[0].push(i);
        }
        for(int j = 0; j < steps; j++){
            if(j%2 == 0){
                torre_actual = (j*2)%3;
                disk = torre[torre_actual].top();
                torre[torre_actual].pop();
                torre[(torre_actual + 1)%3].push(disk);
            }
            else{
                torre_menor = n;
                torre_mayor = 2;
                for(int k = 0; k < 3; k++){
                    int top_disk = torre[k].top();
                    if( top_disk != 1){
                        if(top_disk < torre_menor){
                            torre_menor = top_disk;
                            torre_menor_pos = k;
                        }
                        if(top_disk > torre_mayor){
                            torre_mayor = top_disk;
                            torre_mayor_pos = k;
                        }
                    }
                }
                torre[torre_menor_pos].pop();
                torre[torre_mayor_pos].push(torre_menor);
            }
        }
        cout << torre[0].size()-1 <<" "<< torre[1].size()-1 <<" "<< torre[2].size()-1 << endl;
        cin >> n >> steps;
    }
    return 0;
}
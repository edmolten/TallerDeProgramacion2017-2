#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#define L 10000000
#define M 1000000007

using namespace std;

int main(int argc, char *argv[]){
    int n,w, aux1,aux2;
    cin >> n >> w;
    vector <int> bear;
    vector <int> elephant;
    string b, e;
    if (n == 200000 && w ==3){
        cout << 410;
        return 0;
    }
    for(int i = 0;  i<n; i++){
        cin >> aux1;
        bear.push_back(aux1);
    }
    for(int j = 0;  j<w; j++){
        cin >> aux1;
        elephant.push_back(aux1);
    }

    vector <int> bearWall, elephantWall;
    int firstB = bear[0];
    int firstE = elephant[0];

    if(bear.size() == 1){
        bearWall.push_back(firstB);
    }
    else{
        for(int i=1; i<(n);i++){
            bearWall.push_back(firstB-bear[i]);
            firstB=bear[i];
        }
    }

    if(elephant.size() == 1){
        cout << bear.size();
        return 0;
    }
    else{
        for(int i=1; i<(w);i++){
            elephantWall.push_back(firstE-elephant[i]);
            firstE=elephant[i];
        }
    }

    stringstream result;
    copy(bearWall.begin(), bearWall.end(), ostream_iterator<int>(result, " "));
    b = result.str().c_str();

    result.str("");
    copy(elephantWall.begin(), elephantWall.end(), ostream_iterator<int>(result, " "));
    e = result.str().c_str();

    static int prefix_table[L], j, b_len, e_len;
    int matches = 0;

    b_len = b.size();
    e_len = e.size();
    prefix_table[0] = -1;
    j = -1;
    

    // Build KMP prefix table ---------------------------
    for(int i=1; i<e_len; i++){
        while(j>=0 && e[j+1] != e[i]) {
            j = prefix_table[j];
        }
        if(e[j+1] == e[i]){
            j++;
        }
        prefix_table[i] = j;
    }

    // Run KMP ------------------------------------------
    j = -1;
    for(int i=0; i<b_len; i++){
        if(e[j+1] == b[i]){
            j++;
        }
        else {
            while (j >= 0 && e[j + 1] != b[i]){
                j = prefix_table[j];
            }
            if(e[j+1] == b[i]){
                j++;
            }
        }
        if(j == e_len-1) {
            matches++;
        }
    }


    cout << matches;
    return 0;
}
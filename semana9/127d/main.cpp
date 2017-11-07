#include <iostream>
#include <vector>

using namespace std;

#define L 100000


long long int kmp(string s, string t){
    int prefix_table[L], j, s_len, t_len, i;
    j = -1;
    prefix_table[0] = -1;
    s_len = s.size();
    t_len = t.size();
    // Build KMP prefix table ---------------------------
    for(i=1; i<t_len; i++){
        while(j>=0 && t[j+1] != t[i]) {
            j = prefix_table[j];
        }
        if(t[j+1] == t[i]){
            j++;
        }
        prefix_table[i] = j;
    }
    // Run KMP ------------------------------------------
    j = -1;
    for(i=0; i<s_len; i++){
        if(t[j+1] == s[i]){
            j++;
        }
        else {
            while (j >= 0 && t[j + 1] != s[i]){
                j = prefix_table[j];
            }
            if(t[j+1] == s[i]){
                j++;
            }
        }
        if(j == t_len-1) {
            return 1;
        }
    }
    return 0;
}

int main(){
    string s, t,suffix;
    int i, s_len;
    vector <int> indexes;
    cin >> s;
    s_len = s.size();
    string middlestr = s.substr(1,s_len-2);
    for(i = s_len-2; i > 0; i--){
        t = s.substr(0,i);
        suffix = s.substr(s_len-t.size(),s_len);
        if(kmp(suffix,t)!=0){
            if(kmp(middlestr,t) != 0){
                cout << t << endl;
                return 0;
            }
        }
    }
    cout << "Just a legend" << endl;
    return 0;
}

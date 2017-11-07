#include <iostream>

using namespace std;

#define L 100000
#define M 1000000007

int main(){
    // static for memory issues in Windows
    static int prefix_table[L], j, s_len, t_len, i;
    static long long DP[L], left_matches[L], sums[L], total[L], m, result;
    string s, t;

    cin >> s >> t;
    DP[0] = 0;
    sums[0] = 0;
    total[0] = 0;
    result = 0;
    j = -1;
    m = M;
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
            left_matches[i] = 1;
        }
    }

    // Run DP ----------------------------------------------
    for(i=1; i<=s_len; i++){
        if(left_matches[i-1]){ // if the pattern matches from that position backward
            DP[i] = total[i-t_len] + i-t_len+1;
            DP[i] %= m;
            sums[i] = DP[i] + sums[i-1];
            sums[i] %= m;
        } else {
            DP[i] = DP[i-1];
            sums[i] = DP[i] + sums[i-1];
            sums[i] %= m;
        }
        total[i] = sums[i] + total[i-1];
        total[i] %= m;
        result += DP[i];
        result %= m;
    }
    cout << result << endl;
    return 0;
}
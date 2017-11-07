#include <iostream>

using namespace std;

#define L 100000
#define M 1000000007

int main(){
    int partition[L];
    int j, st_len, pattern_len, i;
    long long DP[L], left_matches[L], sums[L], total[L];
    long long m, result;
    string s, t;

    cin >> s >> t;
    DP[0] = 0;
    sums[0] = 0;
    total[0] = 0;
    result = 0;
    j = -1;
    m = M;
    partition[0] = -1;
    st_len = s.size();
    pattern_len = t.size();

    for(i=1; i<pattern_len; i++){
        while(j>=0 && t[j+1] != t[i]) {
            j = partition[j];
        }
        if(t[j+1] == t[i]){
            j++;
        }
        partition[i] = j;
    }
    j = -1;
    for(i=0; i<st_len; i++){
        if(t[j+1] == s[i]){
            j++;
        }
        else {
            while (j >= 0 && t[j + 1] != s[i]){
                j = partition[j];
            }
            if(t[j+1] == s[i]){
                j++;
            }
        }
        if(j == pattern_len-1) {
            left_matches[i] = 1;
        }
    }
    for(i=1; i<=st_len; i++){
        if(left_matches[i-1]){
            DP[i] = total[i-pattern_len] + i-pattern_len+1;
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
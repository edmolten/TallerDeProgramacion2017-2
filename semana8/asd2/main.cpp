#include <iostream>

using namespace std;

#define L 10//0000
#define M 1000000007

int main(){
    int partition[L], j, st_len, pattern_len;;
    long long DP[L], left_matches[L], sums[L], total[L], m;
    string s, t;
    j = -1;
    m = M;
    partition[0] = -1;
    cin >> s >> t;
    st_len = s.size();
    pattern_len = t.size();
    for(int i=1; i<pattern_len; i++){
        while(j>=0 && t[j+1] != t[i]) {
            j = partition[j];
        }
        if(t[j+1] == t[i]){
            j++;
        }
        partition[i] = j;
    }
    j = -1;
    for(int i=0; i<st_len; i++){
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
    DP[0] = sums[0] = total[0] = 0;
    long long ans = 0;
    for(int i=1;i<=st_len;++i){
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
        ans += DP[i];
        ans %= m;
    }
    cout << ans << endl;
    return 0;
}
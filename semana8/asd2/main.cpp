#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

long long MOD = (long long) 1e9 + 7LL;


string s, t;
int par[100005];
long long f[100005], g[100005], sum[100005], tot[100005];

int N, M;
int main(){
    cin >> s >> t;
    N = s.size();
    M = t.size();
    int k = -1;
    par[0] = -1;
    for(int i=1;i<M;++i){
        while(k>=0 && t[k+1] != t[i]) k = par[k];
        if(t[k+1] == t[i]) ++k;
        par[i] = k;
    }
    k = -1;
    for(int i=0;i<N;++i){
        if(t[k+1] == s[i]) ++k;
        else {
            while(k>=0 && t[k+1] != s[i]) k = par[k];
            if(t[k+1] == s[i]) ++k;
        }
        if(k == M-1) {
            g[i] = 1;
        }
    }
    f[0] = sum[0] = tot[0] = 0;
    long long ans = 0;
    for(int i=1;i<=N;++i){
        if(g[i-1]){
            f[i] = tot[i-M] + i-M+1;
            f[i] %= MOD;
            sum[i] = f[i] + sum[i-1];
            sum[i] %= MOD;
        } else {
            f[i] = f[i-1];
            sum[i] = f[i] + sum[i-1];
            sum[i] %= MOD;
        }
        tot[i] = sum[i] + tot[i-1];
        tot[i] %= MOD;
        ans += f[i];
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

const int LIMIT = 3000; // 2000 throws out of bounds exception :(
vector<int> divisors[LIMIT];
int dp[LIMIT][LIMIT];
int MODULE = 1000000007;

void fill_divs(){
    for(int i = 1; i < LIMIT; i++)
        for(int j = i; j < LIMIT; j+=i)
            divisors[j].push_back(i);
}

int sum(int len, int ends_with)
{
    if(len == 1) return 1; // base case
    if(dp[len][ends_with] != -1) return dp[len][ends_with]; // known dp
    int n = divisors[ends_with].size();
    int res = 0;
    for(int i = 0; i < n; i++)
        res = (res + sum(len - 1, divisors[ends_with][i])) % MODULE;
    dp[len][ends_with] = res;
    return res;
}

int main() {
    fill_divs();
    memset(dp, -1, sizeof dp);
    int n, k;
    int res = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        res = (res + sum(k, i)) % MODULE;
    cout << res;
    return 0;
}
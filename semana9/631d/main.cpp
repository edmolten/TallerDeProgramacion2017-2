#include <cstdlib>
#include <utility>
#include <cstdio>
using namespace std;

#define L 200000

// usual kpm table, but modified to work with the pairs defined for the problem
void get_kpm_prefix_table(pair<unsigned long long, char> t[L], int table[L], int m) {
    int j=0;
    for(int i=0; i<m-1; i++) { //fill with 0
        table[i] = 0;
    }
    for(int i=2; i<m-1; i++) {
        while (j && (t[i+1].second != t[j + 2].second || t[i+1].first != t[j + 2].first)){
            j = table[j];
        }
        if(t[i+1].second == t[j+2].second && t[i+1].first == t[j+2].first) {
            j++;
        }
        table[i]=j;
    }
}

// usual kpm, but modified to work with the pairs defined for the problem
unsigned long long run_kpm(int table[L],
                           pair<unsigned long long, char> s[L],
                           pair<unsigned long long, char> t[L],
                           int n,
                           int m){
    int j=0;
    unsigned long long result = 0;
    for(int i=1;i<=n;i++) {
        while (j && (s[i].second != t[j + 2].second || s[i].first != t[j + 2].first)){
            j = table[j];
        }
        if(s[i].second == t[j+2].second && s[i].first == t[j+2].first) {
            j++;
        }
        if(j == m-2) {
            if(s[i-m+2].second==t[1].second && t[1].first<=s[i-m+2].first
               && s[i+1].second==t[m].second && t[m].first<=s[i+1].first) {
                result ++;
            }
            j = table[j];
        }
    }
    return result;
}

// gets inputs with format n1-c1 n2-c2 ...
void get_input(pair<unsigned long long, char> pairs[L], int limit){
    unsigned long long n;
    char c;
    for(int i = 1; i< limit + 1; i++){
        scanf("%I64d-%c",&n, &c); // codeforces uses %I64d, we use %llu
        pairs[i].first = n;
        pairs[i].second = c;
    }
}

// Accumulates the different character occurrences in the first positions of t
// If there are pairs n1-c1 n2-c1 n3-c1, it becomes (n1+n2+n3)-c1
// n changes to the value of different characters, so everything else is ignored
void acumulate_chars(pair<unsigned long long, char> s[L], int * n){
    char current_char = s[1].second;
    unsigned long long current_num = s[1].first;
    int j = 0;
    for(int i = 2; i < *n +1; i++){
        if(s[i].second == current_char){
            current_num += s[i].first;
        }
        else{
            j++;
            s[j].first = current_num;
            s[j].second = current_char;
            current_char=s[i].second;
            current_num=s[i].first;
        }
    }
    j++;
    s[j].first = current_num;
    s[j].second = current_char;
    *n = j;
}

int main(){
    int n,m;
    // static for memory issues
    static pair<unsigned long long, char> s[L], t[L];
    scanf("%d %d",&n, &m);
    get_input(s,n);
    get_input(t,m);
    acumulate_chars(s, &n);
    acumulate_chars(t, &m);
    unsigned long long result = 0;
    if(m == 1){ // case 1: pattern have just one different character
        for(int i=1;i<=n;i++) {
            // if char is the same and fits
            if (s[i].second == t[1].second && s[i].first >= t[1].first) {
                result += (s[i].first - t[1].first + 1);
            }
        }
    }
    else if (m == 2){ // case 2: pattern have two different characters
        int j=1;
        for(int i=1;i<=n;i++) {
            if(s[i].second==t[j].second && s[i].first >= t[j].first){ // same as case 1
                if(j==2) {
                    result++;
                }
                j=(j+1)%3;
                if(j==0) {
                    j = 1;
                }
            }
            else j=1;
        }
    }
    else { // case 3: we use KPM
        // static for memory issues
        static int table[L];
        get_kpm_prefix_table(t, table, m);
        result = run_kpm(table, s, t, n, m);
    }
    printf("%I64d\n",result); // codeforces uses %I64d, we use %llu
}
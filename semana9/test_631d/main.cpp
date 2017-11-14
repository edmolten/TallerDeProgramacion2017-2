#include <bits/stdc++.h>
#define maxn 7
#define REP(i,x,y) for(int i=x;i<(y);i++)
using namespace std;
typedef long long ll;
struct P{
    char ch;
    ll num;
    P(){}
    P(char ch,ll num):ch(ch),num(num){}
};
int n,m,cnt1,cnt2;

ll ans=0;
int nxt[maxn];

void get_next(P t[]) {
    int j=0;
    for(int i=2;i<m-1;i++) {
        while(j&&(t[i].ch!=t[j+1].ch||t[i].num!=t[j+1].num)) j=nxt[j];
        if(t[i].ch==t[j+1].ch&&t[i].num==t[j+1].num) j++;
        nxt[i]=j;
    }
}
void kmp(P s[],P t[]) {
    int j = 0;
    for(int i = 1; i <= n; i++) {
        while (j && (s[i].ch != t[j + 1].ch || s[i].num != t[j + 1].num)){
            j = nxt[j];
        }
        if(s[i].ch == t[j+1].ch && s[i].num == t[j+1].num){
            j++;
        }
        if(j == m-2) {
            if(s[i-m+2].ch==t[0].ch&&t[0].num<=s[i-m+2].num&&s[i+1].ch==t[m-1].ch&&t[m-1].num<=s[i+1].num){
                ans++;
            }
            j=nxt[j];
        }
    }
}
int main()
{
    static P s[maxn],t[maxn];
    scanf("%d %d",&n,&m);
    REP(i,1,n+1) scanf("%llu-%c",&s[i].num,&s[i].ch);
    REP(i,1,m+1) scanf("%llu-%c",&t[i].num,&t[i].ch);
    char head=s[1].ch;
    ll num=s[1].num;
    REP(i,2,n+1) {
        if(head!=s[i].ch) {
            s[++cnt1]=P(head,num);
            head=s[i].ch;
            num=s[i].num;
        }
        else num+=s[i].num;
    }
    s[++cnt1]=P(head,num);
    n=cnt1;
    head=t[1].ch;num=t[1].num;
    REP(i,2,m+1) {
        if(head!=t[i].ch) {
            t[++cnt2]=P(head,num);
            head=t[i].ch;
            num=t[i].num;
        }
        else num+=t[i].num;
    }
    t[++cnt2]=P(head,num);
    m=cnt2;
    ans=0;
    if(m==1) {
        for(int i=1;i<=n;i++)
            if(s[i].ch==t[1].ch&&s[i].num>=t[1].num) ans+=(s[i].num-t[1].num+1);
        printf("%llu\n",ans);
    }
    else if(m==2) {
        int pos=1;
        for(int i=1;i<=n;i++) {
            if(s[i].ch==t[pos].ch&&s[i].num>=t[pos].num){
                if(pos==2) {
                    ans++;
                }
                pos=(pos+1)%3;
                if(pos==0) {
                    pos = 1;
                }
            }
            else pos=1;
        }
        printf("%llu\n",ans);
    }
    else {
        get_next(t+1);
        kmp(s,t+1);
        printf("%llu\n",ans);
    }
}
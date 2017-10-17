#include <cstdio>

int CATALAN[] = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796};
bool first = true;
int n;

int main(){
    while(scanf("%d",&n)==1){
        if(!first){
            printf("\n");
        }
        printf("%d\n",CATALAN[n]);
        first = false;
    }
    return 0;
}
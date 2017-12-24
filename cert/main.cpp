#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double n,h;
    cin >> n >> h;
    for(int i = 1; i < n; i++) {
        printf("%.12f ", h * sqrt(i / n)) ;
    }
    return 0;
}
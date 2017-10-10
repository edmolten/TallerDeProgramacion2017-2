#include <iostream>
using namespace std;

int factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


int main() {
    int n;
    cin >> n;
    while(n){
        cout << factorial(2*n)/(factorial(n+1)*factorial(n)) << endl;
        cin >> n;
    }
    return 0;
}
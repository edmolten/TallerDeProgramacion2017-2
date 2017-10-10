#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

double factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


int main() {
    int n;
    string z;
    double a, b, c;
    while(true){

        cin >> z;
        if(z=="\n") break;
        n = stoi(z);
        a= factorial(2*n);
        b=factorial(n+1);
        c= factorial(n);
        cout << a/(b*c) << endl;
    }
    return 0;
}
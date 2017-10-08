
using namespace std;

double find_nth_root(double n, double p)
{
    double low = 0, high = 1;
    while (pow(high, n) <= p) {
        low = high;
        high *= 2;
    }
    while (low != high - 1) {
        double k = (high - low) / 2;
        double value = pow(k, n);
        if (value == p) {
            return k;
        }
        if (value < p) {
            low = k;
        } else        {
            high = k;
        }
    }
    return low;
}

#include <iostream>
#include <cmath>

int main() {
    double n,p;
    while(scanf("%lf %lf",&n,&p)==2) {
        printf("%.0lf\n", pow(p, 1/n));
    }
    return 0;
}
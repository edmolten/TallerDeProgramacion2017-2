#include <iostream>
#include <math.h>
#include <vector>

using namespace std;



int main() {
    int n;
    vector<int> primes(4792);
    vector<bool> isPrime(46340, true);
    primes[0] = 2;
    int pos(1);

    for (long long i = 3; i < 46340; i += 2)
    {
        if (isPrime[i])
        {
            for (long long j = i * i; j < 46340; j += i)
            {
                isPrime[j] = false;
            }

            primes[pos] = i;
            ++pos;
        }
    }
    do {
        cin >> n;
        if (n < 0) {
            cout << n << " = -1 x ";
            n = n * -1;
        } else {
            cout << n << " = ";
        }
        int mayorPrime = 0;

        for (int i = 0; i < primes.size(); i++) {
            if (primes[i] <= n) {
                mayorPrime++;
            } else break;

        }

        vector<int> result(mayorPrime);


        for (int i = 0; i < primes.size(); i++) {
            if (n % primes[i] == 0) {
                n = n / primes[i];
                result[i]++;
                --i;
            }
            if (n == 1)break;
        }
        int q = 0;

        for(int w = 0; w < result.size(); w++){
            if(result[w]!=0){
                for(int r=0; r<result[w];r++){
                    if(q==0) {
                        cout  << primes[w];
                    }else cout << " x " << primes[w];
                    q++;

                }
            }
        }
        cout << endl;

    }while(n!=0);


    return 0;
}
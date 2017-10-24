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

    cin >> n ;
    int mayorPrime;
    while(n!=0){
        mayorPrime = 0;
        for(int i=0; i< primes.size(); i++ ){
            if(primes[i]<=n){
                mayorPrime++;
            }

        }
        int result[mayorPrime];

        for(int j = 0; j < mayorPrime; j++){
            int floor;
            int a=1;
            int k = 0;
            do{
                floor = n/pow(primes[j],a);
                k += floor;
                a++;
            }while(floor != 0);
            result[j]=k;
        }
        cout << n;
        cout << "! = ";
        for(int w=0; w<mayorPrime; w++){
            cout << result[w];
            if(w!=mayorPrime-1){
                cout << " ";
            }
        }
        cout << endl;
        cin >> n;
    }


    return 0;
}
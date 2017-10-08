#include <iostream>
#include <math.h>
using namespace std;



int main() {
    int n;
    int primes[]= {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    cin >> n ;
    int mayorPrime;
    while(n!=0){
        mayorPrime = 0;
        for(int i=0; i< 25; i++ ){
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
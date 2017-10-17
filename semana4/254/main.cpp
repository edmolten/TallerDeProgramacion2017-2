#include <bitset>
#include <iostream>

using namespace std;

void swap(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int string_number_to_reverse_binary(string string_number, int binary[]){
    int a[128] = {0};
    int binary_size = 0;
    int string_number_size = string_number.size();
    for (int i = 0; i < string_number_size ; i++) {
        a[i] = string_number[string_number_size - 1 - i] - '0';
        cout << "a[" << i << "] = " << a[i] << endl;
    }
    while (string_number_size){
        int mod = 0, mul;
        for (int i = string_number_size - 1; i >= 0; i--)
        {
            mul = mod * 10 + a[i];
            a[i] = mul >> 1;
            mod = mul & 1;
        }
        if(mod){
            binary[binary_size] = 1;
        }
        else{
            binary[binary_size] = 0;
        }
        cout << binary[binary_size] << " ";
        binary_size++;
        if (!a[string_number_size - 1]) {
            string_number_size--;
        }
    }
    cout << endl;
    return binary_size;
}
int main(){
    int n, T1, T2, T3;;
    string m;
    cin >> n >> m;
    int binary[100]; //suficiente para representar 2^100-1, cada celda es 1 o 0
    while ( n!=0 and m != "0"){
        int binary_size = string_number_to_reverse_binary(m, binary);
        T1 = 0; T2 = 0; T3 = 0;
        for (int i = binary_size-1; i >= 0; i--) {
            printf("%c ", binary[i]);
            int bit = binary[i];
            if (bit == 1){
                T3++;
                swap(&T1, &T2);
//                tmp = T1; T1 = T2; T2 = tmp;
            }
            else{
                T1++;
                swap(&T2, &T3);
                //tmp = T2; T2 = T3; T3 = tmp;
            }
        }
        int left = n - binary_size;
        if (left & 1){
            swap(&T2, &T3);
           /* tmp = T2;
            T2 = T3;
            T3 = tmp;*/
        }
        T1 += left;
        if (n & 1){
            printf("%d %d %d\n", T1, T3, T2);
        }
        else {
            printf("%d %d %d\n", T1, T2, T3);
        }
        cin >> n >> m;
    }
    return 0;
}

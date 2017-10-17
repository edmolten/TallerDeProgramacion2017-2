#include <iostream>
#include <stack>

using namespace std;

typedef stack <int> pila;

int main() {

    int n, steps, torre_actual, torre_objetivo, disk, torreA, torreB;

    pila torre[3];

    cin >> n >> steps;

    while(n != 0 && steps != 0) {
        for (int i = n; i > 0; i--) {
            torre[0].push(i);
        }

        for (int j = 0; j < steps; j++) {

            if (j % 2 == 0) {

                torre_actual = (j * 2) % 3;
                torre_objetivo = (torre_actual + 1) % 3;

                disk = torre[torre_actual].top();
                torre[torre_actual].pop();
                torre[torre_objetivo].push(disk);
            }

            else {
                torreA = (torre_objetivo + 1) % 3;
                torreB = (torreA + 1) % 3;

                if (torre[torreA].empty()) {
                    disk = torre[torreB].top();
                    torre[torreB].pop();
                    torre[torreA].push(disk);
                } else if (torre[torreB].empty()) {
                    disk = torre[torreA].top();
                    torre[torreA].pop();
                    torre[torreB].push(disk);
                } else {
                    if (torre[torreA].top() > torre[torreB].top()) {
                        disk = torre[torreB].top();
                        torre[torreB].pop();
                        torre[torreA].push(disk);
                    } else {
                        disk = torre[torreA].top();
                        torre[torreA].pop();
                        torre[torreB].push(disk);
                    }
                }
            }
        }

        cout << torre[0].size() << " " << torre[1].size() << " " << torre[2].size() << endl;

        torre[0] = pila();
        torre[1] = pila();
        torre[2] = pila();

        cin >> n >> steps;
    }
    return 0;
}
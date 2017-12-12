

#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

#define INF 1e9
#define EPS 1e-8


struct point_i { double x, y;   // only used if more precision is needed
    point_i() { x = y = 0.0; }                      // default constructor
    point_i(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator < (point_i other) const { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y; }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator == (point_i other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); } };


double dist(point_i p1, point_i p2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double

point_i centerCircleRadius(point_i a, point_i b, double r){
    double distance = dist(a, b);
    double squaredDistance = distance * distance;
    double k = sqrt((r*r)/squaredDistance - 0.25);

    point_i center;

    center.x = (a.x + b.x)/2 + k*(b.y - a.y);
    center.y = (a.y + b.y)/2 + k*(a.x - b.x);

    return center;
}

int main(){
    int x, y, n;
    double radio;
    bool flag = false;
    vector<point_i> puntos;

    while(cin >> n){
        if(!n){
            break;
        }

        puntos.clear();

        for(int i = 0; i < n; i++){
            cin >> x >> y;
            point_i puntoAux;
            puntoAux.x = x;
            puntoAux.y = y;
            puntos.push_back(puntoAux);
        }

        cin >> radio;

        if(radio == 0.0){
            flag = true;
            cout << "There is no way of packing that polygon." << endl;
        }
        else if(puntos.size() == 1){
            flag = true;
            cout << "The polygon can be packed in the circle." << endl;
        }
        else{
            for (int i = 0; i < n && !flag; i++) {
                for (int j = 0; j < n && !flag; j++) {
                    if(dist(puntos[i], puntos[j]) - 2 * radio > EPS){
                        flag = true;
                        cout << "There is no way of packing that polygon." << endl;
                    }
                }
            }

            if(!flag){
                for (int i = 0; i < n && !flag; i++) {
                    for (int j = i+1; j < n && !flag; j++) {
                        point_i center1 = centerCircleRadius(puntos[i], puntos[j], radio);
                        point_i center2 = centerCircleRadius(puntos[j], puntos[i], radio);
                        flag = true;
                        for(int k = 0; k < n; k++){
                            //cout << center1.x << center1.y << " " << center2.x << center2.y << endl;
                            if(dist(puntos[k], center1) - radio > EPS || dist(puntos[k], center1) - radio > EPS){
                                flag = false;
                                break;
                            }
                        }
                    }
                }

                if(flag) cout << "The polygon can be packed in the circle." << endl;
                else{
                    cout << "There is no way of packing that polygon." << endl;
                }
            }
        }
        flag = false;
    }
}
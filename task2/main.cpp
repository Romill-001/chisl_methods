#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#define E 2.71828182846

using namespace std;

double left_triangles(int a, int b, vector<double> points) {
    double sum;
    for (int i = a; i < b; i++) {
        sum += (points[i+1] - points[i]) * (pow(E, (-points[i])));
    }
    return sum;
}

double right_triangles(int a, int b, vector<double> points) {
    double sum;
    for (int i = a; i < b; i++) {
        sum += (points[i+1] - points[i]) * (pow(E, (-points[i+1])));
    }
    return sum;
}

int main() {
    vector<double> points {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0};
    printf("%.8lf\n", left_triangles(0,11,points));
    printf("%.8lf\n", right_triangles(0,11,points));
    return 0;
}
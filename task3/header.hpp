#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double f_x(double x) {
    return -pow(x,5) + 22 * pow(x,4) - 36 * pow(x,3) + 28 * pow(x,2) - 19 * x + 6;
    //return -pow(x, 6) + 26 * pow(x, 4) + 4 * pow(x, 3) - 12 * pow(x, 2);
}

double u_x(double x) {
    return x * pow((1 - x), 3);
    //return pow(x, 4) * (1 - x);
}

double p_x(double x) {
   return 1 + pow(x, 2);
   //return 1 + x;
}

double q_x(double x) {
    return 1 + x;
}

void progonka_method(vector<vector<double>> &A, vector<double> &alpha, vector<double> &betta, vector<double> &x, int n) {
    double h = 1.0 / n;

    // прямой ход
    alpha[0] = A[0][1] / A[0][0];
    betta[0] = -(f_x(1 * h)* pow(h, 2) / A[0][0]);

    for (int i = 1; i <= n - 1; ++i) {
        double del = 1.0 / (A[i][i] - alpha[i - 1] * A[i][i - 1]);
        alpha[i] = A[i][i + 1] * del;
        betta[i] = (A[i][i - 1] * betta[i - 1] - f_x((i + 1) * h) * pow(h,2)) * del;
    }

    // обратный ход
    x[n - 1] = betta[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = alpha[i] * x[i + 1] + betta[i];
    }

    for (int i = 0; i <= n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | u(ih) = %8.6lf | |y_i - u(ih)| = %8.6lf\n", i * h, x[i], u_x(i * h), abs(x[i] - u_x(i * h)));
    }
}

vector<vector<double>> create_matrix(int n){

    double h = 1. / n;

    vector<vector<double>> matrix_res(n, vector<double>(n,0.0));

    for (int i = 0; i <= n - 1; i++) {
        if (i == 0) {
            double b = (p_x((i + 1) * h) + p_x((i + 2) * h) + (pow(h,2) * q_x((i + 1) * h)));
            double c = -p_x((i + 2) * h);
            matrix_res[i][i] = -b;
            matrix_res[i][i + 1] = -c;
            continue;
        }
        if (i == (n - 1)) {
            double b = (p_x((i + 1) * h) + p_x((i + 2) * h) + (pow(h,2) * q_x((i + 1) * h)));
            double a = -p_x((i + 1) * h);
            matrix_res[i][i] = -b;
            matrix_res[i][i - 1] = -a;
            continue;
        }
        double a = -p_x((i + 1) * h);
        double b = (p_x((i + 1) * h) + p_x((i + 2) * h) + (pow(h,2) * q_x((i + 1) * h)));
        double c = -p_x((i + 2) * h);
        matrix_res[i][i] = -b;
        matrix_res[i][i + 1] = -c;
        matrix_res[i][i - 1] = -a;
    }
    return matrix_res;
}

double calculate_new_x(int i, vector<double>& x, int n, vector<vector<double>> &A) {

    double h = 1. / n;
    
    double sum1 = 0.0;
    double sum2 = 0.0;

    if (i > 0) {
        for (int j = 1; j <= i - 1; j++) {sum1 += A[i][j] * x[j];}
    }

    if (i < n - 1) {
       for (int j = i + 1; j <= n; j++) {sum2 += A[i][j] * x[j];}
    }
    return (f_x(i * h) * pow(h, 2) - sum1 - sum2) / (A[i][i]);
}

void Seidel_method(int maxK, int n, vector<double> &x, vector<vector<double>> &A) {

    double h = 1. / n;

    int k = 0;
    double error = 0.0;
    while (error <= pow(h,3)) {
        for (int i = 0; i < n; ++i) {
            double new_x = calculate_new_x(i, x, n, A);
            error = max(error, abs(x[i] - new_x));
            x[i] = new_x;
        }
        k++;
    }
    for (int i = 0; i <= n; ++i) {
        printf("ih = %4.2lf | y_i = %9.10lf | k = %d, err = %9.10lf\n", i * h, x[i], k, error);
    }
}
double calculate_new_x_relax(int i, vector<double> &x, int n, double omega) {

    double h = 1. / n;
    
    double sum1 = 0.0;
    double sum2 = 0.0;

     if (i >= 1) {
        for (int j = 1; j <= i - 1; j++) {sum1 += p_x(j * h) * x[j];}
    }

    if (i <= n - 1) {
       for (int j = i + 1; j <= n; j++) {sum2 += p_x(j * h) * x[j];}
    }

    double new_x = (f_x(i * h) * pow(h, 2) - sum1 - sum2) / (p_x(i * h) + p_x((i + 1) * h) + pow(h, 2) * q_x(i * h));
    return x[i] + omega * (new_x - x[i]);
}

void relax_bottom(int maxK, int n, vector<double> &x) {
    double h = 1. / n;

    int k = 0;
    double error = 0.0;
    double omega = 0.1;
    x[0] = 0;
    while (error <= pow(h,3) && k < maxK) {
        error = 0.0;
        for (int i = 1; i <= n; ++i) {
            double new_x = calculate_new_x_relax(i, x, n, omega);
            error = max(error, abs(new_x - x[i]));
            x[i] = new_x;
        }
        k++;
    }
    for (int i = 0; i <= n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | u(ih) = %8.6lf | |y_i - u(ih)| = %8.6lf\n", i * h, x[i], u_x(i*h), abs(x[i] - u_x(i*h)));
    }
}
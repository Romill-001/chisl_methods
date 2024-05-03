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

vector<double> func_vec(int n) {
    double h = 1. / n;
    vector<double> b(n,0);
    for (int i = 1; i <= n; ++i) {
        b[i - 1] = f_x(i * h) * pow(h,2);
    }
    return b;
}
//Алгорит Томаса
void progonka_method(vector<vector<double>> &A, vector<double> &x, int n, vector<double> &b) {
    
    vector<double> alpha(n + 1), betta(n + 1);

    double h = 1.0 / n;

    // прямой ход
    alpha[0] = A[0][1] / A[0][0];
    betta[0] = (b[0]) / A[0][0];

    for (int i = 1; i < n; ++i) {
        double del = 1.0 / (A[i][i] - alpha[i - 1] * A[i][i - 1]);
        alpha[i] = A[i][i + 1] * del;
        betta[i] = (-A[i][i - 1] * betta[i - 1] + b[i]) * del;
    }

    // обратный ход
    x[n - 1] = betta[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = -alpha[i] * x[i + 1] + betta[i];
    }

    for (int i = 0; i < n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | u(ih) = %8.6lf | |y_i - u(ih)| = %8.6lf\n", i * h, x[i], u_x(i * h), abs(x[i] - u_x(i * h)));
    }
}

vector<vector<double>> create_matrix(int n){

    double h = 1. / n;

    vector<vector<double>> matrix_res(n, vector<double>(n,0.0));

    for (int i = 0; i < n; ++i) {
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

double calculate_new_x(int i, vector<double>& x, int n, vector<vector<double>> &A, vector<double> &b) {
    double h = 1.0 / n;
    double sum1 = 0.0;

    if (i > 0) {
        for (int j = 0; j <= i - 1; ++j) {
            sum1 += A[i][j] * x[j];
        }
    }

    if (i < n - 1) {
        for (int j = i + 1; j < n; ++j) {
            sum1 += A[i][j] * x[j];
        }
    }

    return (b[i] - sum1) * (1.0 / A[i][i]);
}

double calculate_error(vector<double> &new_x, vector<double> &old_x) {

    double max_err = 0.0;
    for (int i = 0; i < old_x.size(); ++i) {
        double err = abs(new_x[i] - old_x[i]);
        if (err > max_err)
            max_err = err;
    }

    return max_err;
}
void Seidel_method(int maxK, int n, vector<double> &x, vector<vector<double>> &A, vector<double> &b) {
    double h = 1.0 / n;
    int k = 1;
    vector<double> new_x(n, 0.);
    x[0] = 0;
    double error = 1.0;

    while (error > 1e-6 && k < maxK) {

        vector<double> curr_x = x;

        for (int i = 0; i < n; ++i) {
            new_x[i] = calculate_new_x(i, curr_x, n, A, b);
        }

        error = calculate_error(new_x, curr_x);

        x = new_x;

        k++;
    }

    for (int i = 0; i < n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | k = %d\n", i * h, x[i], k);
    }
}
double calculate_new_x_relax(int i, vector<double>& x, int n, vector<vector<double>> &A, double omega, vector<double> &b) {
    
    double sum1 = 0.0;

    if (i > 0) {
        for (int j = 0; j <= i - 1; ++j) {
            sum1 += A[i][j] * x[j];
        }
    }

    if (i < n - 1) {
        for (int j = i + 1; j < n; ++j) {
            sum1 += A[i][j] * x[j];
        }
    }

    double new_x = (b[i] - sum1) * (1.0 / A[i][i]);
    return x[i] + omega * (new_x - x[i]);
}

void relax_bottom(int maxK, int n, vector<double>& x, vector<vector<double>>& A, vector<double>& b) {
    double h = 1.0 / n;
    double omega = 0.8;

    int glob_k = 0;
    double glob_err = 0.;
    for (int k = 1; k <= maxK; ++k) {
        vector<double> new_x(n, 0.0);

        for (int i = 0; i < n; ++i) {
            new_x[i] = calculate_new_x_relax(i, x, n, A, omega, b);
        }

        double error = calculate_error(new_x, x);

        if (error < 1e-6) {
            glob_k = k;
            glob_err = error;
            break;
        }

        x = new_x;
    }

    for (int i = 0; i < n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | k = %d\n", i * h, x[i], glob_k);
    }
}

double calculate_tau(const std::vector<double>& r, const std::vector<double>& Ar) {
    double a = 0.;
    double b = 0.;
    for (size_t i = 0; i < r.size(); ++i) {
        a += r[i] * r[i];
        b += Ar[i] * r[i];
    }
    if (std::abs(b) < 1e-10) {
        return 0.0;
    }
    return a / b;
}

double calculate_new_x_spusk(int i, const std::vector<double>& x, int n, const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    std::vector<double> r(n, 0.);
    std::vector<double> Ar(n, 0.);

    if (i == 0) {
        r[0] = A[0][0] * x[0] - b[0];
        Ar[0] = A[0][0] * r[0];
    } else {
        r[i] = A[i][i - 1] * x[i - 1] + A[i][i] * x[i];
        Ar[i] = A[i][i - 1] * r[i - 1] + A[i][i] * r[i];
        if (i < n - 1) {
            r[i] += A[i][i + 1] * x[i + 1];
            Ar[i] += A[i][i + 1] * r[i + 1];
        }
    }

    return x[i] - calculate_tau(r, Ar) * r[i];
}

void spusk(int maxK, int n, std::vector<double>& x, const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    double h = 1.0 / n;
    int k = 1;
    std::vector<double> new_x(n, 0.);
    new_x[0] = calculate_new_x_spusk(0, new_x, n, A, b);
    double error = 1.0;

    while (error >= 1e-6 && k < maxK) {

        std::vector<double> curr_x = x;

        for (int i = 1; i < n; ++i) {
            new_x[i] = calculate_new_x_spusk(i, curr_x, n, A, b);
        }

        error = calculate_error(new_x, curr_x);

        x = new_x;

        k++;
    }

    for (int i = 0; i < n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | k = %d\n", i * h, x[i], k);
    }
}
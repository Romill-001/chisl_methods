
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double f_x(double x) {
    return 6  - (x * x * x * x * x) + (22 * x * x * x * x) - (36 * x * x + x) + (28 * x * x) - (19 * x);
}

double u_x(double x) {
    return - (x * x * x * x) + (3 * x * x * x) - (3 * x * x) + x;
}

double p_x(double x) {
    return 1 + x * x;
}

double q_x(double x) {
    return 1 + x;
}

int main() {
    int n = 10.0;
    std::vector<double> alpha(n+1);
    std::vector<double> betta(n+1);
    std::vector<double> a(n+1);
    std::vector<double> b(n+1);
    std::vector<double> c(n+1);
    std::vector<double> y_i(n+1);
    std::vector<double> a_i(n+1);
    std::vector<double> q_i(n+1);
    std::vector<double> u_i(n+1);
    std::vector<double> f_i(n+1);

    double h = 1.0 / n;

    for (int i = 0; i <= n; ++i) {
        a_i[i] = p_x(i * h);
        q_i[i] = q_x(i * h);
        u_i[i] = u_x(i * h);
        f_i[i] = f_x(i * h) * h * h;
    }

    for (int i = 0; i <= n - 1; ++i) {
        a[i] = a_i[i];
        b[i] = -(a_i[i] + a[i + 1] + h * h * q_i[i]);
        c[i] = a_i[i + 1];
    }

    alpha[1] = c[0] / b[0];
    betta[1] = -(f_i[0] / b[0]);
    
    for (int i = 1; i <= n - 1; ++i) {
        alpha[i + 1] = c[i] / (b[i] - alpha[i] * a[i]);
        betta[i + 1] = (a[i] * betta[i] - f_i[i]) / (b[i] - alpha[i] * a[i]);
    }

    for (int i = n - 1; i >= 0; --i) {
        y_i[i] = alpha[i + 1] * y_i[i + 1] + betta[i + 1];
    }

    for (int i = 0; i <= n; ++i) {
        printf("ih = %4.2lf | y_i = %9.6lf | u(ih) = %8.6lf | |y_i - u(ih)| = %8.6lf\n", i * h, y_i[i], u_i[i], abs(y_i[i] - u_i[i]));
    }
    return 0;
}

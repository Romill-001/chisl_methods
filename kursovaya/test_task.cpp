#include <iostream>
#include <vector>
#include <cmath>

std::vector<double> f(double x, const std::vector<double>& y) {
    double y1 = y[0];
    double y2 = y[1];
    std::vector<double> dy(2);
    dy[0] = -y2 + y1*(pow(y1, 2) + pow(y2, 2) - 1);
    dy[1] = y1 + y2*(pow(y1, 2) + pow(y2, 2) - 1);
    return dy;
}

std::vector<double> multiply(double scalar, const std::vector<double>& vec) {
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = scalar * vec[i];
    }
    return result;
}

std::vector<double> add(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    std::vector<double> result(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

std::vector<std::vector<double>> runge_kutta_4(double a, double b, const std::vector<double>& y0, double h) {
    int n = static_cast<int>((b - a) / h) + 1;
    std::vector<std::vector<double>> result(n, std::vector<double>(2));
    double x = a;
    std::vector<double> y = y0;

    for (int i = 0; i < n; ++i) {
        result[i][0] = y[0];
        result[i][1] = y[1];

        std::vector<double> k1 = f(x, y);
        std::vector<double> k2 = f(x + h / 2, add(y,  multiply(h / 2, k1)));
        std::vector<double> k3 = f(x + h / 2, add(y, multiply(h / 2, k2)));
        std::vector<double> k4 = f(x + h, add(y, multiply(h, k3)));

        for (int j = 0; j < 2; ++j) {
            y[j] += h / 6 * (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]);
        }
        x += h;
    }

    return result;
}

int main() {
    double a = 0.0;
    double b = 5.0;
    double h = 0.1;
    std::vector<double> y0 = {1.0 / sqrt(2), 1.0 / sqrt(2)};

    std::vector<std::vector<double>> solution = runge_kutta_4(a, b, y0, h);

    for (int i = 0; i < solution.size(); ++i) {
        printf("x = %5.2lf | y_1 = %9.6lf | y_2 = %9.6lf\n",a + i * h, solution[i][0], solution[i][1]);
    }

    return 0;
}

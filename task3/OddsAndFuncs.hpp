#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace odds {
    int n = 20;
    std::vector<double> alpha(n);
    std::vector<double> betta(n);
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> y_i(n);
    std::vector<double> a_i(n);
    std::vector<double> q_i(n);
    std::vector<double> u_i(n);
    std::vector<double> f_i(n);
}

double f_x(double x) {
    return 6 + (-1) * (std::pow(x,5)) + 22 * std::pow(x,4) - 36 * std::pow(x,3) + 28 * x * x - 19 * x;
}

double u_x(double x) {
    return (-1) * std::pow(x,4) + 3 * std::pow(x,3) - 3 * x * x + x;
}

double p_x(double x) {
    return 1 + x * x;
}

double q_x(double x) {
    return 1 + x;
}
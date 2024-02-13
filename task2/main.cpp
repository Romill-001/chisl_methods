#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace constans {
const int steps = 1024;
const double LEFT_BORDER = 0;
const double EPSILON = 1e-6;
const double E = 2.71828182846;
}  // namespace constans

double McLorenFunc(double x, int steps) {
  double result = 0;
  for (int n = 0; n < steps; ++n) {
    result += pow(-1, n) * pow(x, 2 * n + 1) / (tgamma(n + 1) * (2 * n + 1));
  }
  return 2 / sqrt(M_PI) * result;
}

double func(double t) { return (2 / sqrt(M_PI)) * pow(constans::E, -(t * t)); }

double leftRectangles(double (*func)(double), const double &a, double b,
                      int steps) {
  double result = 0.0;
  double h = (b - a) / steps;
  double x_i = 0.0;
  for (int i = 0; i < steps; i++) {
    x_i = a + h * i;
    result += h * func(x_i);
  }
  return result;
}

double rightRectangles(double (*func)(double), const double &a, double b,
                       int steps) {
  double result = 0.0;
  double h = (b - a) / steps;
  double x_i_1 = 0.0;
  for (int i = 1; i <= steps; i++) {
    x_i_1 = a + h * i;
    result += h * func(x_i_1);
  }
  return result;
}

double middleRectangles(double (*func)(double), const double &a, double b,
                        int steps) {
  double result = 0.0;
  double h = (b - a) / steps;
  double x_i = 0.0;
  double x_i_1 = 0.0;
  for (int i = 1; i <= steps; i++) {
    x_i = a + h * (i - 1);
    x_i_1 = a + h * i;
    result += h * func((x_i + x_i_1) / 2);
  }
  return result;
}

double trapezeFormula(double (*func)(double), const double &a, double b,
                      int steps) {
  double result = func(a) + func(b);
  double h = (b - a) / steps;
  double x_i_1 = 0.0;
  for (int i = 1; i <= steps; i++) {
    x_i_1 = a + h * i;
    result += 2 * func(x_i_1);
  }
  result *= h / 2;
  return result;
}

double SypmsonsFormula(double (*func)(double), const double &a, double b,
                       int steps) {
  double result = func(a) + func(b);
  double h = (b - a) / steps;
  double x_i_1 = 0.0;
  int k;
  for (int i = 1; i <= steps; i++) {
    k = 2 + 2 * (i % 2);
    x_i_1 = a + h * i;
    result += k * func(x_i_1);
  }
  result *= h / 3;
  return result;
}

void CalculateFunc(vector<double> points, double (*function)(double (*func)(double), const double&, double, int)) {
  for (auto point : points) {
    int i = 1;
    double diff = 0.0;
    do {
      diff = fabs(function(func, constans::LEFT_BORDER, point, i) -
                  function(func, constans::LEFT_BORDER, point, 2 * i));
      i++;
    } while (diff >= constans::EPSILON && i <= constans::steps);
    printf(
        "x_i = %.1lf | J_o = %.6lf | J_n = %.6lf | |J_o - J_n| = %.6lf | N "
        "= %d\n",
        point, McLorenFunc(point, 10),
        function(func, constans::LEFT_BORDER, point, i), diff, i);
  }
}
int main() {
  vector<double> points = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0,
                           1.2, 1.4, 1.6, 1.8, 2.0};
  cout << "Правые прямоугольники\n"; 
  CalculateFunc(points, rightRectangles);
  cout << "Левые прямоугольники\n";
  CalculateFunc(points, leftRectangles);
  cout << "Средние прямоугольники\n";
  CalculateFunc(points, middleRectangles);
  cout << "Трапеции\n";
  CalculateFunc(points, trapezeFormula);
  cout << "Симпсон\n";
  CalculateFunc(points, SypmsonsFormula);
  return 0;
}
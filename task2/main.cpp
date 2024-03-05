#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace constans {
const int STEPS = 1024;
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
  double h = (b - a) / steps;
    double result = 0;
    double x = 0;
    for (int i = 0; i < steps; i++)
    {
        result += (func(x) + 4 * func(x + h / 2) + func(x + h)) * h / 6;
        x += h;
    }
    return result;
}

double GaussFormula(double (*func)(double), const double &a, double b,
                       int steps) {
    double h = (b - a) / steps;
    double ad1 = (1 - 1.0 / sqrt(3)) * h / 2;
    double ad2 = (1 + 1.0 / sqrt(3)) * h / 2;
    double result = 0;
    double x = 0;
    for (int i = 0; i < steps; i++)
    {
        result += (func(x + ad1) + func(x + ad2)) * h / 2;
        x += h;
    }
    return result;
}

void CalculateFunc(vector<double> points,
                   double (*function)(double (*func)(double), const double &,
                                      double, int)) {
  for (auto point : points) {
    int i = 1;
    double last_j = 0.0;
    double j = 0.0;
    do {
      i++;
      last_j = j;
      j = function(func, constans::LEFT_BORDER, point, i);
    } while (fabs(last_j - j) > constans::EPSILON && i <= constans::STEPS);

    double difference = fabs(McLorenFunc(point, 15) - j);

    printf(
        "x_i = %.1lf | J_o = %.6lf | J_n = %.6lf | |J_o - J_n| = %.6lf | N "
        "= %d\n",
        point, McLorenFunc(point, 15), j, difference, i - 1);
  }
}


int main() {
  vector<double> points = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0,
                           1.2, 1.4, 1.6, 1.8, 2.0};
  cout << "Правые прямоугольники\n";
  CalculateFunc(points, rightRectangles);
  cout << "Левые прямоугольники\n";
  CalculateFunc(points, leftRectangles);
  cout << "Центральные прямоугольники\n";
  CalculateFunc(points, middleRectangles);
  cout << "Трапеции\n";
  CalculateFunc(points, trapezeFormula);
  cout << "Симпсон\n";
  CalculateFunc(points, SypmsonsFormula);
  cout << "Гаус\n";
  CalculateFunc(points, GaussFormula);
  return 0;
}
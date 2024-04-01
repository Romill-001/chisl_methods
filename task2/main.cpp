#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace constans {
const int STEPS = 1024;
const float LEFT_BORDER = 0;
const float EPSILON = 1e-6;
const float E = 2.71828182846;
}  // namespace constans

float McLorenFunc(float x, int steps) {
  float result = 0;
  for (int n = 0; n < steps; ++n) {
    result += pow(-1, n) * pow(x, 2 * n + 1) / (tgamma(n + 1) * (2 * n + 1));
  }
  return (2 / sqrt(M_PI)) * result;
}

float func(float t) { return (2 / sqrt(M_PI)) * pow(constans::E, -(t * t)); }

float leftRectangles(float (*func)(float), const float &a, float b,
                      int steps) {
  float result = 0.0;
  float h = (b - a) / steps;
  float x_i = 0.0;
  for (int i = 0; i < steps; i++) {
    x_i = a + h * i;
    result += h * func(x_i);
  }
  return result;
}

float rightRectangles(float (*func)(float), const float &a, float b,
                       int steps) {
  float result = 0.0;
  float h = (b - a) / steps;
  float x_i_1 = 0.0;
  for (int i = 1; i <= steps; i++) {
    x_i_1 = a + h * i;
    result += h * func(x_i_1);
  }
  return result;
}

float middleRectangles(float (*func)(float), const float &a, float b,
                        int steps) {
  float result = 0.0;
  float h = (b - a) / steps;
  float x_i = 0.0;
  float x_i_1 = 0.0;
  for (int i = 1; i <= steps; i++) {
    x_i = a + h * (i - 1);
    x_i_1 = a + h * i;
    result += h * func((x_i + x_i_1) / 2);
  }
  return result;
}

float trapezeFormula(float (*func)(float), const float &a, float b,
                      int steps) {
  float result = func(a) + func(b);
  float h = (b - a) / steps;
  float x_i_1 = 0.0;
  for (int i = 1; i <= steps; i++) {
    x_i_1 = a + h * i;
    result += 2 * func(x_i_1);
  }
  result *= h / 2;
  return result;
}

float SypmsonsFormula(float (*func)(float), const float &a, float b,
                       int steps) {
  float h = (b - a) / steps;
    float result = 0;
    float x = 0;
    for (int i = 0; i < steps; i++)
    {
        result += (func(x) + 4 * func(x + h / 2) + func(x + h)) * h / 6;
        x += h;
    }
    return result;
}

float GaussFormula(float (*func)(float), const float &a, float b,
                       int steps) {
    float h = (b - a) / steps;
    float ad1 = (1 - 1.0 / sqrt(3)) * h / 2;
    float ad2 = (1 + 1.0 / sqrt(3)) * h / 2;
    float result = 0;
    float x = 0;
    for (int i = 0; i < steps; i++)
    {
        result += (func(x + ad1) + func(x + ad2)) * h / 2;
        x += h;
    }
    return result;
}

void CalculateFunc(vector<float> points,
                   float (*function)(float (*func)(float), const float &,
                                      float, int)) {
  for (auto point : points) {
    int i = 1;
    float last_j = 0.0;
    float j = 0.0;
    do {
      i *= 2;
      last_j = j;
      j = function(func, constans::LEFT_BORDER, point, i);
    } while (abs(last_j - j) > constans::EPSILON && i < constans::STEPS);

    float difference = abs(McLorenFunc(point, 11) - j);

    printf(
        "x_i = %.1lf | J_o = %.6lf | J_n = %.6lf | |J_o - J_n| = %.6lf | N "
        "= %d\n",
        point, McLorenFunc(point, 11), j, difference, i);
  }
}


int main() {
  vector<float> points = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0,
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
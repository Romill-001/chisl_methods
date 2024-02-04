#include <iostream>
#include <math.h>
#include <vector>

float calc(float x) {
  int n = 0;
  float node_0 = x;
  float ans = x;
  while (fabs(node_0) >= 1e-6) {
    float q = (-1)*(((2*n + 1)*x*x)/(2*n*n + 5*n + 3));
    node_0 *= q;
    ans += node_0;
    n++;
  }
  return (2/sqrt(M_PI))*ans;
}

float lagrange(std::vector<float> x, std::vector<float> y, int n, float _x)
{
  float result = 0.0;
  for (int i = 0; i < n; i++)
  {
    float P = 1.0;
    for (int j = 0; j < n; j++)
      if (j != i)
        P *= ((_x - x[j]) / (x[i] - x[j]));
    result = result +  P  * y[i];
  }  
  return result;
}
void first_task(std::vector<float>& points, std::vector<float>& summs) {
    std::cout << "1 task---------------------------------------" << '\n';
    for (float i = 0; i <= 2; i += 0.4) {
      points.push_back(i);
      summs.push_back(calc(i));
      printf("%.8f f(%.1f)\n",calc(i), i);
      
  }
}
void find_row(std::vector<float>& points, std::vector<float>& summs, float n) {
    for (float i = 0; i <= 2; i += 2.0 / (n - 1)) {
      points.push_back(i);
      summs.push_back(calc(i));
  }
}
void sec_task(std::vector<float> points, std::vector<float> summs) {
    std::cout << "2 task---------------------------------------" << '\n';
    for (float i = 0; i <= 2; i += 0.2) {
        printf("%.8f f(%.1f)\n",lagrange(points, summs, 6, i), i);
    }
}
void third_task(std::vector<float> points, std::vector<float> summs) {
    std::cout << "3 task---------------------------------------" << '\n';
    float max = 0;
    for (float i = 0; i <= 2; i += 0.2) {
        //printf("Значениe в точке %.1lf: Ln(%.1lf) = %.8lf, F(%.1lf) = %.8lf, Разница: |Ln(%.1lf) - F(%.1lf)| = %.8lf\n",i, i ,lagrange(points, summs, 6, i), i, calc(i), i,i,fabs(lagrange(points, summs, 6, i)- calc(i)));
        printf("%.8lf\n", fabs(lagrange(points, summs, 6, i)- calc(i)));
        if (fabs(lagrange(points, summs, 6, i)- calc(i)) > max) {
          max = fabs(lagrange(points, summs, 6, i) - calc(i));
        }
    }
    printf("\nmax is %.8f\n", max);
}
void fourth_task() {
    std::cout << "4 task---------------------------------------" << '\n';
    for (int n = 6; n < 60; n++) {
      std::vector<float> points;
      std::vector<float> summs;
      find_row(points, summs, n);
      float max_1 = 0;
      for (float i = 0; i <= 2; i += 0.2) {
          if (fabs(lagrange(points, summs, n, i) - calc(i)) > max_1) {
              max_1 = fabs(lagrange(points, summs, n, i) - calc(i));
          }
      }
      printf("%2d %.8lf\n",n, max_1);
  }
}
int main() {
  setlocale(LC_ALL, "Russian");
  std::vector<float> points;
  std::vector<float> summs;
  first_task(points, summs);
  sec_task(points, summs);
  third_task(points,summs);
  fourth_task();
  return 0;
}
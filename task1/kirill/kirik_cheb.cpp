#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

double calc(double x) {
  int n = 1;
  float node_0 = (-1)*((x*x)/4);
  float ans = (-1)*((x*x)/4);
  while (fabs(node_0) >= 1e-6) {
    float q = (-1)*((n*x*x)/(4*n*n*n + 10*n*n + 8*n + 2));
    node_0 *= q;
    ans += node_0;
    n++;
  }
  return ans;
}

double lagrange(std::vector<double> x, std::vector<double> y, int n, double _x)
{
  double result = 0.0;
  for (int i = 0; i < n; i++)
  {
    double P = 1.0;
    for (int j = 0; j < n; j++)
      if (j != i)
        P *= ((_x - x[j]) / (x[i] - x[j]));
    result = result +  P  * y[i];
  }  
  return result;
}
void first_task(std::vector<double>& points, std::vector<double>& summs) {
    std::cout << "1 task---------------------------------------" << '\n';
    for (auto i : points) {
      printf("%.6f\n", calc(i));
  }
}
void find_row(std::vector<double>& points, std::vector<double>& summs, int n) {
    for (double i = 1; i <= n; i++) {
      double tmp = 2.2 + 1.8*cos(((2*i - 1)/(2*n))*M_PI);
      points.push_back(tmp);
      summs.push_back(calc(tmp));
    }
}
void sec_task(std::vector<double> points, std::vector<double> summs) {
    std::cout << "2 task---------------------------------------" << '\n';
    for (auto i : points) {
        printf("%.8f\n",lagrange(points, summs, 6, i));
    }
}
void third_task(std::vector<double> points,std::vector<double> summs) {
    std::cout << "3 task---------------------------------------" << '\n';
    std::vector<double> points_1;
    std::vector<double> summs_1;
    find_row(points_1, summs_1, 12);
    double max = 0;
      for (double i = 0; i < 12; i++) {
        //printf("Значениe в точке %.1lf: Ln(%.1lf) = %.8lf, F(%.1lf) = %.8lf, Разница: |Ln(%.1lf) - F(%.1lf)| = %.8lf\n",i, i ,lagrange(points, summs, 6, points_1[i]), i, summs_1[i], i,i,fabs(lagrange(points, summs, 6, points_1[i])- summs_1[i]));
        printf("%.8lf\n", fabs(lagrange(points, summs, 6, points_1[i]) - summs_1[i]));
        if (fabs(lagrange(points, summs, 6, points_1[i]) - summs_1[i]) > max) {
            max = fabs(lagrange(points, summs, 6, points_1[i]) - summs_1[i]);
        }
      }
    //printf("\nmax is %.8f\n", max);
}
void fourth_task() {
    std::cout << "4 task---------------------------------------" << '\n';
    for (int n = 6; n < 27; n++) {
      std::vector<double> points;
      std::vector<double> summs;
      find_row(points, summs, n);
      std::vector<double> points_1;
      std::vector<double> summs_1;
      find_row(points_1, summs_1, 12);
      double max_1 = 0;
        for (double i = 0; i < 12; i++) {
          if (fabs(lagrange(points, summs, n, points_1[i]) - summs_1[i]) > max_1) {
              max_1 = fabs(lagrange(points, summs, n, points_1[i]) - summs_1[i]);
          }
        }
      printf("%d %.8lf\n",n, max_1);
    }
}
int main() {
  std::vector<double> points_1;
  std::vector<double> summs_1;
  find_row(points_1,summs_1, 6);
  //first_task(points_1, summs_1);
  std::vector<double> points_2;
  std::vector<double> summs_2;
  find_row(points_2,summs_2, 12);
  //sort(summs_2.begin(), summs_2.end());
  //for (auto i : summs_2) printf("%.8lf\n", i);
  sec_task(points_2, summs_2);
  //third_task(points_2,summs_2);
  //fourth_task();
  return 0;
}
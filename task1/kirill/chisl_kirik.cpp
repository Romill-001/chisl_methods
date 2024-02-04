#include <iostream>
#include <math.h>
#include <vector>
//считаем значение ряда в точке 
float calc(float x) {
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
//функция для разбиения по Лагранжу
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
void first_task(std::vector<float>& points, std::vector<float>& summs) { // табулируем ряд
    std::cout << "1 task---------------------------------------" << '\n';
    for (float i = 0.4; i <= 4; i += 3.6/5) { //берём 5 узлов из отрезка
      points.push_back(i); //закидываем значения в точках и сами точки в массивы 
      summs.push_back(calc(i));
      printf("%.8lf\n",calc(i));
      
  }
}
//тот же самый функционал что и в первом задании но нужно для 4-го
void find_row(std::vector<float>& points, std::vector<float>& summs, float n) {
    for (float i = 0.4; i <= 4; i += 3.6/(n-1)) {
      points.push_back(i);
      summs.push_back(calc(i));
  }
}
void sec_task(std::vector<float> points, std::vector<float> summs) { // считаем значения для разбиения по Лагранжу 
    std::cout << "2 task---------------------------------------" << '\n';
    for (float i = 0.4; i <= 4; i += 3.6/10) { //считаем Лагранжа при количестве узлов = 6
        printf("%.8lf\n", lagrange(points, summs, 6, i));
        //printf("%.1lf\n", i);
    }
}
void third_task(std::vector<float> points, std::vector<float> summs) { // считаем максимальную разность между значениями табулированного ряда и значениями Лагранжа
    std::cout << "3 task---------------------------------------" << '\n';
    float max = 0;
    for (float i = 0.4; i <= 4; i += 3.6/10) { //
        //printf("Значениe в точке %.1lf: Ln(%.1lf) = %lf, F(%.1lf) = %lf, Разница: Ln(%.1lf) - F(%.1lf) = %lf\n",i, i ,lagrange(points, summs, 6, i), i, calc(i), i,i,fabs(lagrange(points, summs, 6, i)- calc(i)));
        printf("%.8lf\n", fabs(lagrange(points, summs, 6, i)- calc(i)));
        if (fabs(lagrange(points, summs, 6, i)- calc(i)) > max) {
          max = fabs(lagrange(points, summs, 6, i) - calc(i));
        }
    }
    //printf("\nmax is %.8lf\n", max);
}
void fourth_task() { // 
    std::cout << "4 task---------------------------------------" << '\n';
    for (int n = 6; n < 27; n++) { //увеличиваем количество узлов которые мы берём
      std::vector<float> points;
      std::vector<float> summs;
      find_row(points, summs, n);
      float max_1 = 0;
      for (float i = 0.4; i <= 4; i += 3.6/10) {
          if (fabs(lagrange(points, summs, n, i) - calc(i)) > max_1) {
              max_1 = fabs(lagrange(points, summs, n, i) - calc(i));
          }
      }
      if (max_1 < 1000) printf("%.8lf\n", max_1);
    }
}
int main() {
  setlocale(LC_ALL, "Russian");
  /* std::vector<float> points;
  std::vector<float> summs;
  first_task(points, summs);
  sec_task(points, summs);
  third_task(points,summs); */
  fourth_task();
  return 0;
}
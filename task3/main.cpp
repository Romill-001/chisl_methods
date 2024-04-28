#include "header.hpp"

using namespace std;

int main() {

    int n = 10.0;
    double h = 1.0 / n;

    std::vector<double> alpha(n + 1), betta(n + 1), y_i_p(n + 1), y_i_s(n + 1), y_i_r(n + 1);
    vector<vector<double>> A = create_matrix(n);
    printf("Прогонка\n");
    progonka_method(A, alpha, betta, y_i_p, n);
    printf("Зейдель\n");
    Seidel_method(1000, n, y_i_s, A);
    //printf("Нижняя релаксация\n");
    //relax_bottom(1000, n, y_i_r);
    return 0;
}

#include "header.hpp"

using namespace std;

int main() {

    int n = 10.0;

    std::vector<double> alpha(n + 1), betta(n + 1), y_i_p(n + 1), y_i_s(n + 1), y_i_r(n + 1), y_i_sp(n + 1), b(n);
    vector<vector<double>> A = create_matrix(n);
    b = func_vec(n);
    printf("Прогонка\n");
    progonka_method(A, alpha, betta, y_i_p, n, b);
    printf("Зейдель\n");
    Seidel_method(10000, n, y_i_s, A, b);
    printf("Нижняя релаксация\n");
    relax_bottom(10000, n, y_i_r, A, b);
    printf("Наискорейший спуск\n");
    spusk(10000, n, y_i_sp, A, b);
    return 0;
}

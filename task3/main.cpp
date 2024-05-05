#include "header.hpp"

using namespace std;

int main() {

    int n = 10.0;

    std::vector<double> y_i_p(n + 1), y_i_s(n + 1), y_i_r(n + 1), y_i_sp(n + 1), b(n);
    vector<vector<double>> A = create_matrix(n);
    b = func_vec(n);
    printf("Прогонка\n");
    progonka_method(A, y_i_p, n, b);
    printf("Зейдель\n");
    int k_s = Seidel_method(n, y_i_s, A, b);
    printf("Нижняя релаксация\n");
    int k_r = relax_bottom(n, y_i_r, A, b);
    printf("Наискорейший спуск\n");
    int k_dec = spusk(n, y_i_sp, A, b);
    printf("Прогонка - Зейдель\n");
    m_print(k_s, y_i_p, y_i_s);
    printf("Прогонка - Нижн релаксация\n");
    m_print(k_r, y_i_p, y_i_r);
    printf("Прогонка - Спуск\n");
    m_print(k_dec, y_i_p, y_i_sp);
    return 0;
}

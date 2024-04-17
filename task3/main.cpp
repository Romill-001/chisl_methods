#include "OddsAndFuncs.hpp"

using namespace std;
using namespace odds;

int main() {

    double h = 1.0 / n;
    y_i[0] = 0;
    y_i[n] = 0;

    for (int i = 0; i <= n; i++) {
        a_i[i] = p_x(i * h);
        q_i[i] = q_x(i * h);
        u_i[i] = u_x(i * h);
        f_i[i] = f_x(i * h) * h * h;
    }

    for (int i = 0; i < n; i++) {
        a[i] = -a_i[i];
        c[i] = a_i[i] + a[i + 1] + h * h * q_i[i];
        b[i] = -a_i[i + 1];
    }

    alpha[1] = b[0] / c[0];
    betta[1] = f_i[0] / c[0];
    
    for (int i = 1; i < n; i++) {
        alpha[i + 1] = b[i] / (c[i] - alpha[i] * a[i]);
        betta[i + 1] = (f_i[i] + a[i] * betta[i]) / (c[i] - alpha[i] * a[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        y_i[i] = alpha[i + 1] * y_i[i + 1] + betta[i + 1];
    }

    for (int i = 0; i <= n; i++) {
        printf("ih = %4.2lf | y_i = %9.6lf | u(ih) = %8.6lf | |y_i - u(ih)| = %8.6lf\n", i * h, y_i[i], u_i[i], fabs(y_i[i]- u_i[i]));
    }
    return 0;
}

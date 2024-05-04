#include <iostream>
#include <vector>
#include <cmath>

// Функция, описывающая систему дифференциальных уравнений второго порядка
std::vector<double> f(double x, const std::vector<double>& y) {
    double y1 = y[0];
    double y2 = y[1];
    std::vector<double> dy(2);
    // Ваша система уравнений
    // Замените выражения в dy[0] и dy[1] на соответствующие уравнения
    dy[0] = /* уравнение для y' */;
    dy[1] = /* уравнение для z' */;
    return dy;
}

// Функция умножения вектора на скаляр
std::vector<double> multiply(double scalar, const std::vector<double>& vec) {
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = scalar * vec[i];
    }
    return result;
}

// Функция сложения двух векторов
std::vector<double> add(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    std::vector<double> result(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

// Метод Рунге-Кутты четвертого порядка
std::vector<std::vector<double>> runge_kutta_4(double a, double b, const std::vector<double>& y0, double h) {
    int n = static_cast<int>((b - a) / h) + 1; // Количество шагов
    std::vector<std::vector<double>> result(n, std::vector<double>(2)); // Матрица для хранения результатов
    double x = a;
    std::vector<double> y = y0; // Инициализация начальных значений

    for (int i = 0; i < n; ++i) {
        // Запись текущих значений y в результат
        result[i][0] = y[0];
        result[i][1] = y[1];

        // Вычисление коэффициентов метода Рунге-Кутты
        std::vector<double> k1 = f(x, y);
        std::vector<double> k2 = f(x + h / 2, add(y, multiply(h / 2, k1)));
        std::vector<double> k3 = f(x + h / 2, add(y, multiply(h / 2, k2)));
        std::vector<double> k4 = f(x + h, add(y, multiply(h, k3)));

        // Обновление значений y по методу Рунге-Кутты
        for (int j = 0; j < 2; ++j) {
            y[j] += h / 6 * (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]);
        }
        x += h; // Переход к следующему шагу
    }

    return result;
}

int main() {
    double a = 0.0; // Начальное значение x
    double b = 5.0; // Конечное значение x
    double h = 0.1; // Шаг интегрирования
    std::vector<double> y0 = {1.0, 0.0}; // Начальные условия

    // Получение решения методом Рунге-Кутты
    std::vector<std::vector<double>> solution = runge_kutta_4(a, b, y0, h);

    // Вывод результатов
    for (int i = 0; i < solution.size(); ++i) {
        printf("x = %5.2lf | y = %9.6lf | z = %9.6lf\n", a + i * h, solution[i][0], solution[i][1]);
    }

    return 0;
}

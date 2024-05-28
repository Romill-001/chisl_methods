import numpy as np
import matplotlib.pyplot as plt

def f(y1, y2):
    dy1 = -y2 + y1 * (y1**2 + y2**2 - 1)
    dy2 = y1 + y2 * (y1**2 + y2**2 - 1)
    return dy1, dy2

def rk4_step(y1, y2, h):
    k1_y1, k1_y2 = f(y1, y2)
    k2_y1, k2_y2 = f(y1 + 0.5 * h * k1_y1, y2 + 0.5 * h * k1_y2)
    k3_y1, k3_y2 = f(y1 + 0.5 * h * k2_y1, y2 + 0.5 * h * k2_y2)
    k4_y1, k4_y2 = f(y1 + h * k3_y1, y2 + h * k3_y2)
    y1_new = y1 + (h / 6) * (k1_y1 + 2 * k2_y1 + 2 * k3_y1 + k4_y1)
    y2_new = y2 + (h / 6) * (k1_y2 + 2 * k2_y2 + 2 * k3_y2 + k4_y2)
    return y1_new, y2_new

def exact_solution(x):
    y1_exact = np.cos(x) / (np.sqrt(1 + 2.71828182846**(2*x)))
    y2_exact = np.sin(x) / (np.sqrt(1 + 2.71828182846**(2*x)))
    return y1_exact, y2_exact

def max_error(y_num, y_exact):
    return np.max(np.abs(y_num - y_exact))

def solve_system_e(h_values):
    max_errors = []
    for h in h_values:
        t_values = np.arange(t0, t_end, h)
        y1_values = np.zeros_like(t_values)
        y2_values = np.zeros_like(t_values)
        y1 = y1_0
        y2 = y2_0
        for i, t in enumerate(t_values):
            y1_values[i] = y1
            y2_values[i] = y2
            y1, y2 = rk4_step(y1, y2, h)
        y1_exact, y2_exact = exact_solution(t_values)
        max_errors.append(max(max_error(y1_values, y1_exact), max_error(y2_values, y2_exact)))
    return max_errors

def solve_system_eh4(h_values):
    max_errors = []
    for h in h_values:
        t_values = np.arange(t0, t_end, h)
        y1_values = np.zeros_like(t_values)
        y2_values = np.zeros_like(t_values)
        y1 = y1_0
        y2 = y2_0
        for i, t in enumerate(t_values):
            y1_values[i] = y1
            y2_values[i] = y2
            y1, y2 = rk4_step(y1, y2, h)
        y1_exact, y2_exact = exact_solution(t_values)
        max_errors.append(max(max_error(y1_values, y1_exact), max_error(y2_values, y2_exact))/h**4)
    return max_errors

y1_0 = 1 / np.sqrt(2) 
y2_0 = 0  
t0 = 0
t_end = 5
h_values = np.linspace(0.001, 0.1, 100) 


max_errors_e = solve_system_e(h_values)
max_errors_eh4 = solve_system_eh4(h_values)

plt.figure(figsize=(16, 7))

plt.subplot(1, 2, 1)
plt.plot(h_values, max_errors_e)
plt.xlabel('Шаг интегрирования, h')
plt.ylabel('Максимальная погрешность')
plt.title('Зависимость максимальной погрешности e от выбранного шага h')
plt.grid(True)
plt.subplot(1, 2, 2)
plt.plot(h_values, max_errors_eh4)
plt.xlabel('Шаг интегрирования, h')
plt.ylabel('Максимальная погрешность')
plt.title('Зависимость максимальной погрешности e/h^4 от выбранного шага h')
plt.grid(True)
plt.savefig('plot_max_err.png')
plt.show()


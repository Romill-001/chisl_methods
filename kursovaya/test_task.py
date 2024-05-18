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

def exact_solution(x, e):
    y1_exact = np.cos(x) / (np.sqrt(1 + e**(2*x)))
    y2_exact = np.sin(x) / (np.sqrt(1 + e**(2*x)))
    return y1_exact, y2_exact

y1_0 = 1 / np.sqrt(2)  
y2_0 = 1 / np.sqrt(2)  
e = 0
t0 = 0
t_end = 5
h = 0.01


t_values = np.arange(t0, t_end, h)
y1_values = np.zeros_like(t_values)
y2_values = np.zeros_like(t_values)

y1 = y1_0
y2 = y2_0
for i, t in enumerate(t_values):
    y1_values[i] = y1
    y2_values[i] = y2
    y1, y2 = rk4_step(y1, y2, h)

y1_exact, y2_exact = exact_solution(t_values, e)

plt.plot(t_values, y1_values, label='Численное решение y1')
plt.plot(t_values, y2_values, label='Численное решение y2')
plt.plot(t_values, y1_exact, label='Точное решение y1', linestyle='--')
plt.plot(t_values, y2_exact, label='Точное решение y2', linestyle='--')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Решение системы методом Рунге-Кутты 4-го порядка')
plt.legend()
plt.grid(True)
plt.savefig('plot_test_task.png')
plt.show()

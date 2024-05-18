import numpy as np
import matplotlib.pyplot as plt

def f(u, M, m):
    u1, u2, u3, u4 = u
    R1 = ((u1 + m)**2 + u3**2)**(3/2)
    R2 = ((u1 - M)**2 + u3**2)**(3/2)
    f1 = u2
    f2 = u1 + 2*u4 - M*(u1 - m)/R1 - m*(u1 - M)/R2
    f3 = u4
    f4 = u3 - 2*u2 - M*u3/R1 - m*u3/R2
    return np.array([f1, f2, f3, f4])

def rk4_step(u, h, M, m):
    k1 = h * f(u, M, m)
    k2 = h * f(u + 0.5 * k1, M, m)
    k3 = h * f(u + 0.5 * k2, M, m)
    k4 = h * f(u + k3, M, m)
    return u + (k1 + 2*k2 + 2*k3 + k4) / 6

u0 = np.array([0.994, 0, 0, -2.031732629557337])
m = 0.012277471
M = 1 - m
t0 = 0
t_end = 20
h = 0.01  

t_values = np.arange(t0, t_end, h)
u_values = np.zeros((len(t_values), len(u0)))

u = u0
for i, t in enumerate(t_values):
    u_values[i] = u
    u = rk4_step(u, h, M, m)

x_values = u_values[:, 0]
y_values = u_values[:, 2]

plt.plot(x_values, y_values)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Решение системы методом Рунге-Кутты 4-го порядка')
plt.grid(True)
plt.savefig('plot_main_task.png')
plt.show()

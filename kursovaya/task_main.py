import numpy as np
import matplotlib.pyplot as plt

def aren(t, u):
    x, y, vx, vy = u
    m = 0.012277471; M = 1 - m
    r1 = ((x+m)**2+y**2)**(1.5);
    r2 = ((x-M)**2+y**2)**(1.5)
    return np.array([vx, vy,x+2*vy-M*(x+m)/r1-m*(x-M)/r2,y-2*vx-M* y /r1-m* y /r2])

aren_init = np.array([0.994, 0, 0, -2.031732629557337])
aren_tmax = 11.124340337

def rk4(f, tau, t, u):
    k1 = f(t, u)
    k2 = f(t + tau/2, u + tau/2*k1)
    k3 = f(t + tau/2, u + tau/2*k2)
    k4 = f(t + tau , u + tau *k3)
    return u + tau * (k1 + 2*k2 + 2*k3 + k4) / 6

def adaptive_stepsize(f, y0, tmax, method, tol, tau=0.01):
    t = 0; u = y0
    T = [0]; Y = [y0]
    failed = 0 # Число неудачных шагов
    while t < tmax:
        if t + tau > tmax: tau = tmax - t
        u1 = method(f, tau, t, u) # Целый шаг
        u2 = method(f, tau/2, t, u)
        u2 = method(f, tau/2, t+tau/2, u2) # Два полушага
        err = np.linalg.norm(u1-u2)/(1-2**-4) # Правило Рунге
        fac = (tol/err)**(1 / (4+1)) # Подстраиваем tau
        taunew = tau * min(2, max(0.25, 0.8 * fac))
        if err < tol: # Ошибка мала, принимаем шаг
            t += tau; u = u1
            T.append(t); Y.append(u)
        else: # Если ошибка велика, повторяем шаг с новым tau
            failed += 1
        tau = taunew
    return np.array(T), np.array(Y)

T, Y = adaptive_stepsize(aren, aren_init, aren_tmax, rk4, 1e-6)
x_values = Y[:, 0]
y_values = Y[:, 1]

# Построение орбиты
plt.figure(figsize=(8, 6))
plt.plot(x_values, y_values, label='Орбита планетоида', color='blue')
plt.scatter([0], [0], color='red', label='Земля')
plt.scatter([1], [0], color='green', label='Луна')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Орбита планетоида вокруг Земли - орбита Арентострофа')
plt.legend()
plt.grid(True)
plt.axis('equal')
plt.savefig('plot_main_task.png')
plt.show()



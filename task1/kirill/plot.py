import matplotlib.pyplot as plt

#Погрешности по 11 точкам
points_lag = [0.4, 0.8, 1.1, 1.5, 1.8, 2.2, 2.6, 2.9, 3.3, 3.6, 4.0]
val_lag = [0.00000000, 0.00005813, 0.00000000, 0.00003216, 0.00000000, 0.00003183, 0.00000000, 0.00005627, 0.0000000, 0.00020051, 0.0000000]
points_cheb = [0.4, 0.8, 1.1, 1.5, 1.8, 2.2, 2.6, 2.9, 3.3, 3.6, 4.0]
val_cheb = [0.00007861, 0.00007572, 0.00007277, 0.00006754, 0.00006096, 0.00005288, 0.00004418, 0.00003564, 0.00002770, 0.00002125, 0.00001668]
plt.figure(figsize=(15, 15))
plt.plot(points_lag, val_lag, label = "Погрешности по равнораспределённым узлам", linewidth=3)
plt.plot(points_cheb, val_cheb, label = "Погрешности по узлам Чебышева", linewidth=3)
plt.legend(fontsize=20)
plt.tick_params(axis='x', labelsize=22)
plt.tick_params(axis='y', labelsize=22)
plt.savefig('diff_lag_tab.png')

points_lag = [0.4, 0.8, 1.1, 1.5, 1.8, 2.2, 2.6, 2.9, 3.3, 3.6, 4.0]
val_lag = [0.00000000, 0.00005813, 0.00000000, 0.00003216, 0.00000000, 0.00003183, 0.00000000, 0.00005627, 0.0000000, 0.00020051, 0.0000000]
plt.figure(figsize=(15, 15))
plt.plot(points_lag, val_lag, label = "Погрешности по равнораспределённым узлам", linewidth=3)
plt.legend(fontsize=20)
plt.tick_params(axis='x', labelsize=22)
plt.tick_params(axis='y', labelsize=22)
plt.savefig('diff_just_lag.png')

#Погрешности от узлов
points = [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]
val = [0.00020051, 0.00004633, 0.00000155, 0.00000024, 0.00003958, 0.00000000, 0.00000072, 0.00000095, 0.00112963, 0.00000083, 0.00000285, 0.00000556,
0.00572538, 0.06039476, 0.00000584, 0.00232744, 0.11327314, 0.07564211, 0.32855654, 0.24901152]
points_c = [x for x in range (6,27)]
val_c = [0.00007861, 0.00002385, 0.00000153, 0.00000053, 0.00000033, 0.00000032, 0.00000000, 0.00000049, 0.00000057, 0.00000031, 0.00000048, 0.00000034,
0.00000069, 0.00000044, 0.00000026, 0.00000033, 0.00000035, 0.00000028, 0.00000018, 0.00000047, 0.00000045]
plt.figure(figsize=(15, 15))
plt.plot(points, val, label = "Погрешность в зависимости от кол-ва узлов", linewidth=3)
plt.plot(points_c, val_c, label = "Погрешность в зависимости от кол-ва узлов Чебышев", linewidth=3)
plt.legend(fontsize=20)
plt.tick_params(axis='x', labelsize=22)
plt.tick_params(axis='y', labelsize=22)
plt.savefig('differs.png')

points = [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]
val = [0.00020051, 0.00004633, 0.00000155, 0.00000024, 0.00003958, 0.00000000, 0.00000072, 0.00000095, 0.00112963, 0.00000083, 0.00000285, 0.00000556,
0.00572538, 0.06039476, 0.00000584, 0.00232744, 0.11327314, 0.07564211, 0.32855654, 0.24901152]
plt.figure(figsize=(15, 15))
plt.plot(points, val, label = "Погрешность в зависимости от кол-ва узлов", linewidth=3)
plt.legend(fontsize=20)
plt.tick_params(axis='x', labelsize=22)
plt.tick_params(axis='y', labelsize=22)
plt.savefig('differs_not_c.png')

#Табуляция
points_tab = [0.4,1.1,1.8,2.6,3.3,4.0]
val_tab = [-0.03973429, -0.29765847, -0.73558891, -1.25076473, -1.73436868, -2.10449171]
plt.figure(figsize=(15, 15))
plt.plot(points_tab, val_tab, label = "Табуляция по 6 узлам", linewidth=3)
plt.legend(fontsize=25)
plt.tick_params(axis='x', labelsize=22)
plt.tick_params(axis='y', labelsize=22)
plt.savefig('tab_6_nodes.png')

#Лагранж
points_lag_2 = [0.4, 0.8, 1.1, 1.5, 1.8, 2.2, 2.6, 2.9, 3.3, 3.6, 4.0]
val_lag_2 = [-0.03973429, -0.14091089, -0.29765847, -0.50001723, -0.73558891, -0.99056667, -1.25076473, -1.50264931, -1.73436880, -1.93678188, -2.10449147]
plt.figure(figsize=(15, 15))
plt.plot(points_lag_2, val_lag_2, label = "Полином Лагранжа", linewidth=3)
plt.legend(fontsize=25)
plt.tick_params(axis='x', labelsize=22)
plt.tick_params(axis='y', labelsize=22)
plt.savefig('tab_11_nodes.png')
import matplotlib.pyplot as plt
import numpy as np


# データセット1
#x_values1 = np.array([1.772,1.75,1.79,1.73,1.769,1.807,1.75,1.785,1.821])
x_values1 = np.array([39,42,43,45,46,47,49,50,51])
y_values1 = np.array([295.074,313.152,330.240,328.455,349.738,366.13,365.05,308.08,401.37])
x_error1 = np.array([0,0,0,0,0,0,0,0,0])
y_error1 = np.array([0.195,0.294,0.215,0.270,0.322,0.517,0.588,0.500,0.510])

# データセット2
y_values2 = np.array([290.446,309.83,329.222,326.327,349.488,364.983,362.577,385.155,400.067])
y_error2 = np.array([3.018,0.763,0.273,3.216,0.541,0.295,1.494,0.714,0.359])

# データセット2
y_values3 = np.array([307.908,311.767,328.384,324.262,347.541,363.430,319.375,367.287,397.353])
y_error3 = np.array([0.245,0.586,0.302,1.193,0.634,0.349,0.910,0.657,0.338])

y_values4 = np.array([295.408,314.018,330.386,329.167,350.255,366.045,365.833,385.658,401.626])
y_error4 = np.array([0.103,0.125,0.115,0.170,0.123,0.110,0.168,0.150,0.133])


y_values21 = y_values2 - y_values1
y_values31 = y_values3 - y_values1
y_values41 = y_values4 - y_values1

y_error21 = y_error2 + y_error1
y_error31 = y_error3 + y_error1
y_error41 = y_error4 + y_error1


# スキャッタープロットとエラーバーを描画
plt.errorbar(x_values1, y_values21, xerr=x_error1, yerr=y_error21, fmt='o',markerfacecolor='white',color='red',capsize=5)


plt.errorbar(x_values1, y_values31, xerr=x_error1, yerr=y_error31, fmt='s', capsize=5, color='black',markerfacecolor='white')

plt.errorbar(x_values1, y_values41, xerr=x_error1, yerr=y_error41, fmt='s', capsize=5, color='blue')


plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')


#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

#plt.xticks([42,43,44,45,46,47,48])
#plt.yticks([-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10])
#
#
#plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

#plt.xlim(20,47.3)
plt.ylim(-20,20)


# グリッドを表示
#plt.grid(True)

# グラフを表示
plt.show()

#plt.savefig('./plot_s2p_cr_final.svg',format='svg')

import matplotlib.pyplot as plt
import numpy as np


# データセット1
#x_values1 = np.array([1.772,1.75,1.79,1.73,1.769,1.807,1.75,1.785,1.821])
x_values1 = np.array([39,42,43,45,46,47,49,50,51])
y_values1 = np.array([0,0,0,0,0,0,0,0,0])
x_error1 = np.array([0,0,0,0,0,0,0,0,0])
y_error1 = np.array([0.195,0.294,0.215,0.270,0.322,0.517,0.588,0.500,0.510])

# データセット2
y_values2 = np.array([2.1,3.3,1.0,2.09,2.065,1.12,2.44,1.652,1.27])
y_error2 = np.array([3.018,0.763,0.273,3.216,0.541,0.295,1.494,0.714,0.359])

# データセット2
y_values3 = np.array([-4.75,1.397,1.876,4.195,2.19,2.711,5.286,2.034,2.016])
y_error3 = np.array([0.245,0.586,0.302,1.193,0.634,0.349,0.910,0.657,0.338])

y_values4 = np.array([-0.361,-0.8879,-0.1546,-0.743,-0.560,0.0608,-0.815,-0.579,-0.286])
y_error4 = np.array([0.103,0.125,0.115,0.170,0.123,0.110,0.168,0.150,0.133])


#y_values21 = y_values2 - y_values1
#y_values31 = y_values3 - y_values1
#y_values41 = y_values4 - y_values1
#
#y_error21 = y_error2 + y_error1
#y_error31 = y_error3 + y_error1
#y_error41 = y_error4 + y_error1


# スキャッタープロットとエラーバーを描画

plt.errorbar(x_values1, y_values1, xerr=x_error1, yerr=y_error1, fmt='s',color='black',capsize=5,markerfacecolor='white')

plt.errorbar(x_values1, y_values2, xerr=x_error1, yerr=y_error2, fmt='o',markerfacecolor='white',color='red',capsize=5)

plt.errorbar(x_values1, y_values3, xerr=x_error1, yerr=y_error3, fmt='D', capsize=5, color='green')

plt.errorbar(x_values1, y_values4, xerr=x_error1, yerr=y_error4, fmt='s', capsize=5, color='blue')


plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')


#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

plt.xticks([39,40,41,42,43,44,45,46,47,48,49,50,51])
#plt.yticks([-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10])
#
#
plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

#plt.xlim(20,47.3)
plt.ylim(-7,7)


# グリッドを表示
#plt.grid(True)

# グラフを表示
#plt.show()

plt.savefig('./plot_be_comp_final.svg',format='svg')

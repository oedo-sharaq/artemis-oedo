import matplotlib.pyplot as plt
import numpy as np

# データセット1
x_values1 = [49, 50,51, 52]
y_values1 = [-2.4,-1.73, 1.65,2.54]
x_error1 = [0,0,0,0]
y_error1 = [1.52, 0.771, 0.462,0.29]

## データセット2
#x_values2 = [52,53,54]
#y_values2 = [2.66,4.02,5.524]
#x_error2 = [0,0,0]
#y_error2 = [0.61,0.025,0.005]

# データセット2
x_values3 = [48, 49, 50, 51,52]
y_values3 = [-2.39,-1.08,0.03,1.48,2.66]
x_error3 = [0,0,0,0,0]
y_error3 = [0.3,0.78,0.51,0.5,0]

fig, ax = plt.subplots()


## スキャッタープロットとエラーバーを描画
#plt.scatter(x_values1, y_values1, label='Data Set 1', color='red')
#plt.errorbar(x_values1, y_values1, xerr=x_error1, yerr=y_error1, fmt='d-', capsize=5, color='red')
#
##plt.scatter(x_values2, y_values2, label='Data Set 2', color='black')
##plt.errorbar(x_values2, y_values2, xerr=x_error2, yerr=y_error2, fmt='s-', capsize=5, color='black')
#
#plt.scatter(x_values3, y_values3, label='Data Set 3', color='black')
#plt.errorbar(x_values3, y_values3, xerr=x_error3, yerr=y_error3, fmt='*:', capsize=5, color='black')


ax.errorbar(x_values1,y_values1,yerr=y_error1, fmt='og')
ax.errorbar(x_values3,y_values3,yerr=y_error3, fmt='sr-.',facecolor='None',edgecolors='red')

ax.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')


#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

plt.xticks([48,49,50,51,52,53,54])
plt.yticks([-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6])


plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

plt.xlim(47.3,55.3)
plt.ylim(-6.5,6.5)


# グリッドを表示
#plt.grid(True)

# グラフを表示
plt.show()

#

import matplotlib.pyplot as plt


# データセット1
x_values1 = [20,22,24,26]
y_values1 = [3.621,1.823,1.964,1.379]
x_error1 = [0,0,0,0]
y_error1 = [0.0,0.02,0.22,0.99]

x_values2 = [21,23,25,27]
y_values2 = [1.332,1.342,1.0009,1.353]
x_error2 = [0,0,0,0]
y_error2 = [0.0,0.065,0.596,1.08]

#x_values1 = [20,21,22,23,24,25,26,27]
#y_values1 = [3.621,1.332,1.823,1.342,1.964,1.0009,1.379,1.353]
#x_error1 = [0,0,0,0,0,0,0,0]
#y_error1 = [0.0,0.0,0.02,0.065,0.22,0.596,0.99,1.08]


## データセット2
#x_values2 = [46]
#y_values2 = [1.379]
#x_error2 = [0]
#y_error2 = [0.99]


# スキャッタープロットとエラーバーを描画
plt.scatter(x_values1, y_values1, label='Data Set 1', color='black')
plt.errorbar(x_values1, y_values1, xerr=x_error1, yerr=y_error1, fmt='o-', capsize=5, color='black')

plt.scatter(x_values2, y_values2, label='Data Set 2', color='red')
plt.errorbar(x_values2, y_values2, xerr=x_error2, yerr=y_error2, fmt='o-', capsize=5, color='black')

#plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')


#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

plt.xticks([20,21,22,23,24,25,26,27])
plt.yticks([0,1,2,3,4])


plt.tick_params(axis='both', which='both', direction='in')


# 凡例を表示
plt.legend()

plt.xlim(19.3,28)
plt.ylim(0,4.3)


# グリッドを表示
#plt.grid(True)

# グラフを表示
#plt.show()

plt.savefig('./plot_delta3.svg',format='svg')




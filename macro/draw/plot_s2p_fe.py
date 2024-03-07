import matplotlib.pyplot as plt


# データセット1
x_values1 = [45, 46, 47,48, 49]
y_values1 = [-2.8, -0.26, 1.24, 3.19, 4.29]
x_error1 = [0,0,0,0,0]
y_error1 = [3.2, 0.6, 0.39,0.39, 0.29]

# データセット2
x_values2 = [48, 49]
y_values2 = [3.11,4.766]
x_error2 = [0,0]
y_error2 = [0.09,0.025]

# データセット2
x_values3 = [45, 46, 47, 48]
y_values3 = [-1.8,-0.050,2.19,3.11]
x_error3 = [0,0,0,0]
y_error3 = [0.2,0.3,0.5,0.09]

# データセット2
x_values4 = [45]
y_values4 = [-1.15]
x_error4 = [0]
y_error4 = [0.016]


# スキャッタープロットとエラーバーを描画
plt.errorbar(x_values1, y_values1,  yerr=y_error1, fmt='o-', capsize=5, color='red',markerfacecolor='red',markersize=7)


plt.errorbar(x_values3, y_values3,  yerr=y_error3, fmt='s-', capsize=5, color='black',markerfacecolor='white',markersize=7)

plt.errorbar(x_values2, y_values2, yerr=y_error2, fmt='s-', capsize=5, color='black',markersize=7)

plt.errorbar(x_values4, y_values4, fmt='*', capsize=5, color='cyan',markersize=10)

plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')

#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

plt.xticks([45,46,47,48,49,])
plt.yticks([-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6])


plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

plt.xlim(44.3,49.3)
plt.ylim(-6.5,6.5)


# グリッドを表示
#plt.grid(True)

# グラフを表示
#plt.show()

#plt.savefig('./plot_s2p_fe_final.svg',format='svg')
plt.savefig('./plot_s2p_fe_20240215.svg',format='svg')

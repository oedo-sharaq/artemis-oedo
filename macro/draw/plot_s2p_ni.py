import matplotlib.pyplot as plt


# データセット1
x_values1 = [49, 50,51, 52]
y_values1 = [-2.4,-1.73, 1.65,2.54]
x_error1 = [0,0,0,0]
y_error1 = [1.52, 0.771, 0.462,0.76]

## データセット2
x_values2 = [52,53,54]
y_values2 = [2.66,4.02,5.524]
x_error2 = [0,0,0]
y_error2 = [0.61,0.025,0.005]

# データセット2
x_values3 = [48, 49, 50, 51,52]
y_values3 = [-2.39,-1.08,0.03,1.48,2.66]
x_error3 = [0,0,0,0,0]
y_error3 = [0.3,0.78,0.51,0.5,0]

x_values4 = [48]
y_values4 = [-1.28]
x_error4 = [0]
y_error4 = [0.04]

# スキャッタープロットとエラーバーを描画
#plt.errorbar(x_values1, y_values1, xerr=x_error1, yerr=y_error1, fmt='o-',markerfacecolor='red',color='red',capsize=10)
#plt.errorbar(x_values1, y_values1, yerr=y_error1, fmt='o-',markerfacecolor='red',color='red',capsize=5, markersize=7)

plt.errorbar(x_values3, y_values3, yerr=y_error3, fmt='s-', capsize=5, color='black',markerfacecolor='white',markersize=7)

#plt.errorbar(x_values2, y_values2, xerr=x_error2, yerr=y_error2, fmt='s-', capsize=8, color='black')
plt.errorbar(x_values2, y_values2, yerr=y_error2, fmt='s-', capsize=5, color='black',markersize=7)

#plt.errorbar(x_values4, y_values4, xerr=x_error4, yerr=y_error4, fmt='d', capsize=12, color='cyan')
plt.errorbar(x_values4, y_values4,  fmt='*', capsize=5, color='cyan',markersize=10)

plt.errorbar(x_values1, y_values1, yerr=y_error1, fmt='o-',markerfacecolor='red',color='red',capsize=5, markersize=7)

plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')


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
#plt.show()

#plt.savefig('./plot_s2p_ni_final_20231221.svg',format='svg')
plt.savefig('./plot_s2p_ni_final_20240215.svg',format='svg')

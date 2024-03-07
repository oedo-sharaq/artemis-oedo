import matplotlib.pyplot as plt


# データセット1
x_values1 = [42,43,44]
y_values1 = [-2.02,0.036, 2.73]
x_error1 = [0,0,0]
y_error1 = [0.72, 0.367, 0.365]

# データセット2
x_values2 = [44,45,46,47]
y_values2 = [2.9,4.78,6.5,10.13]
x_error2 = [0,0,0,0]
y_error2 = [0.05,0.04,0.011,0.005]

# データセット2
x_values3 = [42,43,44]
y_values3 = [-1.48,0.85,2.9]
x_error3 = [0,0,0]
y_error3 = [0.31,0.2,0.05]


# スキャッタープロットとエラーバーを描画
#plt.errorbar(x_values1, y_values1, yerr=y_error1, fmt='o-',markerfacecolor='red',color='red',capsize=5,markersize=7)

plt.errorbar(x_values3, y_values3, yerr=y_error3, fmt='s-', capsize=5, color='black',markerfacecolor='white',markersize=7)

plt.errorbar(x_values2, y_values2, yerr=y_error2, fmt='s-', capsize=5, color='black',markersize=7)

plt.errorbar(x_values1, y_values1, yerr=y_error1, fmt='o-',markerfacecolor='red',color='red',capsize=5,markersize=7)

plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')


#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

plt.xticks([42,43,44,45,46,47,48])
plt.yticks([-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10])


plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

plt.xlim(41.3,47.3)
plt.ylim(-6,11.3)


# グリッドを表示
#plt.grid(True)

# グラフを表示
#plt.show()

#plt.savefig('./plot_s2p_cr_final_20231221.svg',format='svg')
plt.savefig('./plot_s2p_cr_final_20240215.svg',format='svg')

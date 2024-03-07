import matplotlib.pyplot as plt


# データセット1
x_values1 = [39,40,41]
y_values1 = [-3.17,1.57,2.78]
x_error1 = [0,0,0]
y_error1 = [2.287, 0.488, 0.45]

# データセット2
x_values2 = [40,41,42]
y_values2 = [1.510,2.993,4.83589]
x_error2 = [0,0,0]
y_error2 = [0.07,0.028,0.0027]

# データセット2
x_values3 = [39,40]
y_values3 = [-1.060,1.510]
x_error3 = [0,0]
y_error3 = [0.2,0.07]


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

plt.xticks([39,40,41,42])
plt.yticks([-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6])


plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

plt.xlim(38.3,42.3)
plt.ylim(-7,6.5)


# グリッドを表示
#plt.grid(True)

# グラフを表示
#plt.show()

#plt.savefig('./plot_s2p_ti_final.svg',format='svg')
plt.savefig('./plot_s2p_ti_20240215.svg',format='svg')

import matplotlib.pyplot as plt


# データセット1
x_values1 = [24,23,22]
y_values1 = [2.9,3.85,4.83589]
x_error1 = [0,0,0]
y_error1 = [0.05,0.04,0.00027]

# データセット1
x_values2 = [28,27,25]
y_values2 = [-2.39,-1.020,1.640]
x_error2 = [0,0,0]
y_error2 = [0.3,0.67,0.3]


# データセット1
x_values3 = [26]
y_values3 = [-0.26]
x_error3 = [0]
y_error3 = [0.6]

# データセット1
x_values4 = [28]
y_values4 = [-1.28]
x_error4 = [0]
y_error4 = [0.12]

# データセット2
x_values5 = [28,27,26,25,24,23,22]
y_values5 = [-2.73,-0.97,0.12,1.44,2.88,3.87,4.94]
x_error5 = [0,0,0,0,0,0,0]
y_error5 = [0,0,0,0,0,0,0]

# データセット2
x_values6 = [28,27,26,25,24,23,22]
y_values6 = [-1.02,-0.13,0.91,1.85,2.93,3.62,4.49]
x_error6 = [0,0,0,0,0,0,0]
y_error6 = [0,0,0,0,0,0,0]



# スキャッタープロットとエラーバーを描画
plt.errorbar(x_values1, y_values1,  yerr=y_error1, fmt='s', capsize=5, color='black',label='Expt',markersize=7)


plt.errorbar(x_values2, y_values2, yerr=y_error2, fmt='s', capsize=5, color='black',markerfacecolor='white',label='AMEpredic',markersize=7)

plt.errorbar(x_values3, y_values3,  yerr=y_error3, fmt='o', capsize=5, color='red',markerfacecolor='red',label='This work',markersize=7)

plt.errorbar(x_values4, y_values4,  fmt='*', capsize=5, color='cyan',label='Q2p',markersize=10)

#plt.errorbar(x_values5, y_values5, xerr=x_error5, yerr=y_error5, fmt='--', color='blue',label='pf')
plt.plot(x_values5, y_values5,  linestyle='--', color='blue',label='pf')

#plt.errorbar(x_values6, y_values6, xerr=x_error6, yerr=y_error6, fmt='-', color='magenta',label='pfg9/2')
plt.plot(x_values6, y_values6, linestyle='-', color='magenta',label='pfg9/2')

plt.axhline(0, color='black', linestyle='--', linewidth=1, label='y=0')




#r グラフのタイトルと軸ラベルを設定
#plt.title('Scatter Plot with Multiple Data Sets')
#plt.xlabel('X-axis')
#plt.ylabel('Y-axis')

plt.xticks([28,27,26,25,24,23,22])
plt.yticks([-4,-3,-2,-1,0,1,2,3,4,5,6])


plt.tick_params(axis='both', which='both', direction='in')

# 凡例を表示
plt.legend()

plt.xlim(21.3,28.5)
plt.ylim(-4,6)


# グリッドを表示
#plt.grid(True)

# グラフを表示
#plt.show()

#plt.savefig('./plot_s2p_n20.svg',format='svg')
plt.savefig('./plot_s2p_n20_20240216.svg',format='svg')




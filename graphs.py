# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import math
#X轴，Y轴数据
# x_NN = []

# for i in range(46,61):
#     x_NN.append(i)

x_NN = [48,50,52,54,55,56,57,58,59,60]
y_NN = [4,1,9,6,6,11,7,17,48,177]

x_NK = [46,48,49,50,52,53,54,55,56,57,58,59,60]
y_NK = [3,1,14,18,8,85,77,6,47,230,325,71,288]

x_KK = [35,36]
for i in range(39,61):
    x_KK.append(i)
y_KK = [1,7,9,45,2,11,23,124,11,71,78,296,28,211,386,1150,83,590,1193,3866,455,2688,3653,9303]

x_KN = [32,41,42,44,45,46]
for i in range(48,61):
    x_KN.append(i)

y_KN = [1,2,2,2,4,32,10,16,133,8,48,171,260,64,170,33,31,56,295]

# x_NK = []
# ytic= [1,10,100,1000,10000]
# ytic= [1,10,100]


plt.figure() #创建绘图对象

# plt.yscale('log')

y_NN_log2 = [math.log(a,2) for a in y_NN]
y_NK_log2 = [math.log(b,2) for b in y_NK]
y_KK_log2 = [math.log(c,2) for c in y_KK]
y_KN_log2 = [math.log(d,2) for d in y_KN]

# NN, = plt.plot(x_NN,y_NN,"b^-",linewidth=1)   #在当前绘图对象绘图（X轴，Y轴，蓝色虚线，线宽度）
# NK, = plt.plot(x_NK,y_NK,"r*-",linewidth=1)
# KK, = plt.plot(x_KK,y_KK,"go-",linewidth=1)

NN, = plt.plot(x_NN,y_NN_log2,"b^-",linewidth=1)
NK, = plt.plot(x_NK,y_NK_log2,"r*-",linewidth=1)
KK, = plt.plot(x_KK,y_KK_log2,"go-",linewidth=1)
KN, = plt.plot(x_KN,y_KN_log2,"yD-",linewidth=1)

# plt.legend(handles=[NN,NK,KK],lables=['|N|N|','|N|K|','|K|K|'],loc='best')
# plt.legend()
plt.legend(['|N|N|','|N|K|','|K|K|','|K|N| (partial)'])
# ytick=[1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384]
ytic=range(0,15)
plt.yticks(ytic)
plt.xlabel("T₃") #X轴标签

plt.ylabel("# Cores(log2)")  #Y轴标签
plt.title("Number of 3-round trail cores of weight T₃") #图标题
plt.show()  #显示图
# plt.savefig("line.jpg") #保存图

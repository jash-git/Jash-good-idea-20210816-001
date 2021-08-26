# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
#主函数
if __name__ =="__main__":
    #输入矩阵
    I = np.array([[1,2],[3,4]],np.float32)
    # I 的高和宽
    H1,W1 = I.shape[:2]
    #卷积核
    K = np.array([[-1,-2],[2,1]],np.float32)
    # K 的高和宽
    H2,W2 = K.shape[:2]
    #计算 full 卷积
    c_full = signal.convolve2d(I,K,mode='full')
    #指定锚点的位置
    kr,kc = 1,0
    #根据锚点位置，从 full 卷积中截取得到 same 卷积
    c_same = c_full[H2-kr-1:H1+H2-kr-1,W2-kc-1:W1+W2-kc-1]
    print c_same
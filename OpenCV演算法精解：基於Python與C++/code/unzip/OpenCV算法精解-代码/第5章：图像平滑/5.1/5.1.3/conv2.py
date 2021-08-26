# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
#主函数
if __name__ =="__main__":
    #图像矩阵
    I=np.array([[1,2,3,10,12],
                [32,43,12,4,190],
                [12,234,78,0,12],
                [43,90,32,8,90],
                [71,12,4,98,123]],np.float32)
    #卷积核
    kernel = np.array([[1,0,-1],
                       [1,0,-1],
                       [1,0,-1]])
    # full 卷积
    fullConv = signal.convolve2d(I,kernel,mode='full',boundary = 'fill',fillvalue= 0)
    # same 卷积
    sameConv = signal.convolve2d(I,kernel,mode='same',boundary = 'symm')
    # valid 卷积
    validConv = signal.convolve2d(I,kernel,mode='valid')
    print fullConv
    print sameConv
    print validConv
    


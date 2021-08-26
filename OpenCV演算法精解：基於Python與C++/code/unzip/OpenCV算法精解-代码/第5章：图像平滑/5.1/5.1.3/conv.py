# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
#主函数
if __name__ =="__main__":
    #图像矩阵
    '''
    I=np.array([[1,2,3,10,12],
                [32,43,12,4,190],
                [12,234,78,0,12],
                [43,90,32,8,90],
                [71,12,4,98,123]],np.float32)
    '''
    I = np.ones((10,10),np.float32)
    I[1:3,3:5]=5
    I[3:5,4:7]=3
    #卷积核
    '''
        kernel = np.array([[1,0,-1],
                       [1,0,-1],
                       [1,0,-1]])
    '''
    kernel1 = np.array([[1,3,4],[9,10,2],[-1,10,2]],np.float32)
    kernel2 = np.array([[-1,2,3],[4,5,6],[10,9,10]],np.float32)
    #kernel1 = np.array([[-1,2,3]],np.float32)
    #kernel2 = np.array([[10],[43],[1]],np.float32)
    kernel = signal.convolve2d(kernel1,kernel2,mode='full')
    print kernel
    #第一种方式:直接进行卷积运算得到的结果
    I_Kernel = signal.convolve2d(I,kernel,mode='same',boundary = 'symm',fillvalue= 0)
    #第二种方式:用可分离卷积核性质得到的结果
    I_kernel1 = signal.convolve2d(I,kernel1,mode='same',boundary = 'wrap',fillvalue= 0)
    I_kernel1_kernel2 = signal.convolve2d(I_kernel1,kernel2,mode='same',boundary = 'wrap',fillvalue= 0)
    #print I_Kernel
    print "*******************"
    print np.max(np.abs(I_Kernel - I_kernel1_kernel2))
    print "********************"
    print I_Kernel
    print I_kernel1_kernel2
    


# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
import cv2

#主函数
if __name__ =="__main__":
    #图像矩阵
    I = np.array([
                  [34,56,1,0,255,230,45,12],
                  [0,201,101,125,52,12,124,12],
                  [3,41,42,40,12,90,123,45],
                  [5,245,98,32,34,234,90,123],
                  [12,12,10,41,56,89,189,5],
                  [112,87,12,45,78,45,10,1],
                  [42,123,234,12,12,21,56,43],
                  [1,2,45,123,10,44,123,90]
                  ],np.float64)
    #卷积核
    kernel = np.array([[1,0,-1],[1,0,1],[1,0,-1]],np.float64)
    # I 与 kernel 进行全卷积
    confull = signal.convolve2d(I,kernel,mode='full',boundary = 'fill',fillvalue=0)
    # I 的傅里叶变换
    FT_I = np.zeros((I.shape[0],I.shape[1],2),np.float64)
    cv2.dft(I,FT_I,cv2.DFT_COMPLEX_OUTPUT)
    # kernel 的傅里叶变换
    FT_kernel = np.zeros((kernel.shape[0],kernel.shape[1],2),np.float64)
    cv2.dft(kernel,FT_kernel,cv2.DFT_COMPLEX_OUTPUT)
    # 傅里叶变换
    fft2= np.zeros((confull.shape[0],confull.shape[1]),np.float64)
    #对 I 进行右侧和下侧补 0
    I_Padded = np.zeros((I.shape[0]+kernel.shape[0]-1,I.shape[1]+kernel.shape[1]-1),np.float64)
    I_Padded[:I.shape[0],:I.shape[1]] = I
    FT_I_Padded = np.zeros((I_Padded.shape[0],I_Padded.shape[1],2),np.float64)
    cv2.dft(I_Padded,FT_I_Padded,cv2.DFT_COMPLEX_OUTPUT)
    #对 kernel 进行右侧和下侧补 0 
    kernel_Padded = np.zeros((I.shape[0]+kernel.shape[0]-1,I.shape[1]+kernel.shape[1]-1),np.float64)
    kernel_Padded[:kernel.shape[0],:kernel.shape[1]] = kernel
    FT_kernel_Padded = np.zeros((kernel_Padded.shape[0],kernel_Padded.shape[1],2),np.float64)
    cv2.dft(kernel_Padded,FT_kernel_Padded,cv2.DFT_COMPLEX_OUTPUT)
    #两个傅里叶变换相乘
    FT_Ikernel = cv2.mulSpectrums(FT_I_Padded,FT_kernel_Padded,cv2.DFT_ROWS)
    #利用傅里叶变换求全 ( full ) 卷积
    ifft2 = np.zeros(FT_Ikernel.shape[:2],np.float64)
    cv2.dft(FT_Ikernel,ifft2,cv2.DFT_REAL_OUTPUT+cv2.DFT_INVERSE+cv2.DFT_SCALE)
    print np.max(ifft2 - confull)
    
    # 全卷积进行傅里叶变换等于两个傅里叶变换的点乘
    FT_confull = np.zeros((confull.shape[0],confull.shape[1],2),np.float64)
    cv2.dft(confull,FT_confull,cv2.DFT_COMPLEX_OUTPUT)
    print FT_confull-FT_Ikernel
    print np.max(FT_confull-FT_Ikernel)
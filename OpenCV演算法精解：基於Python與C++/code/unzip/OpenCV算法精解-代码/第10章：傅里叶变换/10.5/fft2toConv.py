# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
import cv2
#利用傅里叶变换计算离散的二维卷积
def fft2Conv(I,kernel,borderType=cv2.BORDER_DEFAULT):
    #图像矩阵的高、宽
    R,C = I.shape[:2]
    #卷积核的高、宽
    r,c = kernel.shape[:2]
    #卷积核的半径
    tb = (r-1)/2
    lr = (c-1)/2
    #第一步：扩充边界
    I_padded = cv2.copyMakeBorder(I,tb,tb,lr,lr,borderType)
    #第二步：对 I_padded 和 kernel 右侧和下侧补零
    #满足二维快速傅里叶变换的行数、列数
    rows = cv2.getOptimalDFTSize(I_padded.shape[0]+r-1)
    cols = cv2.getOptimalDFTSize(I_padded.shape[1]+c-1)
    #补零
    I_padded_zeros = np.zeros((rows,cols),np.float64)
    I_padded_zeros[:I_padded.shape[0],:I_padded.shape[1]] = I_padded
    kernel_zeros = np.zeros((rows,cols),np.float64)
    kernel_zeros[:kernel.shape[0],:kernel.shape[1]] = kernel
    #第三步：快速傅里叶变换
    fft2_Ipz = np.zeros((rows,cols,2),np.float64)
    cv2.dft(I_padded_zeros,fft2_Ipz,cv2.DFT_COMPLEX_OUTPUT)
    fft2_kz = np.zeros((rows,cols,2),np.float64)
    cv2.dft(kernel_zeros,fft2_kz,cv2.DFT_COMPLEX_OUTPUT)
    #第四步：两个快速傅里叶变换点乘
    Ipz_rz = cv2.mulSpectrums(fft2_Ipz,fft2_kz,cv2.DFT_ROWS)
    #第五步：傅里叶逆变换，并只取实部
    ifft2FullConv = np.zeros((rows,cols),np.float64)
    cv2.dft(Ipz_rz,ifft2FullConv,cv2.DFT_REAL_OUTPUT+cv2.DFT_INVERSE+cv2.DFT_SCALE)
    print np.max(ifft2FullConv)
    #第六步：裁剪，同输入的图像矩阵尺寸一样
    sameConv = np.copy(ifft2FullConv[r-1:R+r-1,c-1:C+c-1])
    return sameConv
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
                  ],np.float32)
    #卷积核
    kernel = np.array([[1,0,-1],[1,0,-1],[1,0,-1]],np.float32)
    # same 卷积
    consame = signal.convolve2d(I,kernel,mode='same',boundary = 'symm')
    print consame
    # 利用傅里叶变换计算卷积
    sameConv = fft2Conv(I,kernel,cv2.BORDER_REFLECT)
    print sameConv

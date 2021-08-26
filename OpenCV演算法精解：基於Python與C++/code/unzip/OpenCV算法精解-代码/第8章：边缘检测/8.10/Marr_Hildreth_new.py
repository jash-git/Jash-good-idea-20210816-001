# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
from scipy import signal
#非归一化的高斯卷积
def gaussConv(I,size,sigma):
    #卷积核的高和宽
    H,W = size
    #构造水平方向上非归一化的高斯卷积核
    xr,xc = np.mgrid[0:1,0:W]
    xc -= (W-1)/2
    xk = np.exp(-np.power(xc,2.0)/(2.0*pow(sigma,2)))
    # I 与 xk 卷积
    I_xk = signal.convolve2d(I,xk,'same','symm')
    #构造垂直方向上的非归一化的高斯卷积核
    yr,yc = np.mgrid[0:H,0:1]
    yr -= (H-1)/2
    yk = np.exp(-np.power(yr,2.0)/(2.0*pow(sigma,2.0)))
    # I_xk 与 yk 卷积
    I_xk_yk = signal.convolve2d(I_xk,yk,'same','symm')
    I_xk_yk *= 1.0/(2*np.pi*pow(sigma,2.0))
    return I_xk_yk
#高斯差分
def DoG(I,size,sigma,k=1.1):
    #标准差为 sigma 的非归一化的高斯卷积
    Is = gaussConv(I,size,sigma)
    #标准差为 k*sigma 的非归一化高斯卷积
    Isk = gaussConv(I,size,k*sigma)
    #两个高斯卷积的差分
    doG = Isk - Is
    doG /= (pow(sigma,2.0)*(k-1))
    return doG
#零交叉点：方法1
def zero_cross_default(doG):
    zero_cross = np.zeros(doG.shape,np.uint8)
    rows,cols = doG.shape
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            # 左 / 右方向
            if doG[r][c-1]*doG[r][c+1] < 0:
                zero_cross[r][c] = 255
                continue
            #上 / 下方向
            if doG[r-1][c]*doG[r+1][c] < 0:
                zero_cross[r][c] = 255
                continue
            #左上 / 右下方向
            if doG[r-1][c-1]*doG[r+1][c+1] < 0:
                zero_cross[r][c] = 255
                continue
            #右上 / 左下方向
            if doG[r-1][c+1]*doG[r+1][c-1] < 0:
                zero_cross[r][c] = 255
                continue
    return zero_cross
#零交叉点：方法2
def zero_cross_mean(doG):
    zero_cross = np.zeros(doG.shape,np.uint8)
    #存储左上，右上，左下，右下方向
    fourMean = np.zeros(4,np.float32)
    rows,cols = doG.shape
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            #左上方的均值
            leftTopMean = np.mean(doG[r-1:r+1,c-1:c+1])
            fourMean[0] = leftTopMean
            #右上方的均值
            rightTopMean = np.mean(doG[r-1:r+1,c:c+2])
            fourMean[1] = rightTopMean
            #左下方的均值
            leftBottomMean = np.mean(doG[r:r+2,c-1:c+1])
            fourMean[2] = leftBottomMean
            #右下方的均值
            rightBottomMean = np.mean(doG[r:r+2,c:c+2])
            fourMean[3] = rightBottomMean
            if(np.min(fourMean)*np.max(fourMean)<0):
                zero_cross[r][c] = 255
    return zero_cross
# Marr_Hildreth 边缘检测算法
def Marr_Hildreth(image,size,sigma,k=1.1,crossType="ZERO_CROSS_DEFAULT"):
    #高斯差分
    doG = DoG(image,size,sigma,k)
    #过零点
    if crossType == "ZERO_CROSS_DEFAULT":
        zero_cross = zero_cross_default(doG)
    elif  crossType == "ZERO_CROSS_MEAN":
        zero_cross = zero_cross_mean(doG)
    else:
        print "no crossType"
    return zero_cross
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python Marr_Hilreth.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    # Marr-Hilreth 边缘检测算法
    result = Marr_Hildreth(image,(19,19),2,1.1,"ZERO_CROSS_MEAN")
    cv2.imshow("Marr-Hildreth",result)
    cv2.imwrite("MH.jpg",result)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
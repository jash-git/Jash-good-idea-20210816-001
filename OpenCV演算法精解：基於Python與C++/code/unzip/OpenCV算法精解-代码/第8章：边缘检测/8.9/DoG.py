# -*- coding: utf-8 -*-
import sys
import cv2
import numpy as np
from scipy import signal
import math
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
    #
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
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python DoG.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #高斯差分边缘检测
    sigma = 4
    k = 0.9
    size = (25,25)
    imageDoG = DoG(image,size,sigma,k)
    #二值化边缘，对 imageDoG 阈值处理
    edge = np.copy(imageDoG)
    edge[edge>0] = 255
    edge[edge<=0] = 0
    edge = edge.astype(np.uint8)
    cv2.imshow("edge",edge)
    cv2.imwrite("edge.jpg",edge)
    #图像边缘抽象化
    asbstraction = -np.copy(imageDoG)
    asbstraction = asbstraction.astype(np.float32)
    asbstraction[asbstraction>=0]=1.0
    asbstraction[asbstraction<0] = 1.0+ np.tanh(asbstraction[asbstraction<0])
    cv2.imshow("asbstraction",asbstraction)
    asbstraction = asbstraction*255
    asbstraction = asbstraction.astype(np.uint8)
    cv2.imwrite("asbstraction.jpg",asbstraction)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
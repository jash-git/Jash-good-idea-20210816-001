# -*- coding: utf-8 -*-
import numpy as np
import sys
import math
import cv2
from scipy import signal
#二项式展开式的系数，即平滑系数
def pascalSmooth(n):
    pascalSmooth = np.zeros([1,n],np.float32)
    for i in range(n):
        pascalSmooth[0][i] = math.factorial(n -1)/(math.factorial(i)*math.factorial(n-1-i))
    return pascalSmooth
#计算差分
def pascalDiff(n):
    pascalDiff = np.zeros([1,n],np.float32)
    pascalSmooth_previous = pascalSmooth(n-1)
    for i in range(n):
        if i ==0:
            #恒等于 1
            pascalDiff[0][i] = pascalSmooth_previous[0][i]
        elif i == n-1:
            #恒等于 -1
            pascalDiff[0][i] = -pascalSmooth_previous[0][i-1]
        else:
            pascalDiff[0][i] = pascalSmooth_previous[0][i] - pascalSmooth_previous[0][i-1]
    return pascalDiff
#通过平滑系数和差分系数的卷积运算计算卷积核
def getSobelKernel(winSize):
     pascalSmoothKernel = pascalSmooth(winSize)
     pascalDiffKernel = pascalDiff(winSize)
     #水平方向上的卷积核
     sobelKernel_x = signal.convolve2d(pascalSmoothKernel.transpose(),pascalDiffKernel,mode='full')
     #垂直方向上的卷积核
     sobelKernel_y = signal.convolve2d(pascalSmoothKernel,pascalDiffKernel.transpose(),mode='full')
     return (sobelKernel_x,sobelKernel_y)
# sobel 边缘检测
def sobel(image,winSize):
    rows,cols = image.shape
    pascalSmoothKernel = pascalSmooth(winSize)
    pascalDiffKernel = pascalDiff(winSize)
    # --- 与水平方向的卷积核卷积 ----
    image_sobel_x = np.zeros(image.shape,np.float32)
    #垂直方向上的平滑
    image_sobel_x = signal.convolve2d(image,pascalSmoothKernel.transpose(),mode='same')
    #水平方向上的差分
    image_sobel_x = signal.convolve2d(image_sobel_x,pascalDiffKernel,mode='same')
    # --- 与垂直方向上的卷积核卷积 --- 
    image_sobel_y = np.zeros(image.shape,np.float32)
    #水平方向上的平滑
    image_sobel_y = signal.convolve2d(image,pascalSmoothKernel,mode='same')
    #垂直方向上的差分
    image_sobel_y = signal.convolve2d(image_sobel_y,pascalDiffKernel.transpose(),mode='same')
    return (image_sobel_x,image_sobel_y)
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python Sobel.py imageFile"
    #得到卷积核
    sobelKernel3 = getSobelKernel(3)
    sobelKernel5 = getSobelKernel(5)
    print(sobelKernel3)
    print(sobelKernel5)
    #卷积
    image_sobel_x,image_sobel_y = sobel(image,3)
    edge_x = np.abs(image_sobel_x)
    edge_x[ edge_x>255]=255
    edge_x=edge_x.astype(np.uint8)
    edge_y = np.abs(image_sobel_y)
    edge_y[ edge_y>255]=255
    edge_y=edge_y.astype(np.uint8)
    cv2.imwrite("img7_sobel_x_3_3.jpg",edge_x)
    cv2.imwrite("img7_sobel_y_3_3.jpg",edge_y)
    #边缘强度：两个卷积结果对应位置的平方和
    edge = np.sqrt(np.power(image_sobel_x,2.0) + np.power(image_sobel_y,2.0))
    #边缘强度的灰度级显示
    edge[edge>255] = 255
    edge = np.round(edge)
    edge = edge.astype(np.uint8)
    cv2.imshow("sobel edge",edge)
    cv2.imwrite("sobel.jpg",edge)
    #模拟素描
    pencilSketch = edge.copy()
    pencilSketch = 255 - pencilSketch
    pencilSketch[pencilSketch < 80] = 80
    cv2.imshow("pencilSketch",pencilSketch)
    cv2.imwrite("pencilSketch.jpg",pencilSketch)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
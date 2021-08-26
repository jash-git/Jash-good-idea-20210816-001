# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
from scipy import signal
#构建 LoG 算子
def createLoGKernel(sigma,kSize):
    # LoG 算子的宽高，且两者均为奇数
    winH,winW = kSize
    logKernel = np.zeros(kSize,np.float32)
    #方差
    sigmaSquare = pow(sigma,2.0)
    # LoG 算子的中心
    centerH = (winH-1)/2
    centerW = (winW-1)/2
    for r in xrange(winH):
        for c in xrange(winW):
            norm2 = pow(r-centerH,2.0) + pow(c-centerW,2.0)
            logKernel[r][c] = 1.0/sigmaSquare*(norm2/sigmaSquare - 2)*math.exp(-norm2/(2*sigmaSquare))
    return logKernel
#零交叉点：方法1
def zero_cross_default(img_conv_log):
    zero_cross = np.zeros(img_conv_log.shape,np.uint8)
    rows,cols = img_conv_log.shape
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            # 左 / 右方向
            if img_conv_log[r][c-1]*img_conv_log[r][c+1] < 0:
                zero_cross[r][c] = 255
                continue
            #上 / 下方向
            if img_conv_log[r-1][c]*img_conv_log[r+1][c] < 0:
                zero_cross[r][c] = 255
                continue
            #左上 / 右下方向
            if img_conv_log[r-1][c-1]*img_conv_log[r+1][c+1] < 0:
                zero_cross[r][c] = 255
                continue
            #右上 / 左下方向
            if img_conv_log[r-1][c+1]*img_conv_log[r+1][c-1] < 0:
                zero_cross[r][c] = 255
                continue
    return zero_cross
#零交叉点：方法2
def zero_cross_mean(img_conv_log):
    zero_cross = np.zeros(img_conv_log.shape,np.uint8)
    #存储左上，右上，左下，右下方向
    fourMean = np.zeros(4,np.float32)
    rows,cols = img_conv_log.shape
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            #左上方的均值
            leftTopMean = np.mean(img_conv_log[r-1:r+1,c-1:c+1])
            fourMean[0] = leftTopMean
            #右上方的均值
            rightTopMean = np.mean(img_conv_log[r-1:r+1,c:c+2])
            fourMean[1] = rightTopMean
            #左下方的均值
            leftBottomMean = np.mean(img_conv_log[r:r+2,c-1:c+1])
            fourMean[2] = leftBottomMean
            #右下方的均值
            rightBottomMean = np.mean(img_conv_log[r:r+2,c:c+2])
            fourMean[3] = rightBottomMean
            if(np.min(fourMean)*np.max(fourMean)<0):
                zero_cross[r][c] = 255
    return zero_cross
# Marr_Hildreth 边缘检测算法
def Marr_Hildreth(image,loGSize,sigma,crossType="ZERO_CROSS_DEFAULT"):
    #第一步：创建 LoG 算子
    loGKernel = createLoGKernel(sigma,loGSize)
    #第二步：图像与 LoG 算子的卷积
    img_conv_log = signal.convolve2d(image,loGKernel,'same','symm')
    #第三步：过零点
    if crossType == "ZERO_CROSS_DEFAULT":
        zero_cross = zero_cross_default(img_conv_log)
    elif  crossType == "ZERO_CROSS_MEAN":
        zero_cross = zero_cross_mean(img_conv_log)
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
    result = Marr_Hildreth(image,(13,13),2,"ZERO_CROSS_MEAN")
    result = 255 - result
    cv2.imshow("Marr-Hildreth",result)
    cv2.imwrite("MH.jpg",result)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
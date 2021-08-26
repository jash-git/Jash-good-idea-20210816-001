# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
#计算图像灰度直方图
def calcGrayHist(image):
    #灰度图像矩阵的宽高
    rows,cols = image.shape
    #存储灰度直方图
    grayHist = np.zeros([1,256],np.uint32)
    for r in xrange(rows):
        for c in xrange(cols):
            grayHist[0][image[r][c]] +=1
    return grayHist         
def ostu(image):
    rows,cols = image.shape
    #计算图像的灰度直方图
    grayHist = calcGrayHist(image)
    #归一化灰度直方图
    uniformGrayHist = grayHist/float(rows*cols)
    #计算零阶累积矩和一阶累积矩
    zeroCumuMoment = np.zeros([1,256],np.float32)
    oneCumuMoment = np.zeros([1,256],np.float32)
    for k in xrange(256):
        if k == 0:
            zeroCumuMoment[0][k] = uniformGrayHist[0][0]
            oneCumuMoment[0][k] = (k+1)*uniformGrayHist[0][0]
        else:
            zeroCumuMoment[0][k] = zeroCumuMoment[0][k-1] + uniformGrayHist[0][k]
            oneCumuMoment[0][k] = oneCumuMoment[0][k-1] + k*uniformGrayHist[0][k]
    #计算类间方差  
    variance = np.zeros([1,256],np.float32)
    for k in xrange(255):
        if zeroCumuMoment[0][k] == 0:
            variance[0][k] = 0
        else:
            variance[0][k] = math.pow(oneCumuMoment[0][255]*zeroCumuMoment[0][k] - oneCumuMoment[0][k],2)/(zeroCumuMoment[0][k]*(1.0-zeroCumuMoment[0][k]))
    #找到阈值
    threshLoc = np.where(variance[0][0:255] == np.max(variance[0][0:255]))
    thresh = threshLoc[0]
    #阈值处理
    threshold = np.copy(image)
    threshold[threshold > thresh] = 255
    threshold[threshold <= thresh] = 0
    return threshold
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python ostu.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #阈值算法
    ostu_threshold = ostu(image)
    #显示阈值处理的结果
    cv2.imshow("ostu_threshold",ostu_threshold)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

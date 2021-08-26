# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
import matplotlib.pyplot as plt
#计算图像灰度直方图
def calcGrayHist(image):
    #灰度图像矩阵的宽高
    rows,cols = image.shape
    #存储灰度直方图
    grayHist = np.zeros([256],np.uint32)
    for r in xrange(rows):
        for c in xrange(cols):
            grayHist[image[r][c]] +=1
    return grayHist
#直方图均衡化
def equalHist(image):
    #灰度图像矩阵的宽高
    rows,cols = image.shape
    #计算灰度直方图
    grayHist = calcGrayHist(image)
    #计算累积灰度直方图
    zeroCumuMoment = np.zeros([256],np.uint32)
    for p in xrange(256):
        if p == 0:
            zeroCumuMoment[p] = grayHist[0]
        else:
            zeroCumuMoment[p] = zeroCumuMoment[p-1] + grayHist[p]
    #根据直方图均衡化得到的输入灰度级和输出灰度级的映射
    outPut_q = np.zeros([256],np.uint8)
    cofficient = 256.0/(rows*cols)
    for p in xrange(256):
        q = cofficient* float(zeroCumuMoment[p]) -1
        if q >= 0:
            outPut_q[p] = math.floor(q)
        else:
            outPut_q[p] = 0
    #得到直方图均衡化后的图像
    equalHistImage  = np.zeros(image.shape,np.uint8)
    for r in xrange(rows):
        for c in xrange(cols):
            equalHistImage[r][c] = outPut_q[image[r][c]]
    return equalHistImage
            
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python equalHist.py imageFile"
    #显示原图像
    cv2.imshow("image",image)
    #直方图均衡化
    result = equalHist(image)
    cv2.imshow("equalHist",result)
    cv2.imwrite("equalHist.jpg",result)
    #直方图均衡话后的灰度直方图
    #组数
    numberBins = 256
    #计算灰度直方图
    rows,cols = image.shape
    histEqualResultSeq = result.reshape([rows*cols,])
    histogram,bins,patch_image= plt.hist(histEqualResultSeq,numberBins,facecolor='black',histtype='bar')
    #设置坐标轴的标签
    plt.xlabel(u"gray Level")
    plt.ylabel(u"number of pixels")
    #设置坐标轴的范围
    y_maxValue = np.max(histogram)
    plt.axis([0,255,0,y_maxValue])
    plt.show()
    cv2.waitKey(0)
    cv2.destroyAllWindows()
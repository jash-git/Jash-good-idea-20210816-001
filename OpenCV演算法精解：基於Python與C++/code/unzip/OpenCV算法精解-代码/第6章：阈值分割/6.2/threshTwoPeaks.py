# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
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
#返回阈值和二值图
def threshTwoPeaks(image):
    #计算回复直方图
    histogram = calcGrayHist(image)
    #找到灰度直方图的最大峰值对应的灰度值
    maxLoc = np.where(histogram==np.max(histogram))
    firstPeak = maxLoc[0]
    print maxLoc[0]
    #寻找灰度直方图的 " 第二个峰值 " 对应的灰度值
    measureDists = np.zeros([256],np.float32)
    for k in xrange(256):
        measureDists[k] = pow(k-firstPeak,2)*histogram[k]
    maxLoc2 = np.where(measureDists==np.max(measureDists))
    secondPeak = maxLoc2[0]
    #找到两个峰值之间的最小值对应的灰度值，作为阈值
    thresh = 0
    if firstPeak > secondPeak:
        temp = histogram[int(secondPeak):int(firstPeak)]
        minLoc = np.where(temp == np.min(temp))
        thresh = secondPeak + minLoc[0]+1
    else:
        temp = histogram[int(firstPeak):int(secondPeak)]
        minLoc = np.where( temp == np.min(temp))
        thresh = firstPeak + minLoc[0]+1
    #找到阈值后进行阈值处理，得到二值图
    threshImage_out = image.copy()
    threshImage_out[threshImage_out > thresh] = 255
    threshImage_out[threshImage_out <= thresh] = 0
    return (thresh,threshImage_out)
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python threshTwoPeaks.py imageFile"
    thresh,threshImage_out = threshTwoPeaks(image)
    #输出直方图技术得到的阈值
    print thresh
    #显示原图和阈值化得到的二值图
    cv2.imshow("image",image)
    cv2.imshow("threshTwoPeaks",threshImage_out)
    cv2.imwrite("twoPeaks.jpg",threshImage_out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
#基于空间距离的权重模板 ( 和计算高斯算子的过程是一样的 )
def getClosenessWeight(sigma_g,H,W):
    r,c = np.mgrid[0:H:1, 0:W:1]
    r -= (H-1)/2
    c -= (W-1)/2
    closeWeight = np.exp(-0.5*(np.power(r,2)+np.power(c,2))/math.pow(sigma_g,2))
    return closeWeight
# BilateralFiltering 双边滤波，返回的数据类型为浮点型
def bfltGray(I,H,W,sigma_g,sigma_d):
    #构建空间距离的权重模板
    closenessWeight = getClosenessWeight(sigma_g,H,W)
    #模板的中心点位置
    cH = (H -1)/2
    cW = (W -1)/2
    #图像矩阵的行数和列数
    rows,cols = I.shape
    #双边滤波后的结果
    bfltGrayImage = np.zeros(I.shape,np.float32)
    for r in xrange(rows):
        for c in xrange(cols):
            pixel = I[r][c]
            #判断边界
            rTop = 0 if r-cH < 0 else r-cH
            rBottom = rows-1 if r+cH > rows-1 else r+cH
            cLeft = 0 if c-cW < 0 else c-cW
            cRight = cols-1 if c+cW > cols-1 else c+cW
            #权重模板作用的区域
            region = I[rTop:rBottom+1,cLeft:cRight+1]
            #构建灰度值相似性的权重因子
            similarityWeightTemp = np.exp(-0.5*np.power(region -pixel,2.0)/math.pow(sigma_d,2))        
            closenessWeightTemp = closenessWeight[rTop-r+cH:rBottom-r+cH+1,cLeft-c+cW:cRight-c+cW+1]
            #两个权重模板相乘
            weightTemp = similarityWeightTemp*closenessWeightTemp
            weightTemp = weightTemp/np.sum(weightTemp)
            bfltGrayImage[r][c] = np.sum(region*weightTemp)
    return bfltGrayImage
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python BFilter.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    cv2.imwrite("image.png",image)
    #将灰度值归一化
    image = image/255.0
    #双边滤波
    bfltImage = bfltGray(image,33,33,10,0.8)
    #显示双边滤波的结果
    cv2.imshow("BilateralFiltering",bfltImage)
    bfltImage = bfltImage*255.0
    bfltImage = np.round(bfltImage)
    bfltImage = bfltImage.astype(np.uint8)
    #保存双边滤波的结果
    cv2.imwrite("BilateralFiltering.png",bfltImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

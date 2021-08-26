# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
#基于空间距离的权重因子 ( 和计算高斯算子的过程是一样的 )
def getClosenessWeight(sigma_g,H,W):
    #第一步：构建高斯矩阵gaussMatrix
    gaussMatrix = np.zeros([H,W],np.float32)
    #得到中心点的位置
    cH = (H-1)/2
    cW = (W-1)/2
    for r in xrange(H):
        for c in xrange(W):
            norm2 = math.pow(r-cH,2.0) + math.pow(c-cW,2.0)
            gaussMatrix[r][c] = math.exp(-norm2/(2*math.pow(sigma_g,2.0)))
    #第二步：计算高斯矩阵的和
    sumGM = np.sum(gaussMatrix)
    #第三步：归一化，gaussMatrix/sumGM
    gaussMatrix = gaussMatrix/sumGM
    return gaussMatrix
# BilateralFiltering 双边滤波，返回的数据类型为浮点型
def bfltGray(image,winH,winW,sigma_g,sigma_d):
    #构建空间距离的权重因子
    closenessWeight = getClosenessWeight(sigma_g,winH,winW)
    #得到卷积核的中心点坐标
    halfWinH = (winH -1)/2
    halfWinW = (winW -1)/2
    #图像矩阵的行数和列数
    rows,cols = image.shape
    #双边滤波后的结果
    bfltGrayImage = np.zeros(image.shape,np.float32)
    for r in xrange(rows):
        for c in xrange(cols):
            pixel = image[r][c]
            #判断边界
            rTop = 0 if r-halfWinH < 0 else r-halfWinH
            rBottom = rows-1 if r+halfWinH > rows-1 else r+halfWinH
            cLeft = 0 if c-halfWinW < 0 else c-halfWinW
            cRight = cols-1 if c+halfWinW > cols-1 else c+halfWinW
            #核作用的区域
            region = image[rTop:rBottom+1,cLeft:cRight+1]
            #构建灰度值相似性的权重因子
            similarityWeightTemp = np.exp(-0.5*pow(region -pixel,2.0)/pow(sigma_d,2.0))#错误
            closenessWeightTemp = closenessWeight[rTop-r+halfWinH:rBottom-r+halfWinH+1,cLeft-c+halfWinW:cRight-c+halfWinW+1]
            #两个核相乘
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
    #双边滤波
    image = image.astype(np.float32)
    bfltImage = bfltGray(image,21,21,30,30)
    bfltImage = bfltImage/255.0
    #显示双边滤波的结果
    bfltImage = bfltImage.astype(np.float32)
    cv2.imshow("BilateralFiltering",bfltImage)
    #因为双边滤波返回的是数据类型是浮点型的,可以转换为 8 位图
   # bfltImage = bfltImage*255.0
    #bfltImage = np.round(bfltImage)
    #bfltImage = bfltImage.astype(np.uint8)
    #保存双边滤波的结果
    cv2.imwrite("BilateralFiltering.jpg",bfltImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

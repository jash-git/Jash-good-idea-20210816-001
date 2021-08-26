# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
#基于空间距离的权重因子 ( 和计算高斯核的过程类似 )
def getClosenessWeight(sigma_d,H,W):
    #构建距离权重因子
    closenessWeight = np.zeros([H,W],np.float32)
    #得到中心点的位置
    cH = (H-1)/2
    cW = (W-1)/2
    for r in xrange(H):
        for c in xrange(W):
            norm2 = math.pow(r-cH,2.0) + math.pow(c-cW,2.0)
            closenessWeight[r][c] = math.exp(-norm2/(2*math.pow(sigma_d,2.0)))
    return closenessWeight
# BilateralFiltering 双边滤波，返回的数据类型为浮点型
def blFilter(image,winH,winW,sigma_d,sigma_s):
    #构建空间距离的权重因子
    closenessWeight = getClosenessWeight(sigma_d,winH,winW)
    #得到卷积核的中心点坐标
    halfWinH = (winH -1)/2
    halfWinW = (winW -1)/2
    #图像矩阵的行数和列数
    rows,cols = image.shape
    #双边滤波后的结果
    blfImage = np.zeros(image.shape,np.float32)
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
            similarityWeightTemp = np.exp(-0.5*np.power(region -pixel,2.0)/np.power(sigma_s,2.0))
            closenessWeightTemp = closenessWeight[rTop-r+halfWinH:rBottom-r+halfWinH+1,cLeft-c+halfWinW:cRight-c+halfWinW+1]
            #两个权重因子对应位置相乘
            weightTemp = similarityWeightTemp*closenessWeightTemp
            #归一化
            weightTemp = weightTemp/np.sum(weightTemp)
            blfImage[r][c] = np.sum(region*weightTemp)
    return blfImage
#彩色双边滤波 返回的是浮点型
def blFilterColor(colorImage,winH,winW,sigma_d,sigma_s):
    #分别对三个颜色通道进行双边滤波
    blfColorImage = np.zeros(colorImage.shape,np.float32)
    for c in xrange(3):
        blfColorImage[:,:,c] =  blFilter(colorImage[:,:,c],winH,winW,sigma_d,sigma_s)
    return blfColorImage
    
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_COLOR)
    else:
        print "Usge:python blfFilterColor.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #彩色双边滤波
    image = image.astype(np.float32)#注意首先转换为浮点型
    blfColorImage = blFilterColor(image,27,27,100,30)
    #显示结果
    blfColorImage = np.round(blfColorImage)
    blfColorImage = blfColorImage.astype(np.uint8)
    cv2.imshow("blfFilterColor",blfColorImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

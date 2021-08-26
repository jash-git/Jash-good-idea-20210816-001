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
    closeWeight = np.exp(-0.5*(np.power(r,2.0)+np.power(c,2.0))/math.pow(sigma_g,2.0))
    return closeWeight
def jointBLF(I,H,W,sigma_g,sigma_d,borderType=cv2.BORDER_DEFAULT):
    #构建空间距离的权重模板
    closenessWeight = getClosenessWeight(sigma_g,H,W)
    #对 I 进行高斯平滑
    Ig = cv2.GaussianBlur(I,(W,H),sigma_g)
    #模板的中心点位置
    cH = (H -1)/2
    cW = (W -1)/2
    #对原图和高斯平滑的结果扩充边界
    Ip=cv2.copyMakeBorder(I,cH,cH,cW,cW,borderType)
    Igp=cv2.copyMakeBorder(Ig,cH,cH,cW,cW,borderType)
    #图像矩阵的行数和列数
    rows,cols = I.shape
    i,j=0,0
    #联合双边滤波结果
    jblf = np.zeros(I.shape,np.float64)        
    for r in np.arange(cH,cH+rows,1):
        for c in np.arange(cW,cW+cols,1):
            #当前位置的值
            pixel = Igp[r][c]
            #当前位置的邻域
            rTop,rBottom = r-cH,r+cH
            cLeft,cRight = c-cW,c+cW
            #从 Igp 中截取该邻域，用于构建相似性权重
            region= Igp[rTop:rBottom+1,cLeft:cRight+1]
            #通过上述邻域,构建该位置的相似性权重模板
            similarityWeight = np.exp(-0.5*np.power(region -pixel,2.0)/math.pow(sigma_d,2.0))
            #相似性权重模板和空间距离权重模板形成
            weight = closenessWeight*similarityWeight
            #将权重模板归一化
            weight = weight/np.sum(weight)
            #权重模板和邻域对应位置相乘并求和
            jblf[i][j] = np.sum(Ip[rTop:rBottom+1,cLeft:cRight+1]*weight)
            j += 1
        j = 0
        i += 1
    return jblf
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        I = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python JointBilterFilter.py imageFile"
    #将 8 位图转换为 浮点型
    fI = I.astype(np.float64)
    #联合双边滤波，返回值的数据类型为浮点型
    jblf = jointBLF(fI,33,33,7,2)
    #转换为 8 位图
    jblf = np.round(jblf)
    jblf = jblf.astype(np.uint8)
    cv2.imshow("jblf",jblf)
    #保存结果
    #cv2.imwrite("jblf1.png",jblf)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
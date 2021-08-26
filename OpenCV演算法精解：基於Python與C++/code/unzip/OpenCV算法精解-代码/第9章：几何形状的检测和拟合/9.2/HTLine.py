# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
#霍夫极坐标变换：直线检测
def HTLine (image,stepTheta=1,stepRho=1):
    #宽、高
    rows,cols = image.shape
    #图像中可能出现的最大垂线的长度
    L =  round(math.sqrt(pow(rows-1,2.0)+pow(cols-1,2.0)))+1
    #初始化投票器
    numtheta = int(180.0/stepTheta)
    numRho = int(2*L/stepRho + 1)
    accumulator = np.zeros((numRho,numtheta),np.int32)
    #建立字典
    accuDict={}
    for k1 in xrange(numRho):
        for k2 in xrange(numtheta):
            accuDict[(k1,k2)]=[]
    #投票计数
    for y in xrange(rows):
        for x  in xrange(cols):
            if(image[y][x] == 255):#只对边缘点做霍夫变换
                for m in xrange(numtheta):
                    #对每一个角度，计算对应的 rho 值
                    rho = x*math.cos(stepTheta*m/180.0*math.pi)+y*math.sin(stepTheta*m/180.0*math.pi)
                    #计算投票哪一个区域
                    n = int(round(rho+L)/stepRho)
                    #投票加 1
                    accumulator[n,m] += 1
                    #记录该点
                    accuDict[(n,m)].append((x,y))
    return accumulator,accuDict
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        #输入图像
        I = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usage: python HTPLine.py image"
    #canny 边缘检测
    edge = cv2.Canny(I,50,200)
    #显示二值化边缘
    cv2.imshow("edge",edge)
    #霍夫直线检测
    accumulator,accuDict = HTLine(edge,1,1)
    #计数器的二维直方图方式显示
    rows,cols = accumulator.shape
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    X,Y = np.mgrid[0:rows:1, 0:cols:1]
    surf = ax.plot_wireframe(X,Y,accumulator,cstride=1, rstride=1,color='gray')
    ax.set_xlabel(u"$\\rho$")
    ax.set_ylabel(u"$\\theta$")
    ax.set_zlabel("accumulator")
    ax.set_zlim3d(0,np.max(accumulator))
    #计数器的灰度级显示
    grayAccu = accumulator/float(np.max(accumulator))
    grayAccu = 255*grayAccu
    grayAccu = grayAccu.astype(np.uint8)
    #只画出投票数大于 60 直线
    voteThresh = 60
    for r in xrange(rows):
        for c in xrange(cols):
            if accumulator[r][c] > voteThresh:
                points = accuDict[(r,c)]
                cv2.line(I,points[0],points[len(points)-1],(255),2)
    cv2.imshow('accumulator',grayAccu)
    
    #显示原图
    cv2.imshow("I",I)
    plt.show()
    cv2.imwrite('accumulator.jpg',grayAccu)
    cv2.imwrite('I.jpg',I)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

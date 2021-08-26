# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
#标准霍夫圆检测
def HTCircle (I,minR,maxR,voteThresh = 100):
    #宽、高
    H,W = I.shape
    #归为整数
    minr = round(minR)+1
    maxr = round(maxR)+1
    #初始化三维的计数器
    r_num = int(maxr-minr+1)
    a_num = int(W-1+maxr+maxr+1)
    b_num = int(H-1+maxr+maxr+1)
    accumulator = np.zeros((r_num,b_num,a_num),np.int32)
    #投票计数
    for y in xrange(H):
        for x  in xrange(W):
            if(I[y][x] == 255):#只对边缘点做霍夫变换
                for k in xrange(r_num):# r 变化的步长为 1 
                    for theta in np.linspace(0,360,360):
                        #计算对应的 a 和 b
                        a = x - (minr+k)*math.cos(theta/180.0*math.pi)
                        b = y - (minr+k)*math.sin(theta/180.0*math.pi)
                        #取整
                        a = int(round(a))
                        b = int(round(b))
                        #投票
                        accumulator[k,b,a]+=1
    #筛选投票数 大于 voteThresh的圆
    circles = []
    for k in xrange(r_num):
        for b in xrange(b_num):
            for a in xrange(a_num): 
                if(accumulator[k,b,a]>voteThresh):
                    circles.append((k+minr,b,a))
    return circles
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        #输入图像
        I = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usage: python HTCircle.py image"
    #canny 边缘检测
    edge = cv2.Canny(I,50,200)
    cv2.imshow("edge",edge)
    #霍夫圆检测
    circles = HTCircle(edge,60,80,80)
    #画圆
    for i in xrange(len(circles)):
        cv2.circle(I,(int(circles[i][2]),int(circles[i][1])),int(circles[i][0]),(255),2)
    cv2.imshow("I",I)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
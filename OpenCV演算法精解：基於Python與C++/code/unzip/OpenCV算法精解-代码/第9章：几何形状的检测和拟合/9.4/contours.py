# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        #输入图像
        img = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usage: python contours.py image"
    #边缘检测或阈值分割的二值化
    binaryImg = cv2.Canny(img,50,200)
    #寻找轮廓
    contours,h = cv2.findContours(binaryImg,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
    #打印 contoures 的类型
    print type(contours)
    # contours 是列表类型，打印每一元素的类型
    print type(contours[0])
    #打印轮廓（点集）个数
    print len(contours)
    #对这些点集，求每一个点集最小
    #最小外包凸包
    contoursImg = np.zeros(img.shape,np.uint8)
    cv2.drawContours(contoursImg,contours,7,255,3)
    circle = cv2.minEnclosingCircle(contours[7])
    cv2.circle(contoursImg,(int(circle[0][0]),int(circle[0][1])),int(circle[1]),255,2)
    convexhull = cv2.convexHull(contours[7])
    cv2.drawContours(contoursImg,contours,7,255,3)
    for i in xrange(len(contours)):
        # ----- 最小外包圆 -------
        circle = cv2.minEnclosingCircle(contours[i])
        #画圆
        #cv2.circle(img,(int(circle[0][0]),int(circle[0][1])),int(circle[1]),255,2)
        # ---- 最小直立矩形 ----
        rect = cv2.boundingRect(contours[i])
        #cv2.rectangle(img,(rect[0],rect[1]),(rect[2],rect[3]),255,2)
        # ---- 最小外包的旋转矩形 -----
        convexhull = cv2.convexHull(contours[i])
       
        
    #最小直立矩形
    cv2.imshow("img",img)
    #显示轮廓
    cv2.imshow("contoursImg",contoursImg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    


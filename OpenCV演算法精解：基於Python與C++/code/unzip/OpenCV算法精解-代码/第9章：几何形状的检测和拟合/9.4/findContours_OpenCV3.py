# -*- coding: utf-8 -*-
import cv2
import sys
import numpy as np
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        img = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    else:
        print "Usage findContours.py image"
    #第一步：阈值化，生成二值图
    #图像平滑
    dst = cv2.GaussianBlur(img,(3,3),0.5)
    # Otsu 阈值分割
    OtsuThresh = 0
    OtsuThresh,dst = cv2.threshold(dst,OtsuThresh,255,cv2.THRESH_OTSU)
    # --- 形态学开运算（ 消除细小白点 ）
    #创建结构元
    s = cv2.getStructuringElement(cv2.MORPH_RECT,(5,5))
    dst = cv2.morphologyEx(dst,cv2.MORPH_OPEN,s,iterations=2)
    #第二步：寻找二值图的轮廓，返回值是一个元组，hc[1] 代表轮廓
    hc= cv2.findContours(dst,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    contours = hc[1]
    #打印轮廓的属性
    print type(contours)
    #第三步：画出找到的轮廓并用多边形拟合轮廓
    #轮廓的数量
    n =  len(hc[1])
    #将轮廓画在该黑板上
    contoursImg = np.zeros(img.shape,np.uint8)
    for i in xrange(n):
        #画出轮廓
        cv2.drawContours(contoursImg,contours,i,255,2)
        #画出轮廓的最小外包圆
        circle = cv2.minEnclosingCircle(contours[i])
        cv2.circle(img,(int(circle[0][0]),int(circle[0][1])),int(circle[1]),0,5)
        #多边形逼近（注意与凸包区别）
        approxCurve = cv2.approxPolyDP(contours[i],0.3,True)
        #多边形顶点个数
        k = approxCurve.shape[0]
        #顶点连接，绘制多边形
        for i in xrange(k-1):
            cv2.line(img,(approxCurve[i,0,0],approxCurve[i,0,1]),(approxCurve[i+1,0,0],approxCurve[i+1,0,1]),0,5)
        #首尾相接
        cv2.line(img,(approxCurve[k-1,0,0],approxCurve[k-1,0,1]),(approxCurve[0,0,0],approxCurve[0,0,1]),0,5)
    #显示轮廓
    cv2.imshow("contours",contoursImg)
    #显示拟合的多边形
    cv2.imshow("dst",img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
# -*- coding: utf-8 -*-
import numpy as np
import cv2
import sys
#主函数
if __name__ =="__main__":
    #
    if len(sys.argv)>1:
        img = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usage draw.py image"
    #第二步：边缘检测 或者 阈值处理 生成一张二值图
    img = cv2.GaussianBlur(img,(3,3),0.5)#高斯平滑处理
    binaryImg = cv2.Canny(img,50,200)
    cv2.imshow("binaryImg",binaryImg)
    #第三步：边缘的轮廓，返回的 contours 是一个 list 列表
    contours, h= cv2.findContours(binaryImg,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    #轮廓的数量
    n =  len(contours)
    contoursImg = []
    #画出找到的轮廓
    for i in xrange(n):
        #创建一个黑色画布
        temp = np.zeros(binaryImg.shape,np.uint8)
        contoursImg.append(temp)
        #在第 i 个黑色画布上，画第 i 个轮廓
        cv2.drawContours(contoursImg[i],contours,i,255,2)
        cv2.imshow("contour-"+str(i),contoursImg[i])
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    
    
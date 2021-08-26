# -*- coding: utf-8 -*-
import numpy as np
import cv2
import sys
import math
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)#OpenCV2.X
        #image = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)#OpenCV3.X
    else:
        print "Usage: python warpAffine.py image"
    cv2.imwrite("img.jpg",image)
    #原图的高宽
    h,w=image.shape[:2]
    #仿射变换矩阵，缩小两倍
    A1 = np.array([[0.5,0,0],[0,0.5,0]],np.float32)
    d1 = cv2.warpAffine(image,A1,(w,h),borderValue=125)
    #先缩小两倍，再平移
    A2 = np.array([[0.5,0,w/4],[0,0.5,h/4]],np.float32)
    d2 = cv2.warpAffine(image,A2,(w,h),borderValue=125)
    #在 d2 的基础上，绕图像的中心点旋转
    A3 = cv2.getRotationMatrix2D((w/2,h/2),30,1)
    d3 = cv2.warpAffine(d2,A3,(w,h),borderValue=125)
    #在
    A4 = np.array([[math.cos(math.pi/4),0,0],[math.sin(math.pi/3),1,0]])
    d4 = cv2.warpAffine(image,A4,(2*w,2*h),borderValue=125)
    cv2.imshow("image",image)
    cv2.imshow("d1",d1)
    cv2.imshow("d2",d2)
    cv2.imshow("d3",d3)
    #cv2.imwrite("d3.jpg",d3)
    cv2.imshow("d4",d4)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
     
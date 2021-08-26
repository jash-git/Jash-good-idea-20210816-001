# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_COLOR)
    else:
        print "Usge:python RGB.py imageFile"
    #得到三个颜色通道
    b = image[:,:,0]
    g = image[:,:,1]
    r = image[:,:,2]
    #显示三个颜色通道
    cv2.imshow("b",b)
    cv2.imshow("g",g)
    cv2.imshow("r",r)
    #8位图转换为 浮点型
    fImg = image/255.0
    fb = fImg[:,:,0]
    fg = fImg[:,:,1]
    fr = fImg[:,:,2]
    #显示三个颜色
    cv2.imshow("fb",fb)
    cv2.imshow("fg",fg)
    cv2.imshow("fr",fr)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
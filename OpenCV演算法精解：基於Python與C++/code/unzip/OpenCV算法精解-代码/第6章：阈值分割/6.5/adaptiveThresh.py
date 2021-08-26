# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
def adaptiveThresh(I,winSize,ratio=0.15):
    #第一步：对图像矩阵进行均值平滑
    I_smooth = cv2.boxFilter(I,cv2.CV_32FC1,winSize)
    #I_smooth = cv2.medianBlur(I,winSize)
    #第二步：原图像矩阵与平滑结果做差
    out = I - (1.0-ratio)*I_smooth
    #第三步：对 out 进行全局阈值处理，差值大于等于零，输出值为255，反之为零
    out[out>=0] = 255
    out[out<0] = 0
    out = out.astype(np.uint8)
    return out
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python adaptiveThresh.py imageFile"
    out = adaptiveThresh(image,(31,31),0.15)
    cv2.imshow("out",out)
    cv2.imwrite("adTh.jpg",out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
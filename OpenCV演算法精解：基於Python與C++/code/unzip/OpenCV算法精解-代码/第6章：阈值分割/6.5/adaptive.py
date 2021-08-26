# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#图像积分
def integral(image):
    rows,cols = image.shape
    #行积分运算
    inteImageC = np.zeros(image.shape,np.float32)
    for r in xrange(rows):
        for c in xrange(cols):
            if c == 0:
                inteImageC[r][c] = image[r][c]
            else:
                inteImageC[r][c] = inteImageC[r][c-1] + image[r][c]
    #列积分运算
    inteImage = np.zeros(image.shape,np.float32)
    for c in xrange(cols):
        for r in xrange(rows):
            if r == 0:
                inteImage[r][c] = inteImageC[r][c]
            else:
                inteImage[r][c] = inteImage[r-1][c] + inteImageC[r][c]
    return inteImage
#阈值处理
def threshAdaptive(image,winSize,ratio):
    #图像的宽高
    rows,cols = image.shape
    #窗口的宽高
    winH,winW = winSize
    h = (winH-1)/2
    w = (winW-1)/2
    #阈值处理后的二值化图像
    threshImage = np.zeros(image.shape,np.uint8)
    #图像的积分
    inteImage = integral(image)
    for r in xrange(rows):
        for c in xrange(cols):
            # top left 
            tl_r = (r-h) if r-h > 0 else 0
            tl_c = (c-w) if c-w > 0 else 0
            #bottom right
            br_r = (r+h) if (r+h) < rows else rows -1
            br_c = (c+w) if (c+w) < cols else cols -1
            #计算区域和
            regionSum = inteImage[br_r][br_c] + inteImage[tl_r][tl_c] - inteImage[tl_r][br_c] - inteImage[br_r][tl_c]
            count = (br_r - tl_r + 1)*(br_c - tl_c + 1)
            if(image[r][c]*count < (1 - ratio)*regionSum):
                threshImage[r][c] = 0
            else:
                threshImage[r][c] = 255
    return threshImage
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python threshPun.py imageFile"
    threshImage = threshAdaptive(image,(41,41),0.15)
    #显示自适应阈值后二值化图像
    cv2.imshow("threshImage",threshImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
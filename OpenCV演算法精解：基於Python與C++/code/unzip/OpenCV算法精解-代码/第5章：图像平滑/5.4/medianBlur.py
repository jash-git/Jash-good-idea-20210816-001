# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#中值滤波 
def medianBlur(image,winSize):
    #图像的宽高
    rows,cols = image.shape
    #窗口的宽高，均为奇数
    winH,winW = winSize
    halfWinH = (winH-1)/2
    halfWinW = (winW-1)/2
    #中值滤波后的输出图像
    medianBlurImage = np.zeros(image.shape,image.dtype)
    for r in xrange(rows):
        for c in xrange(cols):
            #判断边界
            rTop = 0 if r-halfWinH < 0 else r-halfWinH
            rBottom = rows-1 if r+halfWinH > rows-1 else r+halfWinH
            cLeft = 0 if c-halfWinW < 0 else c-halfWinW
            cRight = cols-1 if c+halfWinW > cols-1 else c+halfWinW
            #取中值的区域
            region = image[rTop:rBottom+1,cLeft:cRight+1]
            #求中值
            medianBlurImage[r][c] = np.median(region)
    return medianBlurImage
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python medianBlur.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #中值滤波
    medianBlurImage = medianBlur(image,(3,3))
    #显示中值滤波后的结果
    cv2.imshow("medianBlurImage",medianBlurImage)
    cv2.imwrite("medianBlurImage.jpg",medianBlurImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
            
                        

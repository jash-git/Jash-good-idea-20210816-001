# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#图像积分
def integral(image):
    rows,cols = image.shape
    #行积分运算
    inteImageC = np.zeros((rows,cols),np.float32)
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
    #为了在快速均值平滑使用中省去判断边界的问题
    #上边和左边进行补零
    inteImage_0 = np.zeros((rows+1,cols+1),np.float32)
    inteImage_0[1:rows+1,1:cols+1] = inteImage
    return inteImage_0
#快速均值平滑：返回数组的数据类型是浮点型，winSize = ( 高，宽 )
def fastMeanBlur(image,winSize,borderType = cv2.BORDER_DEFAULT):
    halfH = (winSize[0]-1)/2
    halfW = (winSize[1]-1)/2
    ratio = 1.0/(winSize[0]*winSize[1])
    #边缘扩充
    paddImage = cv2.copyMakeBorder(image,halfH,halfH,halfW,halfW,borderType)
    #图像积分
    paddIntegral = integral(paddImage)
    #图像的宽高
    rows,cols = image.shape
    #均值滤波后的结果
    meanBlurImage = np.zeros(image.shape,np.float32)
    r,c = 0,0
    for h in range(halfH,halfH+rows,1):
        for w in range(halfW,halfW+cols,1):
            meanBlurImage[r][c] = (paddIntegral[h+halfH+1][w+halfW+1] + paddIntegral[h-halfH][w-halfW]
                                    -paddIntegral[h+halfH+1][w-halfW]-paddIntegral[h-halfH][w+halfW+1])*ratio
            c+=1
        r+=1
        c=0
    return meanBlurImage
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python fastMeanBlur.py imageFile"
    #快速均值平滑
    meanBlurImage = fastMeanBlur(image,(15,15),cv2.BORDER_DEFAULT)
    #数据类型转换
    meanBlurImage = np.round(meanBlurImage)
    meanBlurImage = meanBlurImage.astype(np.uint8)
    cv2.imshow("fastMeanBlur",meanBlurImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
        

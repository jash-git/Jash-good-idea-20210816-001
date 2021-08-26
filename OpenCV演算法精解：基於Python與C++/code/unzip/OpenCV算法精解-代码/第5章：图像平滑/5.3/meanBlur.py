# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy import signal
import cv2
#均值平滑
def meanBlur(image,H,W,_boundary='fill',_fillvalue=0):
    #H、W均不为零
    if H==0 or W==0:
        print 'W or H is not zero'
        return image
    
    #-------没有对均值平滑算子进行分离
    #meanKernel = 1.0/(H*W)*np.ones([H,W],np.float32)
    #result = signal.convolve2d(image,meanKernel,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    #-----卷积后进行数据类型转换,得到均值平滑的结果
    #result = result.astype(np.uint8)
    #return result
    
    #因为均值算子是可分离的卷积核，根据卷积运算的结合律
    #可以先进行水平方向的卷积，
    #再进行垂直方向的卷积
    #首先水平方向的均值平滑
    meanKernel_x = 1.0/W*np.ones([1,W],np.float32)
    i_conv_mk_x = signal.convolve2d(image,meanKernel_x,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    #然后对得到的水平卷积的结果再进行垂直方向的卷积
    meanKernel_y = 1.0/H*np.ones([H,1],np.float32)
    i_conv_xy = signal.convolve2d(i_conv_mk_x,meanKernel_y,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    i_conv_xy = np.round(i_conv_xy)
    #卷积后的结果进行数据类型转换，得到均值平滑的结果
    result = i_conv_xy.astype(np.uint8)
    return result

#主函数:示例
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python meanBlur.py imageFile"
    #均值滤波卷积核的宽高均设为 2*halfWinSize+1
    halfWinSize = 1
    MAX_HALFWINSIZE = 20
    cv2.namedWindow("meanBlur",1)
    #回调函数，均值滤波
    def callback_meanBlur(_halfWinSize):
        result = meanBlur(image,2*_halfWinSize+1,2*_halfWinSize+1,_boundary='symm',_fillvalue=0)
        cv2.imshow("meanBlur",result)
    callback_meanBlur(halfWinSize)
    cv2.createTrackbar("winSize/2","meanBlur",halfWinSize,MAX_HALFWINSIZE,callback_meanBlur)
    #
    latexImage = meanBlur(image,29,29,'symm')
    cv2.imwrite("latexImage.png",latexImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
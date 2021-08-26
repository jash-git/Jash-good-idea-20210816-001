# -*- coding: utf-8 -*-
import gaussKernel #导入构建高斯核的包
import sys
import numpy as np
from scipy import signal
import cv2
#高斯平滑，返回的数据类型为浮点型
def gaussBlur(image,sigma,H,W,_boundary = 'fill',_fillvalue = 0):
    '''
    #构建HxW的高斯平滑算子
    gaussKernelxy = gaussKernel.getGaussKernel(sigma,H,W)
    #图像矩阵和高斯卷积核卷积
    gaussBlur_xy = signal.convolve2d(image,gaussKernelxy,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    return gaussBlur_xy
    '''
    #因为高斯核是可分解的，根据卷积的结合律
    #先进行水平方向的卷积，然后再进行垂直方向的卷积
    gaussKenrnel_x = gaussKernel.getGaussKernel(sigma,1,W)
    gaussBlur_x = signal.convolve2d(image,gaussKenrnel_x,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    gaussKenrnel_y = gaussKernel.getGaussKernel(sigma,H,1)
    gaussBlur_xy = signal.convolve2d(gaussBlur_x,gaussKenrnel_y,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    return gaussBlur_xy
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python gaussBlur.py imageFile"
    cv2.imshow("image",image)
    cv2.imwrite("img4.jpg",image)
    # 3 11 11 9 25 25
    blurImage = gaussBlur(image,5,51,51,'symm')
    #如果输入的图像是8位图,输出的
    blurImage = np.round(blurImage)
    blurImage = blurImage.astype(np.uint8)
    cv2.imshow("gaussBlur",blurImage)
    cv2.imwrite("gaussBlur.png",blurImage)
    #如果输入的图像数据类型是浮点型，且像素值归一到[0,1]
    image_0_1 = image/255.0
    blurImage_0_1 = gaussBlur(image_0_1,4,5,5,'symm')
    #cv2.imshow("gaussBlur-0-1",blurImage_0_1)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
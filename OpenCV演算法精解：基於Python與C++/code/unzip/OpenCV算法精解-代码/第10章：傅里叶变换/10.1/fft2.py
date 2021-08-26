# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#快速傅里叶变换
def fft2Image(src):
    #得到行、列
    r,c = src.shape[:2]
    #得到快速傅里叶变换最优扩充
    rPadded = cv2.getOptimalDFTSize(r)
    cPadded = cv2.getOptimalDFTSize(c)
    #边缘扩充，下边缘和右边缘扩充值为零
    fft2 = np.zeros((rPadded,cPadded,2),np.float32)
    fft2[:r,:c,0]=src
    #快速傅里叶变换
    cv2.dft(fft2,fft2,cv2.DFT_COMPLEX_OUTPUT)
    return fft2
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python fft2.py imageFile"
    #计算图像矩阵的快速傅里叶变换
    fft2 = fft2Image(image)
    #傅里叶逆变换
    ifft2 = np.zeros(fft2.shape[:2],np.float32)
    cv2.dft(fft2,ifft2,cv2.DFT_REAL_OUTPUT + cv2.DFT_INVERSE + cv2.DFT_SCALE)
    #裁剪
    img = np.copy(ifft2[:image.shape[0],:image.shape[1]])
    #裁剪后的结果 img 等于 image，两个相减的最大值为零
    print np.max(image - img)
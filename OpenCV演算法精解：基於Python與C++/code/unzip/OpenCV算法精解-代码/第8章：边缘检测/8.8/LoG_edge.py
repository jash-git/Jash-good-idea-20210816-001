# -*- coding: utf-8 -*-
import sys
import numpy as np
import math
import cv2
from scipy import signal
#构建 LoG 算子
def createLoGKernel(sigma,kSize):
    # LoG 算子的宽高，且两者均为奇数
    winH,winW = kSize
    logKernel = np.zeros(kSize,np.float32)
    #方差
    sigmaSquare = pow(sigma,2.0)
    # LoG 算子的中心
    centerH = (winH-1)/2
    centerW = (winW-1)/2
    for r in xrange(winH):
        for c in xrange(winW):
            norm2 = pow(r-centerH,2.0) + pow(c-centerW,2.0)
            logKernel[r][c] = 1.0/sigmaSquare*(norm2/sigmaSquare - 2)*math.exp(-norm2/(2*sigmaSquare))
    return logKernel
#高斯拉普拉斯卷积，一般取 _boundary = 'symm'
def LoG(image,sigma,kSize,_boundary='fill',_fillValue = 0):
    #构建 LoG 卷积核
    loGKernel = createLoGKernel(sigma,kSize)
    #图像与 LoG 卷积核卷积
    img_conv_log = signal.convolve2d(image,loGKernel,'same',boundary =_boundary)
    return img_conv_log
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python LoG.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #高斯拉普拉斯卷积
    img_conv_log = LoG(image,2,(13,13),'symm')
    #边缘的二值化显示
    edge_binary = np.copy(img_conv_log)
    edge_binary[edge_binary>=0]=0
    edge_binary[edge_binary<0]=255
    edge_binary = edge_binary.astype(np.uint8)
    cv2.imshow("edge_binary",edge_binary)
    cv2.imwrite("edge1_binary_37_6.jpg",edge_binary)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
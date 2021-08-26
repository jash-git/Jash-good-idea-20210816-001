# -*- coding: utf-8 -*-
import sys
import cv2
import numpy as np
from scipy import signal
def createLoGKernel(sigma,size):
    # LoG 算子的高和宽，且两者均为奇数
    H,W = size
    r,c = np.mgrid[0:H:1,0:W:1]
    r-=(H-1)/2
    c-=(W-1)/2
    #方差
    sigma2 = pow(sigma,2.0)
    # LoG 核
    norm2 = np.power(r,2.0)+np.power(c,2.0)
    #LoGKernel=1.0/sigma2*(norm2/sigma2 -2)*np.exp(-norm2/(2*sigma2))
    LoGKernel=(norm2/sigma2 -2)*np.exp(-norm2/(2*sigma2))
    return LoGKernel
def LoG(image,sigma,size,_boundary='symm'):
    #构建 LoG 卷积核
    loGKernel = createLoGKernel(sigma,size)
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
    img_conv_log = LoG(image,6,(37,37),'symm')
    #边缘的二值化显示
    edge_binary = np.copy(img_conv_log)
    edge_binary[edge_binary>0]=255
    edge_binary[edge_binary<=0]=0
    edge_binary = edge_binary.astype(np.uint8)
    cv2.imshow("edge_binary",edge_binary)
    #cv2.imwrite("edge1_binary_37_6.jpg",edge_binary)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
import math
'''
    得到高斯平滑算子：
    getGaussKernel(sigma,H,W),使用过程中一般H和W一般为奇数，sigma大于零
'''

def getGaussKernel(sigma,H,W):
    '''
        第一步：构建高斯矩阵gaussMatrix
    '''
    gaussMatrix = np.zeros([H,W],np.float32)
    #得到中心点的位置
    cH = (H-1)/2
    cW = (W-1)/2
    #计算1/(2*pi*sigma^2)
    coefficient = 1.0/(2*np.pi*math.pow(sigma,2))
    #
    for r in xrange(H):
        for c in xrange(W):
            norm2 = math.pow(r-cH,2) + math.pow(c-cW,2)
            gaussMatrix[r][c] = coefficient*math.exp(-norm2/(2*math.pow(sigma,2)))
    '''
        第二步：计算高斯矩阵的和
    '''
    sumGM = np.sum(gaussMatrix)
    '''
        第三步：归一化，gaussMatrix/sumGM
    '''
    gaussKernel = gaussMatrix/sumGM
    return gaussKernel
#主函数
if __name__ =="__main__":
    gaussKernel = getGaussKernel(2,3,3)
    print gaussKernel
    #高斯核gaussKernel是可分解的，可以分解为水平方向和垂直方向的卷积核
    gaussKernel_x = getGaussKernel(2,1,3)
    print gaussKernel_x
    gaussKernel_y = getGaussKernel(2,3,1)
    print gaussKernel_y
    '''
    水平方向和垂直方向的卷积核进行卷积运算,注意：mode='full',boundary = 'fill',fillvalue=0
    这样的参数设置，得到的结果才和gaussKernel完全相等，否则，边界不相等
    '''
    gaussKernel_xy = signal.convolve2d(gaussKernel_x,gaussKernel_y,mode='full',boundary ='fill',fillvalue=0)
    print gaussKernel_xy
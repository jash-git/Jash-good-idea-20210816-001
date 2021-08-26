# -*- coding: utf-8 -*-
import sys
import cv2
import numpy as np
from fastMeanBlur import fastMeanBlur#导入快速均值平滑
#快速导向滤波，输入的图像数据类型为归一到[0,1]的浮点型
#s属于(0,1] ,
#建议 r>=4, 1/r=<s<=4/r 
def fastGuidedFilter(I,p,r,eps,s):
    #输入图像的宽高
    rows,cols = I.shape
    #缩小图像
    small_I = cv2.resize(I,dsize=(int(round(s*cols)),int(round(s*rows))),interpolation=cv2.INTER_CUBIC)
    small_p = cv2.resize(p,dsize=(int(round(s*cols)),int(round(s*rows))),interpolation=cv2.INTER_CUBIC)
    #缩放均值平滑的窗口半径
    small_r = int(round(r*s))#确保是整型
    winSize = (2*small_r+1,2*small_r+1)
    # small_I 的均值平滑
    mean_small_I = fastMeanBlur(small_I,winSize,cv2.BORDER_DEFAULT)
    # small_p 的均值平滑
    mean_small_p = fastMeanBlur(small_p,winSize,cv2.BORDER_DEFAULT)
    # small_I.*small_p 的均值平滑
    small_Ip = small_I*small_p
    mean_small_Ip = fastMeanBlur(small_Ip,winSize,cv2.BORDER_DEFAULT)
    #协方差
    cov_small_Ip = mean_small_Ip - mean_small_I*mean_small_p
    mean_small_II = fastMeanBlur(small_I*small_I,winSize,cv2.BORDER_DEFAULT)
    #方差
    var_small_I = mean_small_II - mean_small_I*mean_small_I
    small_a = cov_small_Ip/(var_small_I+eps)
    small_b = mean_small_p - small_a*mean_small_I
    #对 small_a 和 small_b 进行均值平滑
    mean_small_a = fastMeanBlur(small_a,winSize,cv2.BORDER_DEFAULT)
    mean_small_b = fastMeanBlur(small_b,winSize,cv2.BORDER_DEFAULT)
    #放大 small_a 和 small_b
    mean_a = cv2.resize(mean_small_a,dsize=(cols,rows),interpolation=cv2.INTER_LINEAR)
    mean_b = cv2.resize(mean_small_b,dsize=(cols,rows),interpolation=cv2.INTER_LINEAR)
    q = mean_a*I + mean_b
    return q
#彩色快速导向滤波（平滑）
def fGFColorSmooth(I,r,eps,s):
    q_color = np.zeros(I.shape,np.float64)
    #对每一个通道进行导向滤波
    for c in xrange(3):
        q_color[:,:,c] = fastGuidedFilter(I[:,:,c],I[:,:,c],r,eps,s)
    return q_color
#细节增强
def fGFEnchance(I,r,eps,s):
    #导向平滑处理
    qColor = fGFColorSmooth(I,r,eps,s)
    #细节增强处理
    enchanced = (I - qColor)*5 + qColor
    '''
    for c in xrange(3):
        enchanced[:,:,c] = cv2.normalize(enchanced[:,:,c],alpha = 1,beta = 0,norm_type = cv2.NORM_MINMAX)
    '''
    enchanced = cv2.normalize(enchanced,alpha = 1,beta = 0,norm_type = cv2.NORM_MINMAX)
    return enchanced
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1: 
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_COLOR)
    else:
        print "Usge:python fastGuidedFilter.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #快速导向滤波（彩色图像平滑）
    image_0_1 = image/255.0
    result = fGFColorSmooth(image_0_1,5,pow(0.1,2.0),1.0/3)
    cv2.imshow("fastGuidedFilter",result)
    #细节增强
    enchanced = fGFEnchance(image_0_1,5,pow(0.2,2.0),1.0/3)
    cv2.imshow("fGFEnchance",enchanced)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy import signal
import cv2
#prewtt卷积
def prewitt(I,_boundary='symm',):
    #因为prewitt_X是可分离卷积核,根据卷积运算的结合律,可以分两次小卷积核运算
    #1：垂直方向的 " 均值平滑 "
    ones_y = np.array([[1],[1],[1]],np.float32)
    i_conv_pre_x = signal.convolve2d(I,ones_y,mode='same',boundary = _boundary)
    #2：水平方向的差分
    diff_x = np.array([[1,0,-1]],np.float32)
    i_conv_pre_x = signal.convolve2d(i_conv_pre_x,diff_x,mode='same',boundary = _boundary)
    #因为prewitt_y是可分离卷积核，根据卷积运算的结合律，可以分两次小卷积核运算
    #1：水平方向的"均值平滑 "
    ones_x = np.array([[1,1,1]],np.float32)
    i_conv_pre_y = signal.convolve2d(I,ones_x,mode='same',boundary = _boundary)
    #2：垂直方向的差分
    diff_y = np.array([[1],[0],[-1]],np.float32)
    i_conv_pre_y = signal.convolve2d(i_conv_pre_y,diff_y,mode='same',boundary = _boundary)
    return (i_conv_pre_x,i_conv_pre_y)
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python prewitt.py imageFile"   
    #图像矩阵 和 两个 prewitt算子 的卷积
    i_conv_pre_x,i_conv_pre_y = prewitt(image)
    #取绝对值,分别得到水平方向和垂直方向的边缘强度
    abs_i_conv_pre_x = np.abs(i_conv_pre_x)
    abs_i_conv_pre_y = np.abs(i_conv_pre_y)    
    #水平方向和垂直方向的边缘强度的灰度级显示
    edge_x = abs_i_conv_pre_x.copy()
    edge_y = abs_i_conv_pre_y.copy()
    edge_x[edge_x>255]=255
    edge_y[edge_y>255]=255
    edge_x = edge_x.astype(np.uint8)
    edge_y = edge_y.astype(np.uint8)
    cv2.imshow("edge_x",edge_x)
    cv2.imwrite("edge_x.jpg",edge_x)
    cv2.imshow("edge_y",edge_y)
    cv2.imwrite("edge_y.jpg",edge_y)
    #利用 abs_i_conv_pre_x 和 abs_i_conv_pre_y 求最终的边缘强度
    #求边缘强度，有多重方式，这里使用的是插值法
    edge = 0.5*abs_i_conv_pre_x + 0.5*abs_i_conv_pre_y
    #边缘强度的灰度级显示
    edge[edge>255]=255
    edge = edge.astype(np.uint8)
    cv2.imshow('edge',edge)
    cv2.imwrite("edge.jpg",edge)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
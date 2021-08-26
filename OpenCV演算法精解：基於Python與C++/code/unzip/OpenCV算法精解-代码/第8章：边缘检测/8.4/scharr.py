# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy import signal
import cv2
def scharr(I,_boundary='symm'):
    # I 与 scharr_x 的 same 卷积
    scharr_x = np.array([[3,0,-3],[10,0,-10],[3,0,-3]],np.float32)
    I_x = signal.convolve2d(I,scharr_x,mode='same',boundary='symm')
    # I 与 scharr_y 的same 卷积
    scharr_y = np.array([[3,10,3],[0,0,0],[-3,-10,-3]],np.float32)
    I_y = signal.convolve2d(I,scharr_y,mode='same',boundary='symm')
    return (I_x,I_y)
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python scharr.py imageFile"
    #求卷积
    i_conv_sch_x = scharr(image,1,0,_boundary='symm')
    i_conv_sch_y = scharr(image,0,1,_boundary='symm')
    #取绝对值,分别得到水平方向和垂直方向的边缘强度
    abs_i_conv_sch_x = np.abs(i_conv_sch_x)
    abs_i_conv_sch_y = np.abs(i_conv_sch_y)    
    #水平方向和垂直方向的边缘强度的灰度级显示
    edge_x = abs_i_conv_sch_x.copy()
    edge_y = abs_i_conv_sch_y.copy()
    edge_x[edge_x>255]=255
    edge_y[edge_y>255]=255
    edge_x = edge_x.astype(np.uint8)
    edge_y = edge_y.astype(np.uint8)
    cv2.imshow("edge_x",edge_x)
    cv2.imshow("edge_y",edge_y)
    cv2.imwrite("edge_x.jpg",edge_x)
    cv2.imwrite("edge_y.jpg",edge_y)
    #根据水平方向和垂直方向的边缘强度,求最终的边缘强度
    #有多种方式，这里使用平方根形式
    edge = np.sqrt(np.power(abs_i_conv_sch_x,2)+np.power(abs_i_conv_sch_y,2))
    #最终的边缘强度的灰度级显示
    edge[edge>255]=255
    edge = np.round(edge)
    edge = edge.astype(np.uint8)
    cv2.imshow('edge',edge)
    cv2.imwrite("edge.jpg",edge)
    #经过阈值处理的边缘显示
    cv2.namedWindow("thresh_edge",1)
    MAX_THRESH = 255
    thresh = 255
    #回调函数，阈值处理
    def callback_thresh(_thresh):
        threshEdge = edge.copy()
        threshEdge[threshEdge < _thresh] = 0
        threshEdge[threshEdge >= _thresh] = 255
        cv2.imshow("thresh_edge",threshEdge)
        cv2.imwrite("thresh_edge.jpg",threshEdge)
    callback_thresh(thresh)
    cv2.createTrackbar("thresh","thresh_edge",thresh,MAX_THRESH,callback_thresh)
    #模拟铅笔素描
    pencilSketch = edge.copy()
    pencilSketch = 255 - pencilSketch
    pencilSketch[pencilSketch < 100] = 100
    cv2.imshow("pencilSketch",pencilSketch)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
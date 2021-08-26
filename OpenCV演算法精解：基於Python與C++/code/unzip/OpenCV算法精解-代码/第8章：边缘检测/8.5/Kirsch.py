# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy import signal
import cv2
'''
    Krisch边缘检测算法:
    krisch(image,_boundary='fill',_fillvalue=0)
    其中:边缘处理的方式_boundary包括：'symm','wrap','fill',
    且当__boundary='fill'时,填充值默认为零_fillvalue=0
'''
def krisch(image,_boundary='fill',_fillvalue=0):
    '''
    第一步:8个krisch边缘卷积算子分别和图像矩阵进行卷积,然后分别取绝对值得到边缘强度
    '''
    #存储8个方向的边缘强度
    list_edge=[]
    #图像矩阵和k1进行卷积,然后取绝对值（即:得到边缘强度）
    k1 = np.array([[5,5,5],[-3,0,-3],[-3,-3,-3]])
    image_k1 = signal.convolve2d(image,k1,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k1))
    #图像矩阵和k2进行卷积,然后取绝对值（即:得到边缘强度）
    k2 = np.array([[-3,-3,-3],[-3,0,-3],[5,5,5]])
    image_k2 = signal.convolve2d(image,k2,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k2))
    #图像矩阵和k3进行卷积,然后取绝对值（即:得到边缘强度）
    k3 = np.array([[-3,5,5],[-3,0,5],[-3,-3,-3]])
    image_k3 = signal.convolve2d(image,k3,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k3))
    #图像矩阵和k4进行卷积,然后取绝对值（即:得到边缘强度）
    k4 = np.array([[-3,-3,-3],[5,0,-3],[5,5,-3]])
    image_k4 = signal.convolve2d(image,k4,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k4))
    #图像矩阵和k5进行卷积,然后取绝对值（即:得到边缘强度）
    k5 = np.array([[-3,-3,5],[-3,0,5],[-3,-3,5]])
    image_k5 = signal.convolve2d(image,k5,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k5))
    #图像矩阵和k6进行卷积,然后取绝对值（即:得到边缘强度）
    k6 = np.array([[5,-3,-3],[5,0,-3],[5,-3,-3]])
    image_k6 = signal.convolve2d(image,k6,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k6))
    #图像矩阵和k7进行卷积,然后取绝对值（即:得到边缘强度）
    k7 = np.array([[-3,-3,-3],[-3,0,5],[-3,5,5]])
    image_k7 = signal.convolve2d(image,k7,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k7))
    #图像矩阵和k8进行卷积,然后取绝对值（即:得到边缘强度）
    k8 = np.array([[5,5,-3],[5,0,-3],[-3,-3,-3]])
    image_k8 = signal.convolve2d(image,k8,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    list_edge.append(np.abs(image_k8))
    '''
    第二步：对上述8个方向的边缘强度,对应位置取最大值，作为图像最后的边缘强度
    '''
    edge = list_edge[0]
    for i in xrange(len(list_edge)):
        edge = edge*(edge>=list_edge[i]) + list_edge[i]*(edge < list_edge[i])
    return edge

#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python krisch.py imageFile"
    edge = krisch(image,_boundary='symm')
    #边缘强度的灰度级显示
    rows,cols = edge.shape
    for r in xrange(rows):
        for c in xrange(cols):
            if edge[r][c] >255:
                edge[r][c] = 255
    edge = edge.astype(np.uint8)
    cv2.imshow("edge",edge)
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
    #模拟素描
    pencilSketch = edge.copy()
    pencilSketch = 255 - pencilSketch
    pencilSketch[pencilSketch<50] = 50
    cv2.imshow("pencilSketch",pencilSketch)
    cv2.imwrite("pencilSketch.jpg",pencilSketch)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
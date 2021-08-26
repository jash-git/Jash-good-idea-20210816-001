# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy import signal
import cv2
import math
from gaussBlur import gaussBlur#高斯平滑
'''
    laplacian 边缘检测算法:
    laplacian(image,_boundary='fill',_fillvalue=0)
    其中：边缘处理的方式_boundary包括：'symm','wrap','fill',
    且当__boundary='fill'时，填充值默认为零_fillvalue=0
'''
def laplacian(image,_boundary='fill',_fillvalue=0):
    #拉普拉斯卷积核
    #laplacianKernel = np.array([[0,-1,0],[-1,4,-1],[0,-1,0]],np.float32)
    laplacianKernel = np.array([[-1,-1,-1],[-1,8,-1],[-1,-1,-1]],np.float32)
    #图像矩阵和拉普拉斯算子卷积
    i_conv_lap = signal.convolve2d(image,laplacianKernel,mode='same',boundary = _boundary,fillvalue=_fillvalue)
    return i_conv_lap
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python laplacian.py imageFile"
    #显示原图
    cv2.imshow("image.jpg",image)
    cv2.imwrite("image.jpg",image)
    # ----- 第一种情形 ------
    #图像矩阵和拉普拉斯核进行卷积，然后进行阈值处理
    i_conv_lap = laplacian(image,'symm')
    i_conv_lap_copy = np.copy(i_conv_lap)
    #i_conv_lap_copy[i_conv_lap_copy>0] = 255
    #i_conv_lap_copy[i_conv_lap_copy<=0] = 150
    i_conv_lap_copy = np.abs(i_conv_lap_copy)
    i_conv_lap_copy += 125
    i_conv_lap_copy[i_conv_lap_copy>255]=255
    i_conv_lap_copy = i_conv_lap_copy.astype(np.uint8)
    cv2.imshow("i_conv_lap",i_conv_lap_copy)
    cv2.imwrite("i_cov_lap.jpg",i_conv_lap_copy)
    #第五种情形
    
    # ---- 第二种情形 ------
    #对卷积结果取绝对值
    i_conv_lap_abs = np.abs(i_conv_lap)
    i_conv_lap_abs = np.round(i_conv_lap_abs)
    i_conv_lap_abs[i_conv_lap_abs>255]=255
    i_conv_lap_abs = i_conv_lap_abs.astype(np.uint8)
    cv2.imshow("i_conv_lap_abs",i_conv_lap_abs)
    #cv2.imwrite("i_cov_lap_abs.jpg",i_conv_lap_abs)
    # ---- 第三种情形 -----
    #先对图像进行高斯平滑，再进行拉普拉斯卷积，然后阈值处理
    imageBlur = gaussBlur(image,3,19,19,'symm')
    imageBlur_conv_lap = laplacian(imageBlur,'symm')
    threshEdge = np.copy(imageBlur_conv_lap)
    threshEdge = np.abs(threshEdge)
    threshEdge[threshEdge>255] = 255
    #threshEdge[threshEdge>0] = 255
    #threshEdge[threshEdge<=0] = 0
    threshEdge = threshEdge.astype(np.uint8)
    cv2.imshow("threshEdge",threshEdge)
    cv2.imwrite("threshEdge.jpg",threshEdge)
    # ---- 第四种情形 ----
    #图像抽象化
    rows,cols = imageBlur_conv_lap.shape
    imageAbstraction = np.copy(imageBlur_conv_lap)
    for r in xrange(rows):
        for c in xrange(cols):
            if imageAbstraction[r][c] > 0:
                imageAbstraction[r][c] = 1
            else:
                imageAbstraction[r][c] = 1+math.tanh(imageAbstraction[r][c])
    cv2.imshow("imageAbstraction",imageAbstraction)
    #转换为 8 位图，保存结果
    imageAbstraction = 255*imageAbstraction
    imageAbstraction = np.round(imageAbstraction)
    imageAbstraction = imageAbstraction.astype(np.uint8)
    cv2.imwrite("imageAbstraction.jpg",imageAbstraction)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

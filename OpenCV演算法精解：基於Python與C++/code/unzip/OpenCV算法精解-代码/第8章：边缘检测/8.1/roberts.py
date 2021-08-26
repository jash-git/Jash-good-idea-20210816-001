# -*- coding: utf-8 -*-
import sys
import numpy as np
from scipy import signal
import cv2
def roberts(I,_boundary='fill',_fillvalue=0):
    #图像的高、宽
    H1,W1=I.shape[0:2]
    #卷积核的尺寸
    H2,W2=2,2
    #卷积核 1 及 锚点的位置
    R1 = np.array([[1,0],[0,-1]],np.float32)
    kr1,kc1=0,0
    #计算 fuLl 卷积
    IconR1 = signal.convolve2d(I,R1,mode='full',boundary = _boundary,fillvalue=_fillvalue)
    IconR1=IconR1[H2-kr1-1:H1+H2-kr1-1,W2-kc1-1:W1+W2-kc1-1]
    #卷积核2
    R2 = np.array([[0,1],[-1,0]],np.float32)
    #先计算 full 卷积
    IconR2 = signal.convolve2d(I,R2,mode='full',boundary = _boundary,fillvalue=_fillvalue)
    #锚点的位置
    kr2,kc2 = 0,1
    #根据锚点的位置，截取 full卷积，从而得到 same 卷积
    IconR2=IconR2[H2-kr2-1:H1+H2-kr2-1,W2-kc2-1:W1+W2-kc2-1]
    return (IconR1,IconR2)
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python roberts.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #卷积，注意边界扩充一般采用 " symm "
    IconR1,IconR2 = roberts(image,'symm')
    #45度方向上的边缘强度的灰度级显示
    IconR1 = np.abs(IconR1)
    edge_45 = IconR1.astype(np.uint8)
    cv2.imshow("edge_45",edge_45)
    cv2.imwrite("img3_robert_135_edge.jpg",edge_45)
    #135度方向上的边缘强度
    IconR2 = np.abs(IconR2)
    edge_135 = IconR2.astype(np.uint8)
    cv2.imshow("edge_135",edge_135)
    cv2.imwrite("img3_robert_45_edge.jpg",edge_135)
    #用平方和的开方衡量最后的输出边缘
    edge = np.sqrt(np.power(IconR1,2.0) + np.power(IconR2,2.0))
    edge = np.round(edge)
    edge[edge>255] = 255
    edge = edge.astype(np.uint8)
    #显示边缘
    cv2.imshow("edge",edge)
    cv2.imwrite("img3_robert_edge.jpg",edge)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
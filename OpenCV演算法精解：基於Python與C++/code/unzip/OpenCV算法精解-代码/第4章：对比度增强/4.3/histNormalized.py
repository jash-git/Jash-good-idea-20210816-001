# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import matplotlib.pyplot as plt
#直方图正规化
#1、若输入是 8 位图 ，一般设置 O_min = 0，O_max = 255
#2、若输入的是归一化的图像，一般设置 O_min = 0，O_max = 1
def histNormalized(InputImage,O_min = 0,O_max = 255):
    #得到输入图像的最小灰度值
    I_min = np.min(InputImage)
    #得到输入图像的最大灰度值
    I_max = np.max(InputImage)
    #得到输入图像的宽高
    rows,cols = InputImage.shape
    #输出图像
    OutputImage = np.zeros(InputImage.shape,np.float32)
    #输出图像的映射
    cofficient = float(O_max - O_min)/float(I_max - I_min)
    for r in xrange(rows):
        for c in xrange(cols):
            OutputImage[r][c] = cofficient*( InputImage[r][c] - I_min) + O_min
    return OutputImage
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python histNormalized.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #直方图正规化
    histNormResult = histNormalized(image)
    #数据类型转换，灰度级显示
    histNormResult = np.round(histNormResult)
    histNormResult = histNormResult.astype(np.uint8)
    #显示直方图正规化的图片
    cv2.imshow("histNormlized",histNormResult)
    cv2.imwrite("histNormResult.jpg",histNormResult)
    '''
    #如果输入图像是归一化的图像
    image_0_1 = image/255.0
    #直方图正规化
    histNormResult = histNormalized(image_0_1,0,1)
    #保存结果
    histNormResult = 255.0*histNormResult
    histNormResult = np.round(histNormResult)
    histNormResult = histNormResult.astype(np.uint8)
    '''
    #显示直方图正规化后图片的灰度直方图
    #组数
    numberBins = 256
    #计算灰度直方图
    rows,cols = image.shape
    histNormResultSeq = histNormResult.reshape([rows*cols,])
    histogram,bins,patch_image= plt.hist(histNormResultSeq,numberBins,facecolor='black',histtype='bar')
    #设置坐标轴的标签
    plt.xlabel(u"gray Level")
    plt.ylabel(u"number of pixels")
    #设置坐标轴的范围
    y_maxValue = np.max(histogram)
    plt.axis([0,255,0,y_maxValue])
    plt.show()
    cv2.waitKey(0)
    cv2.destroyAllWindows()
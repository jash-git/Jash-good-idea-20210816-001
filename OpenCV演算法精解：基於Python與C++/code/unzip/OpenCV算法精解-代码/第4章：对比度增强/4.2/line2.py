# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import matplotlib.pyplot as plt
#分段线性变换
def piecewiseLinear(image,point1,point2):
    #确保 point1 在 point2的左下角
    x1,y1 = point1
    x2,y2 = point2
    # 0 - point1.x
    a1 = float(y1)/x1
    b1 = 0
    # point1.x - point2.x
    a2 = float(y2-y1)/float(x2-x1)
    b2 = y1 - a2*x1
    print a2
    #point2.x - 255
    a3 = float(255 - y2)/(255-x2)
    b3 = 255 - a3*255
    #输出图像
    outPutImage = np.zeros(image.shape,np.uint8)
    #图像的宽高
    rows,cols = image.shape
    for r in xrange(rows):
        for c in xrange(cols):
            pixel = image[r][c]
            if pixel <= x1:
                outPixel = a1*pixel + b1
            elif pixel>x1 and pixel < x2:
                outPixel = a2*pixel + b2
            else:
                outPixel = a3*pixel + b3
            outPixel = round(outPixel)
            outPutImage[r][c] = outPixel
    return outPutImage
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    else:
        print "Usge:python piecewiseLinear.py imageFile"
    cv2.imshow("image",image)
    #分段线性变换
    outPutImage = piecewiseLinear(image,(100,50),(150,230))
    cv2.imshow("outPutImage",outPutImage)
    #保存变换后的图片
    cv2.imwrite("outPutImage.jpg",outPutImage)
    #显示直方图正规化后图片的灰度直方图
    #组数
    numberBins = 256
    #计算灰度直方图
    rows,cols = outPutImage.shape
    histSeq = outPutImage.reshape([rows*cols,])
    histogram,bins,patch_image= plt.hist(histSeq,numberBins,facecolor='black',histtype='bar')
    #设置坐标轴的标签
    plt.xlabel(u"gray Level")
    plt.ylabel(u"number of pixels")
    #设置坐标轴的范围
    y_maxValue = np.max(histogram)
    print y_maxValue
    plt.axis([0,255,0,y_maxValue])
    plt.show()
    cv2.waitKey(0)
    cv2.destroyAllWindows()
        
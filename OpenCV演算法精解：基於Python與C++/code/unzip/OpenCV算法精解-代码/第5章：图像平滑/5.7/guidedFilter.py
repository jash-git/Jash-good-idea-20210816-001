# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
from fastMeanBlur import fastMeanBlur
#导向滤波
def guidedFilter(I,p,winSize,eps):
    #输入图像的宽高
    rows,cols = I.shape
    # I 的均值平滑
    mean_I = fastMeanBlur(I,winSize,cv2.BORDER_DEFAULT)
    # p 的均值平滑
    mean_p = fastMeanBlur(p,winSize,cv2.BORDER_DEFAULT)
    # I.*p 的均值平滑
    Ip = I*p
    mean_Ip = fastMeanBlur(Ip,winSize,cv2.BORDER_DEFAULT)
    #协方差
    cov_Ip = mean_Ip - mean_I*mean_p
    mean_II = fastMeanBlur(I*I,winSize,cv2.BORDER_DEFAULT)
    #方差
    var_I = mean_II - mean_I*mean_I
    a = cov_Ip/(var_I+eps)
    b = mean_p - a*mean_I
    # 对 a 和 b进行均值平滑
    mean_a = fastMeanBlur(a,winSize,cv2.BORDER_DEFAULT)
    mean_b = fastMeanBlur(b,winSize,cv2.BORDER_DEFAULT)
    q = mean_a*I + mean_b
    return q
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python guidedFilter.py imageFile"
    #将图像归一化
    image_0_1 = image/255.0
    #显示原图
    cv2.imshow("image",image)
    #导向滤波
    result = guidedFilter(image_0_1,image_0_1,(17,17),pow(0.2,2.0))
    cv2.imshow("guidedFilter",result)
    #保存导向滤波的结果
    result = result*255
    result[result>255] = 255
    result = np.round(result)
    result = result.astype(np.uint8)
    cv2.imwrite("guidedFilter.jpg",result)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
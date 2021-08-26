# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
    #第一步：读入图像
        src = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    else:
        print "Usge:python CLAHE.py imageFile"
    #创建 CLAHE  对象
    clahe = cv2.createCLAHE(clipLimit=1.0,tileGridSize=(28,28))
    #限制对比度的自适应阈值均衡化
    dst = clahe.apply(src)
    #显示
    cv2.imshow("src",src)
    cv2.imshow("clahe",dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

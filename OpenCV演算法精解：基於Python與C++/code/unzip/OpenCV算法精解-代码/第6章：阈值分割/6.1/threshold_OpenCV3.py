# -*- coding: utf-8 -*-
import numpy as np
import cv2
#主函数
if __name__ =="__main__":
    src = np.array([[123,234,68],[33,51,17],[48,98,234],
                    [129,89,27],[45,167,134]],np.uint8)
    #手动设置阈值
    the = 150
    maxval = 255
    dst = cv2.threshold(src,the,maxval,cv2.THRESH_BINARY)
    # Otsu 阈值处理 
    otsuThe = 0
    otsuThe,dst_Otsu = cv2.threshold(src,otsuThe,maxval,cv2.THRESH_OTSU)
    print otsuThe,dst_Otsu
    # TRIANGLE 阈值处理
    triThe = 0
    triThe,dst_tri = cv2.threshold(src,triThe,maxval,cv2.THRESH_TRIANGLE)
    print triThe,dst_tri
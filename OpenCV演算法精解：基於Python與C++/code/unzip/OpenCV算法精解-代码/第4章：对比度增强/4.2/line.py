# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    else:
        print "Usge:python lineContrast.py imageFile"
    MAX_VALUE = 120
    value = 120
    #调整对比度后，图像的效果显示窗口
    cv2.namedWindow("contrast",cv2.WND_PROP_AUTOSIZE)
    #调整系数，观察图像的变化
    def callback_contrast(_value):
        #通过线性运算，调整图像对比度
        a = float(_value)/40.0
        contrastImage = a*image
        contrastImage[contrastImage>255]=255
        contrastImage = np.round(contrastImage)
        contrastImage = contrastImage.astype(np.uint8)
        cv2.imshow("contrast",contrastImage)
        cv2.imwrite("contrast.jpg",contrastImage)
    callback_contrast(value)
    cv2.createTrackbar("value","contrast",value,MAX_VALUE,callback_contrast)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

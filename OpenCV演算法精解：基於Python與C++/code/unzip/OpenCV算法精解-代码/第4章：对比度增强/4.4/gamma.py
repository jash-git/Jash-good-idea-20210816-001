# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python gamma.py imageFile"
    MAX_VALUE = 200
    value = 40
    segValue = float(value)
    #伽马调整需要先将图像归一化
    image_0_1 = image/255.0
    #伽马调整后的图像显示窗口
    cv2.namedWindow("gamma_contrast",cv2.WND_PROP_AUTOSIZE)
    #调整 gamma 值，观察图像的变换
    def callback_contrast(_value):
        gamma = float(_value)/segValue
        contrastImage = np.power(image_0_1,gamma)
        cv2.imshow("gamma_contrast",contrastImage)
        #保存伽马调整的结果
        contrastImage*=255
        contrastImage = np.round(contrastImage)
        contrastImage = contrastImage.astype(np.uint8)
        cv2.imwrite("gamma.jpg",contrastImage)
    callback_contrast(value)
    cv2.createTrackbar("value","gamma_contrast",value,MAX_VALUE,callback_contrast)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
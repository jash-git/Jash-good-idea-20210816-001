# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import random
#模拟椒盐噪声，number 指添加椒盐噪声的数量
def salt(image,number):
    #图像的宽高
    rows,cols = image.shape
    #加入椒盐噪声后的图像
    saltImage = np.copy(image)
    for i in xrange(number):
        randR = random.randint(0,rows-1)
        randC = random.randint(0,cols-1)
        saltImage[randR][randC] = 0
    return saltImage
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
         print "Usge:python salt.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    cv2.imwrite("image.jpg",image)
    #添加椒盐噪声
    saltImage = salt(image,2000)
    cv2.imshow("saltImage",saltImage)
    cv2.imwrite("saltImage.jpg",saltImage)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
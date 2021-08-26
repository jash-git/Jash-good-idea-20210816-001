# -*- coding: utf-8 -*-
import sys
import cv2
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
    #第一步：读入图像
        I = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    else:
        print "Usge:python open.py imageFile"
    #cv2.imwrite("I.jpg",I)
    #创建结构元
    s = cv2.getStructuringElement(cv2.MORPH_RECT,(5,5))
    #腐蚀图像
    d = cv2.morphologyEx(I,cv2.MORPH_OPEN,s,iterations=1)
    #显示原图和腐蚀后的结果
    cv2.imshow("I",I)
    cv2.imshow("open",d)
    cv2.imwrite("open.jpg",d)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
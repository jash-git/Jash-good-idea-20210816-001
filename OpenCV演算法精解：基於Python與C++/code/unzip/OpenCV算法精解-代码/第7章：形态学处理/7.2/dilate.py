# -*- coding: utf-8 -*-
import sys
import cv2
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
    #第一步：读入图像
        I = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python erode.py imageFile"
    #显示原图
    cv2.imshow("I",I)
    #结构元半径,迭代次数
    r,i = 1,1
    MAX_R,MAX_I = 20,20
    #显示膨胀效果的窗口
    cv2.namedWindow("dilate",1)
    def nothing(*arg):
        pass
    #调节结构元半径
    cv2.createTrackbar("r","dilate",r,MAX_R,nothing)
    #调节迭代次数
    cv2.createTrackbar("i","dilate",i,MAX_I,nothing)
    while True:
        #得到当前的r值
        r = cv2.getTrackbarPos('r', 'dilate')
        #得到当前的i值
        i= cv2.getTrackbarPos('i','dilate')
        #创建结构元
        s = cv2.getStructuringElement(cv2.MORPH_GRADIENT,(2*r+1,2*r+1))
        #膨胀图像
        d = cv2.erode(I,s,iterations=i)
        #显示膨胀效果
        cv2.imshow("dilate",d)
        cv2.imwrite("dilate.jpg",d)
        ch = cv2.waitKey(5)
        #按下"Esc"键退出循环
        if ch == 27:
            break
    cv2.destroyAllWindows()
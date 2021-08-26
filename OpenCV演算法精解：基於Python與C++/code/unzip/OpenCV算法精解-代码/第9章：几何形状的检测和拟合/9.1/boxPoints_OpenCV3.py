# -*- coding: utf-8 -*-
import cv2
import numpy as np
#主函数
if __name__ =="__main__":
    #旋转矩形
    vertices = cv2.boxPoints(((200, 200), (90, 150), -60.0))
    #四个顶点
    print vertices.dtype#打印数据类型
    print vertices#打印四个顶点
    #根据四个顶点在黑色画板上画出该矩形
    img=np.zeros((400,400),np.uint8)
    for i in xrange(4):
        #相邻的点
        p1 = vertices[i,:]
        j = (i+1)%4
        p2 = vertices[j,:]
        #画出直线
        cv2.line(img,(p1[0],p1[1]),(p2[0],p2[1]),255,2)
    cv2.imshow("img",img)
    cv2.imwrite("boxPoints.jpg",img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


# -*- coding: utf-8 -*-
import numpy as np
import cv2
#主函数
if __name__ == "__main__":
    #点集
    points = np.array ([[[0,0]],[[50,30]],[[100,0]],[[100,100]]] ,np.float32)
    print points.shape
    #points = np.array ([[0,0],[50,30],[100,0],[100,100]] ,np.float32)
    #计算点集的所围区域的周长
    length1 = cv2.arcLength(points,False)#首尾不相连
    length2 = cv2.arcLength(points,True)#首尾相连
    #计算点集所围区域的面积
    area = cv2.contourArea(points)
    #打印周长和面积
    print length1,length2,area

# -*- coding: utf-8 -*-
import numpy as np
import cv2
#主函数
if __name__ == "__main__":
    #黑色画板 400 x 400
    s = 400
    I = np.zeros((s,s),np.uint8)
    #随机生成 横纵坐标均在 100 至 300 的坐标点
    n=80#随机生成 n 个坐标点，每一行存储一个坐标
    points = np.random.randint(100,300,(n,2),np.int32)
    #把上述点集处的灰度值设置为 255,单个白色像素点不容易观察，用一个小圆标注一下
    for i in xrange(n):
        cv2.circle(I,(points[i,0],points[i,1]),2,255,2)
    #求点集 points 的凸包
    convexhull = cv2.convexHull(points,clockwise=False)
    # ----- 打印凸包的信息 ----
    print type(convexhull)
    print convexhull.shape
    #连接凸包的各个点
    k = convexhull.shape[0]
    for i in xrange(k-1):
        cv2.line(I,(convexhull[i,0,0],convexhull[i,0,1]),(convexhull[i+1,0,0],convexhull[i+1,0,1]),255,2)
    #首尾相接
    cv2.line(I,(convexhull[k-1,0,0],convexhull[k-1,0,1]),(convexhull[0,0,0],convexhull[0,0,1]),255,2)
    #显示图片
    cv2.imshow("I",I)
    cv2.imwrite("I.jpg",I)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

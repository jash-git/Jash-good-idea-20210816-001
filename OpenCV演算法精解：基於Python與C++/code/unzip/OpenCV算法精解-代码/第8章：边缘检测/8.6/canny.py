# -*- coding: utf-8 -*-
import numpy as np
import sys
import math
import cv2
import sobel #注意sobel边缘检测
#边缘检测
#非极大值抑制
def non_maximum_suppression_default(dx,dy):
    #边缘强度
    edgeMag = np.sqrt(np.power(dx,2.0) + np.power(dy,2.0))
    #宽、高
    rows,cols = dx.shape
    #梯度方向
    gradientDirection = np.zeros(dx.shape)
    #边缘强度非极大值抑制
    edgeMag_nonMaxSup = np.zeros(dx.shape)
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            #angle 的范围 [0,180] [-180,0]
            angle = math.atan2(dy[r][c],dx[r][c])/math.pi*180
            gradientDirection[r][c] = angle
            #左 / 右方向
            if(abs(angle)<22.5 or abs(angle) >157.5):
                if(edgeMag[r][c]>edgeMag[r][c-1] and edgeMag[r][c] > edgeMag[r][c+1]):
                    edgeMag_nonMaxSup[r][c] = edgeMag[r][c]
            #左上 / 右下方向  
            if(angle>=22.5 and angle < 67.5 or(-angle > 112.5 and -angle <= 157.5)):
                if(edgeMag[r][c] > edgeMag[r-1][c-1] and edgeMag[r][c]>edgeMag[r+1][c+1]):
                     edgeMag_nonMaxSup[r][c] = edgeMag[r][c]
            #上 / 下方向
            if((angle>=67.5 and angle<=112.5) or (angle>=-112.5 and angle<=-67.5)):
                if(edgeMag[r][c] > edgeMag[r-1][c] and edgeMag[r][c] > edgeMag[r+1][c]):
                    edgeMag_nonMaxSup[r][c] = edgeMag[r][c]
            #右上 / 左下方向
            if((angle>112.5 and angle<=157.5) or(-angle>=22.5 and -angle< 67.5 )):
                if(edgeMag[r][c]>edgeMag[r-1][c+1] and edgeMag[r][c] > edgeMag[r+1][c-1]):
                    edgeMag_nonMaxSup[r][c] = edgeMag[r][c]
    return edgeMag_nonMaxSup
#非极大值抑制：插值比较
def non_maximum_suppression_Inter(dx,dy):
    #边缘强度
    edgeMag = np.sqrt(np.power(dx,2.0)+np.power(dy,2.0))
    #宽、高
    rows,cols = dx.shape
    #梯度方向
    gradientDirection = np.zeros(dx.shape)
    #边缘强度的非极大值抑制
    edgeMag_nonMaxSup = np.zeros(dx.shape)
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            if dy[r][c] ==0 and dx[r][c] == 0:
                continue
            #angle的范围 [0,180],[-180,0]
            angle = math.atan2(dy[r][c],dx[r][c])/math.pi*180
            gradientDirection[r][c] = angle
            #左上方和上方的插值 右下方和下方的插值
            if (angle > 45 and angle <=90) or (angle > -135 and angle <=-90):
                ratio = dx[r][c]/dy[r][c]
                leftTop_top = ratio*edgeMag[r-1][c-1]+(1-ratio)*edgeMag[r-1][c]
                rightBottom_bottom = (1-ratio)*edgeMag[r+1][c] + ratio*edgeMag[r+1][c+1]
                if edgeMag[r][c] >  leftTop_top and edgeMag[r][c] > rightBottom_bottom:
                    edgeMag_nonMaxSup[r][c]  = edgeMag[r][c]
            #右上方和上方的插值 左下方和下方的插值
            if (angle>90 and angle<=135) or (angle>-90 and angle <= -45):
                ratio = abs(dx[r][c]/dy[r][c])
                rightTop_top = ratio*edgeMag[r-1][c+1] + (1-ratio)*edgeMag[r-1][c]
                leftBottom_bottom = ratio*edgeMag[r+1][c-1] + (1-ratio)*edgeMag[r+1][c]
                if edgeMag[r][c] > rightTop_top and edgeMag[r][c] > leftBottom_bottom:
                    edgeMag_nonMaxSup[r][c]  = edgeMag[r][c]
            #左上方和左方的插值 右下方和右方的插值
            if (angle>=0 and angle <=45) or (angle>-180 and angle <= -135):
                ratio = dy[r][c]/dx[r][c]
                rightBottom_right = ratio*edgeMag[r+1][c+1]+(1-ratio)*edgeMag[r][c+1]
                leftTop_left = ratio*edgeMag[r-1][c-1]+(1-ratio)*edgeMag[r][c-1]
                if edgeMag[r][c] > rightBottom_right and edgeMag[r][c] > leftTop_left:
                    edgeMag_nonMaxSup[r][c]  = edgeMag[r][c]
            #右上方和右方的插值 左下方和左方的插值
            if(angle>135 and angle<=180) or (angle>-45 and angle <=0):
                ratio = abs(dy[r][c]/dx[r][c])
                rightTop_right = ratio*edgeMag[r-1][c+1]+(1-ratio)*edgeMag[r][c+1]
                leftBottom_left = ratio*edgeMag[r+1][c-1]+(1-ratio)*edgeMag[r][c-1]
                if edgeMag[r][c] > rightTop_right and edgeMag[r][c] > leftBottom_left:
                    edgeMag_nonMaxSup[r][c]  = edgeMag[r][c]
    return edgeMag_nonMaxSup
#判断一个点的坐标是否在图像范围内
def checkInRange(r,c,rows,cols):
    if r>=0 and r<rows and c>=0 and c<cols:
        return True
    else:
        return False
def trace(edgeMag_nonMaxSup,edge,lowerThresh,r,c,rows,cols):
    #大于阈值为确定边缘点
    if edge[r][c] == 0:
        edge[r][c]=255
        for i in range(-1,2):
            for j in range(-1,2):
                if checkInRange(r+i,c+j,rows,cols) and edgeMag_nonMaxSup[r+i][c+j] >= lowerThresh:
                    trace(edgeMag_nonMaxSup,edge,lowerThresh,r+i,c+j,rows,cols)
#滞后阈值
def hysteresisThreshold(edge_nonMaxSup,lowerThresh,upperThresh):
    #宽高
    rows,cols = edge_nonMaxSup.shape
    edge = np.zeros(edge_nonMaxSup.shape,np.uint8)
    for r in range(1,rows-1):
        for c in range(1,cols-1):
            #大于高阈值，设置为确定边缘点，而且以该点为起始点延长边缘
            if edge_nonMaxSup[r][c] >= upperThresh:
                trace(edgeMag_nonMaxSup,edge,lowerThresh,r,c,rows,cols)
            #小于低阈值，被剔除
            if edge_nonMaxSup[r][c]< lowerThresh:
                edge[r][c] = 0
    return edge
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python canny.py imageFile"
    # ------- canny 边缘检测 -----------
    #第一步： 基于 sobel 核的卷积
    image_sobel_x,image_sobel_y = sobel.sobel(image,3)
    #边缘强度：两个卷积结果对应位置的平方和
    edge = np.sqrt(np.power(image_sobel_x,2.0) + np.power(image_sobel_y,2.0))
    #边缘强度的灰度级显示
    edge[edge>255] = 255
    edge = edge.astype(np.uint8)
    cv2.imshow("sobel edge",edge)
    #第二步：非极大值抑制
    edgeMag_nonMaxSup = non_maximum_suppression_default(image_sobel_x,image_sobel_y)
    edgeMag_nonMaxSup[edgeMag_nonMaxSup>255] =255
    edgeMag_nonMaxSup = edgeMag_nonMaxSup.astype(np.uint8)
    cv2.imshow("edgeMag_nonMaxSup",edgeMag_nonMaxSup)
    #第三步：双阈值滞后阈值处理，得到 canny 边缘
    #滞后阈值的目的就是最后决定处于高阈值和低阈值之间的是否为边缘点
    edge = hysteresisThreshold(edgeMag_nonMaxSup,60,180)
    lowerThresh = 40
    upperThresh = 150
    cv2.imshow("canny",edge)
    cv2.imwrite("canny.jpg",edge)
    # -------以下是为了单阈值与滞后阈值的结果比较 ------
    #大于高阈值 设置为白色 为确定边缘
    EDGE = 255
    #小于低阈值的设置为黑色 表示不是边缘，被剔除
    NOEDGE = 0
    #而大于等于低阈值 小于高阈值的设置为灰色，标记为可能的边缘
    POSSIBLE_EDGE = 128
    tempEdge = np.copy(edgeMag_nonMaxSup)
    rows,cols = tempEdge.shape
    for r in xrange(rows):
        for c in xrange(cols):
            if tempEdge[r][c]>=upperThresh:
                tempEdge[r][c] = EDGE
            elif tempEdge[r][c]<lowerThresh:
                tempEdge[r][c] = NOEDGE
            else:
                tempEdge[r][c] = POSSIBLE_EDGE
    cv2.imshow("tempEdge",tempEdge)
    lowEdge = np.copy(edgeMag_nonMaxSup)
    lowEdge[lowEdge>60] = 255
    lowEdge[lowEdge<60] = 0
    cv2.imshow("lowEdge",lowEdge)
    upperEdge = np.copy(edgeMag_nonMaxSup)
    upperEdge[upperEdge>180]=255
    upperEdge[upperEdge<=180]=0
    cv2.imshow("upperEdge",upperEdge)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
        
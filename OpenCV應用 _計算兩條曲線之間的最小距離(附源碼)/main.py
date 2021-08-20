
# -*- coding: cp936 -*-

import numpy as np
import math
import cv2

def cal_pt_distance(pt1, pt2):
  dist = math.sqrt(pow(pt1[0]-pt2[0],2) + pow(pt1[1]-pt2[1],2))
  return dist

font = cv2.FONT_HERSHEY_SIMPLEX
img = cv2.imread('test.jpg')
cv2.imshow('src',img)
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
gray = cv2.GaussianBlur(gray, (3,3), 0)

ret,thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)
contours,hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
#thresh,contours,hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)

flag = False
minDist = 10000
minPt0 = (0,0)
minPt1 = (0,0)
for i in range(0,len(contours[1])):#遍历所有轮廓
  pt = tuple(contours[1][i][0])
  #print(pt)
  min_dis = 10000
  min_pt = (0,0)
  #distance = cv2.pointPolygonTest(contours[1], pt, False)
  for j in range(0,len(contours[0])):
    pt2 = tuple(contours[0][j][0])
    distance = cal_pt_distance(pt, pt2)
    #print(distance)
    if distance < min_dis:
      min_dis = distance
      min_pt = pt2
      min_point = pt
  if min_dis < minDist:
    minDist = min_dis
    minPt0 = min_point
    minPt1 = min_pt
  temp = img.copy()
  cv2.drawContours(img,contours,1,(255,255,0),1)
  cv2.line(temp,pt,min_pt,(0,255,0),2,cv2.LINE_AA)
  cv2.circle(temp, pt,5,(255,0,255),-1, cv2.LINE_AA)
  cv2.circle(temp, min_pt,5,(0,255,255),-1, cv2.LINE_AA)
  cv2.imshow("img",temp)
  if cv2.waitKey(1)&0xFF ==27: #按下Esc键退出
    flag = True
    break
  if flag:
    break

cv2.line(img,minPt0,minPt1,(0,255,0),2,cv2.LINE_AA)
cv2.circle(img, minPt0,3,(255,0,255),-1, cv2.LINE_AA)
cv2.circle(img, minPt1,3,(0,255,255),-1, cv2.LINE_AA)
cv2.putText(img,("min_dist=%0.2f"%minDist), (minPt1[0],minPt1[1]+15), font, 0.7, (0,255,0), 2)

cv2.imshow('result', img)
cv2.imwrite('result.png',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
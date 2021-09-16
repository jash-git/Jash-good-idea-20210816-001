
#--公众号：OenCV与AI深度学习
#--Author:Color Space
import numpy as np

import cv2

font=cv2.FONT_HERSHEY_SIMPLEX

img = cv2.imread('embossed_01.png')

cv2.imshow('src', img)

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

blur = cv2.blur(gray, (50,50))

cv2.imshow('blur', blur)

diff = cv2.absdiff(gray, blur)

cv2.imshow('diff', diff)

ret,thres = cv2.threshold(diff,15,255,cv2.cv2.THRESH_BINARY)

cv2.imshow('thres', thres)

k1 = np.zeros((19, 19),np.uint8)
cv2.circle(k1,(9,9),9,(1,1,1),-1,cv2.LINE_AA)

closing = cv2.morphologyEx(thres, cv2.MORPH_CLOSE, k1, None, None, 1)#闭运算
cv2.imshow('closing',closing)

k2 = np.zeros((13, 13),np.uint8)
cv2.circle(k2,(6,6),6,(1,1,1),-1,cv2.LINE_AA)

opening = cv2.morphologyEx(closing, cv2.MORPH_OPEN, k2, None, None, 1)#闭运算
cv2.imshow('opening',opening)

contours,hierarchy = cv2.findContours(opening, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
count = 0
for cnt in contours:
  center,radius = cv2.minEnclosingCircle(cnt)
  if radius < 5:
    continue
  count = count + 1
  cv2.circle(img,(int(center[0]),int(center[1])),int(radius),(0,255,0),2)
  cv2.drawMarker(img,(int(center[0]),int(center[1])),(0,0,255),
                     cv2.MARKER_CROSS, 15,1,8)
strCount = "count = %d" % count
cv2.putText(img,strCount,(10,30),font,1.0,(255,0,0),2)

cv2.imshow('result', img)
cv2.imwrite('result.jpg', img)

cv2.waitKey(0)
cv2.destroyAllWindows()
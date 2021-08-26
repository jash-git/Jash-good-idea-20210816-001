# -*- coding: utf-8 -*-
import cv2
import numpy as np
#点集
contour = np.array([[0,0],[50,30],[100,100],[100,0]],np.float32)
#判断三个点和点集构成的轮廓的关系
dist1 = cv2.pointPolygonTest(contour,(80,40),False)
dist2 = cv2.pointPolygonTest(contour,(50,0),False)
dist3 = cv2.pointPolygonTest(contour,(40,80),False)
#打印结果
print dist1,dist2,dist3

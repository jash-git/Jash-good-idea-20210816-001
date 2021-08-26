# -*- coding: utf-8 -*-
import cv2
import numpy as np
src1 = np.array([[255,0,255]])
src2 = np.array([[255,0,0]])
#与运算
dst_and = cv2.bitwise_and(src1,src2)
#或运算
dst_or = cv2.bitwise_or(src1,src2)
print "与运算的结果："
print dst_and
print "或运算的结果："
print dst_or
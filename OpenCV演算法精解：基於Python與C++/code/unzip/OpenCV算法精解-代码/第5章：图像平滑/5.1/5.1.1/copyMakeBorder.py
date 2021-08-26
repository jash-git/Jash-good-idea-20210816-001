# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#主函数
if __name__ =="__main__":
    src=np.array([[5,1,7],[1,5,9],[2,6,2]])
    dst=cv2.copyMakeBorder(src,2,2,2,2,2)
    print dst

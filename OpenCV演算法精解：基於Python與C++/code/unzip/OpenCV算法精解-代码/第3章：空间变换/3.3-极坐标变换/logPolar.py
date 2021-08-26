# -*- coding: utf-8 -*-
import cv2
import sys
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        src = cv2.imread(sys.argv[1],cv2.IMREAD_ANYCOLOR)
    else:
        print "Usage: python logPolar.py image"
    #显示原图
    cv2.imshow("src",src)
    #图像的极坐标变换
    M = 150
    dst=cv2.logPolar(src,(508,503),M,cv2.WARP_FILL_OUTLIERS)
    #显示极坐标变化的结果
    print src.shape
    print dst.shape
    cv2.imshow("dst",dst)
    cv2.imwrite("logPolar_150.jpg",dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    

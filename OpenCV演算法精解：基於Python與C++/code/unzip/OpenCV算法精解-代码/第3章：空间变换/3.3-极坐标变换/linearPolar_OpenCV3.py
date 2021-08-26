# -*- coding: utf-8 -*-
import cv2
import sys
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        src = cv2.imread(sys.argv[1],cv2.IMREAD_ANYCOLOR)
    else:
        print "Usage: python linearPolar.py image"
    #显示原图
    cv2.imshow("src",src)
    #图像的极坐标变换
    dst = cv2.linearPolar(src,(508,503),550,cv2.INTER_LINEAR)
    #显示极坐标变化的结果
    cv2.imshow("dst",dst)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
     

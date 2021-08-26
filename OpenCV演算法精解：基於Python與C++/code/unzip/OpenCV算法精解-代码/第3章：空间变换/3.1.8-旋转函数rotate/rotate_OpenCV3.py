# -*- coding: utf-8 -*-
import cv2
import sys
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.IMREAD_ANYCOLOR)
    else:
        print "Usage: python rotate.py image"
    #显示原图
    cv2.imshow("image",image)
    #图像旋转 ： cv2.ROTATE_180  cv2.ROTATE_90_COUNTERCLOCKWISE
    rImg = cv2.rotate(image,cv2.ROTATE_90_COUNTERCLOCKWISE)
    #显示旋转的结果
    cv2.imshow("rImg",rImg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
     
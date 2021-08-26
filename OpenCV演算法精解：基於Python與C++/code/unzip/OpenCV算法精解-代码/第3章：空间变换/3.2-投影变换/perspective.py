# -*- coding: utf-8 -*-
import numpy as np
import cv2
import sys
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usage: python warpPercpective.py image"
    #原图的宽高
    h,w = image.shape
    #将原图的四个顶点投影到一个不规则的四边形中
    src=np.array([[0,0],[w-1,0],[0,h-1],[w-1,h-1]],np.float32);
    dst=np.array([[20,50],[w/2,150],[50,h/2],[w-40,h-40]],np.float32)
    #计算投影矩阵
    p=cv2.getPerspectiveTransform(src,dst)
    #利用计算出的投影矩阵进行头像的投影变换
    r = cv2.warpPerspective(image,p,(w,h),borderValue=0)
    #显示原图和投影效果
    cv2.imshow("image",image)
    cv2.imshow("warpPerspective",r)
    cv2.imwrite("p.jpg",r)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#主函数
if __name__ =="__main__":
    if len(sys.argv)>1:
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_COLOR)
    else:
        print "Usge:python HLS.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #图像归一化，且转换为浮点型
    fImg = image.astype(np.float32)
    fImg = fImg/255.0
    #颜色空间转换
    hlsImg = cv2.cvtColor(fImg,cv2.COLOR_BGR2HLS)
    l = 100 
    s = 100
    MAX_VALUE = 100
    cv2.namedWindow("l and s",cv2.WINDOW_AUTOSIZE)
    def nothing(*arg):
        pass
    cv2.createTrackbar("l","l and s",l,MAX_VALUE,nothing)
    cv2.createTrackbar("s","l and s",s,MAX_VALUE,nothing)
    #调整饱和度和亮度后的效果
    lsImg = np.zeros(image.shape,np.float32)
    #调整饱和度和亮度
    while True:
        #复制
        hlsCopy = np.copy(hlsImg)
        #得到 l 和 s 的值
        l = cv2.getTrackbarPos('l', 'l and s')
        s = cv2.getTrackbarPos('s', 'l and s')
        #调整亮度和饱和度（线性变换）
        hlsCopy[:,:,1] = (1.0+l/float(MAX_VALUE))*hlsCopy[:,:,1]
        hlsCopy[:,:,1][hlsCopy[:,:,1]>1] = 1
        hlsCopy[:,:,2] = (1.0+s/float(MAX_VALUE))*hlsCopy[:,:,2]
        hlsCopy[:,:,2][hlsCopy[:,:,2]>1] = 1
        # HLS2BGR
        lsImg = cv2.cvtColor(hlsCopy,cv2.COLOR_HLS2BGR)
        #显示调整后的效果
        cv2.imshow("l and s",lsImg)
        #保存结果
        lsImg = lsImg*255
        lsImg = lsImg.astype(np.uint8)
        cv2.imwrite("lsImg.jpg",lsImg)
        ch = cv2.waitKey(5)
        if ch == 27:
            break
    cv2.destroyAllWindows()
    

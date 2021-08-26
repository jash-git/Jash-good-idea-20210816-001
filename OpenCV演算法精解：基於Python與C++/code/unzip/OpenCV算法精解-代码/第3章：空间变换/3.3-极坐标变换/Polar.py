# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys
#极坐标变换
def polar(I,center,r,theta=(0,360),rstep=1.0,thetastep=360.0/(180*8)):
    #得到距离的最小最大范围 
    minr,maxr = r
    #角度的最小范围
    mintheta,maxtheta = theta
    #输出图像的高，宽
    H = int((maxr-minr)/rstep)+1
    W =  int((maxtheta-mintheta)/thetastep)+1
    O = np.zeros((H,W),I.dtype)
    #极坐标变换
    r = np.linspace(minr,maxr,H)
    r = np.tile(r,(W,1))
    r = np.transpose(r)
    theta = np.linspace(mintheta,maxtheta,W)
    theta = np.tile(theta,(H,1))
    x,y=cv2.polarToCart(r,theta,angleInDegrees=True)
    #最近邻插值
    for i in xrange(H):
        for j in xrange(W):
            px = int(round(x[i][j])+cx)
            py = int(round(y[i][j])+cy)
            if(px>w-1 or py >h-1):
                O[i][j] = 125#灰色
            else:
                O[i][j] = I[py][px]
    return O
    
#主函数
if __name__ == "__main__":
    if len(sys.argv)>1:
        I = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usage: python polar.py image"
    #图像的宽高
    h,w = I.shape[:2]
    print w,h
    #极左标变换的中心
    cx,cy = w/2.0,h/2.0+10
    print cx,cy
    cv2.circle(I,(int(cx),int(cy)),10,(255.0,0,0),3)
    #距离的最小最大半径 #200 550 270,340
    O = polar(I,(cx,cy),(270,340))
    #旋转
    O = cv2.flip(O,0)
    #显示原图和输出图像
    cv2.imshow("I",I)
    cv2.imshow("O",O)
    cv2.imwrite("O.jpg",O)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
                
    
    
        
    
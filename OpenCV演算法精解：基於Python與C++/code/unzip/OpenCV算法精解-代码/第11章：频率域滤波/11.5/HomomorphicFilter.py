# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#快速傅里叶变换
def fft2Image(src):
    #得到行、列
    r,c = src.shape[:2]
    #得到快速傅里叶变换最优
    rPadded = cv2.getOptimalDFTSize(r)
    cPadded = cv2.getOptimalDFTSize(c)
    #边缘扩充，下边缘和右边缘扩充值为零
    fft2 = np.zeros((rPadded,cPadded,2),np.float32)
    fft2[:r,:c,0]=src
    #快速傅里叶变换
    cv2.dft(fft2,fft2,cv2.DFT_COMPLEX_OUTPUT)
    return fft2
 #傅里叶幅度谱
def amplitudeSpectrum(fft2):
    #求幅度
    real2 = np.power(fft2[:,:,0],2.0)
    Imag2 = np.power(fft2[:,:,1],2.0)
    amplitude = np.sqrt(real2+Imag2)
    return amplitude
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
    #第一步：读入图像
        I = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python homomorphicFilter.py imageFile"
    cv2.imshow("I",I)
    cv2.imwrite("I.jpg",I)
    #第二步：取对数
    lI = np.log(I+1.0)
    lI = lI.astype(np.float32)
    #第三步：每一元素乘以 (-1)^(r+c)
    fI = np.copy(lI)
    for r in xrange(I.shape[0]):
        for c in xrange(I.shape[1]):
            if (r+c)%2:
                fI[r][c] = -1*fI[r][c]
    #第四、五步：补零和快速傅里叶变换
    fft2 = fft2Image(fI)
    #第六步：构造高频增强滤波器（ high-emphasis Filter）
    #找到傅里叶谱中的最大值的位置
    amplitude = amplitudeSpectrum(fft2)
    minValue,maxValue,minLoc,maxLoc = cv2.minMaxLoc(amplitude)
    #滤波器的高和宽
    rows,cols = fft2.shape[:2]
    r,c = np.mgrid[0:rows:1,0:cols:1]
    c-=maxLoc[0]
    r-=maxLoc[1]
    d = np.power(c,2.0)+np.power(r,2.0)
    high,low,k,radius = 2.5,0.5,1,300
    heFilter =(high-low)*(1-np.exp(-k*d/(2.0*pow(radius,2.0))))+low
    #第七步：快速傅里叶变换与高频增强滤波器的点乘
    fft2Filter = np.zeros(fft2.shape,fft2.dtype)
    for i in xrange(2):
        fft2Filter[:rows,:cols,i] = fft2[:rows,:cols,i]*heFilter
    #第八、九步：高频增强傅里叶变换执行傅里叶逆变换,并只取实部
    ifft2 = cv2.dft(fft2Filter,flags=cv2.DFT_REAL_OUTPUT+cv2.DFT_INVERSE+cv2.DFT_SCALE)
    #第十步：裁剪，和输入图像的尺寸一样
    ifI = np.copy(ifft2[:I.shape[0],:I.shape[1]])
    #第十一步：每一元素乘以 (-1)^(r+c)
    for i in xrange(ifI.shape[0]):
        for j in xrange(ifI.shape[1]):
            if (i+j)%2:
                ifI[i][j] = -1*ifI[i][j]
    #第十二步：取指数
    eifI = np.exp(ifI)-1
    #第十三步：归一化，并进行数据类型转换
    eifI = (eifI-np.min(eifI))/(np.max(eifI)-np.min(eifI))
    eifI = 255*eifI
    eifI = eifI.astype(np.uint8)
    cv2.imshow("homomorphicFilter",eifI)
    cv2.imwrite("homomorphicFilter.jpg",eifI)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    
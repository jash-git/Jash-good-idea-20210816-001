# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
import math
#快速傅里叶变换
def fft2Image(src):
    #得到行、列
    r,c = src.shape[:2]
    #得到快速傅里叶变换最优扩充
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
#幅度谱的灰度级显示
def graySpectrum(amplitude):
    #对比度拉伸
    #cv2.log(amplitude+1.0,amplitude)
    amplitude = np.log(amplitude+1.0)
    #归一化,傅里叶谱的灰度级显示
    spectrum = np.zeros(amplitude.shape,np.float32)
    cv2.normalize(amplitude,spectrum,0,1,cv2.NORM_MINMAX)
    return spectrum
#相位谱
def phaseSpectrum(fft2):
    #得到行数、列数
    rows,cols = fft2.shape[:2]
    #计算相位角
    phase = np.arctan2(fft2[:,:,1],fft2[:,:,0])
    #相位角转换为 [ -180 , 180]
    spectrum = phase/math.pi*180
    return spectrum
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
    #第一步：读入图像
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python spectrum.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #cv2.imwrite("img1.jpg",image)
    #快速傅里叶变换
    fft2 = fft2Image(image)
    #求幅度谱
    amplitude = amplitudeSpectrum(fft2)
    amc = np.copy(amplitude)
    amc[amc>255]=255
    amc = amc.astype(np.uint8)
   # cv2.imshow("originam",amc)
    #cv2.imwrite("orAmp.jpg",amc)
    #幅度谱的灰度级显示
    ampSpectrum = graySpectrum(amplitude)
    ampSpectrum *=255
    ampSpectrum = ampSpectrum.astype(np.uint8)
    cv2.imshow("amplitudeSpectrum",ampSpectrum)
    #cv2.imwrite("ampSpectrum.jpg",ampSpectrum)
    #相位谱的灰度级显示
    phaseSpe = phaseSpectrum(fft2)
    cv2.imshow("phaseSpectrum",phaseSpe)
   # cv2.imwrite("phaseSpe.jpg",phaseSpe)
    '''
    傅里叶幅度谱的中心化
    '''
    #第一步：图像乘以(-1)^(r+c)
    rows,cols = image.shape
    fimg = np.copy(image)
    fimg = fimg.astype(np.float32)
    for r in xrange(rows):
        for c in xrange(cols):
            if (r+c)%2:
                fimg[r][c] =-1*image[r][c]
            else:
                fimg[r][c] = image[r][c]
    #第二步：快速傅里叶变换
    imgfft2 = fft2Image(fimg)
    #第三步：傅里叶的幅度谱
    amSpe = amplitudeSpectrum(imgfft2)
    #幅度谱的灰度级显示
    graySpe = graySpectrum(amSpe)
    cv2.imshow("amSpe",graySpe)
    graySpe *=255
    graySpe = graySpe.astype(np.uint8)
    cv2.imwrite("centerAmp.jpg",graySpe)
    #第四步：相位谱的灰度级显示
    phSpe = phaseSpectrum(imgfft2)
    cv2.imshow("phSpe",phSpe)
    #cv2.imwrite("centerphSpe.jpg",phSpe)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
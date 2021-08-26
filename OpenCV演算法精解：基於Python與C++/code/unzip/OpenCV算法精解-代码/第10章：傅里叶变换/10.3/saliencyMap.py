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
    real,Imag = cv2.split(fft2)
    amplitude = cv2.magnitude(real,Imag)
    #amplitude = cv2.magnitude(fft2[:,:,0],fft2[:,:,1])
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
    #显示该相位谱时，首先需要将相位角转换为 [ -180 , 180]
    #spectrum = phase/math.pi*180
    return phase    
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
        image = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    else:
        print "Usge:python saliencyMap.py imageFile"
    #第一步：计算图像的快速傅里叶变换
    fft2 = fft2Image(image)
    #第二步：计算傅里叶幅度谱的灰度级
    #求幅度谱
    amplitude = amplitudeSpectrum(fft2)
    #幅度谱的灰度级
    logAmplitude = graySpectrum(amplitude)
    #第三步：计算相位
    phase = phaseSpectrum(fft2)
    #余弦谱（用于计算实部）
    cosSpectrum = np.cos(phase)
    #正弦谱（用于计算虚部）
    sinSectrum = np.sin(phase)
    #第四步：计算残差（Spectral Residual）
    #对幅度谱的灰度级进行均值平滑
    meanLogAmplitude = cv2.boxFilter(logAmplitude,cv2.CV_32FC1,(3,3))
    #残差
    spectralResidual = logAmplitude - meanLogAmplitude
    #第五步：计算傅里叶逆变换,显著性
    #残差的指数
    expSR = np.exp(spectralResidual)
    #分别计算实部和虚部
    real = expSR*cosSpectrum
    imaginary = expSR*sinSectrum
    #合并实部和虚部
    com = np.zeros((real.shape[0],real.shape[1],2),np.float32)
    com[:,:,0]=real
    com[:,:,1]=imaginary
    #逆变换
    ifft2=np.zeros(com.shape,np.float32)
    cv2.dft(com,ifft2,cv2.DFT_COMPLEX_OUTPUT+cv2.DFT_INVERSE)
    #显著性
    saliencymap = np.power(ifft2[:,:,0],2)+np.power(ifft2[:,:,1],2)
    #对显著性进行高斯平滑
    saliencymap = cv2.GaussianBlur(saliencymap,(11,11),2.5)
    #显示检测到的显著性
    #cv2.normalize(saliencymap,saliencymap,0,1,cv2.NORM_MINMAX)
    saliencymap  = saliencymap/np.max(saliencymap)
    #提高对比度，进行伽马变换
    saliencymap = np.power(saliencymap,0.5)
    saliencymap = np.round(saliencymap*255)
    saliencymap = saliencymap.astype(np.uint8)
    cv2.imshow("saliencymap",saliencymap)
    cv2.imwrite("saliencymap.jpg",saliencymap)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
        
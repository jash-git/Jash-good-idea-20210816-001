# -*- coding: utf-8 -*-
import sys
import numpy as np
import cv2
#截止频率
radius = 50
MAX_RADIUS = 100
#低通滤波类型
lpType = 0
MAX_LPTYPE = 2
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
#幅度谱的灰度级显示
def graySpectrum(amplitude):
    #对比度拉伸
    #cv2.log(amplitude+1.0,amplitude)
    amplitude = np.log(amplitude+1.0)
    #归一化,傅里叶谱的灰度级显示
    spectrum = np.zeros(amplitude.shape,np.float32)
    cv2.normalize(amplitude,spectrum,0,1,cv2.NORM_MINMAX)
    return spectrum
#构建低通滤波器    
def createLPFilter(shape,center,radius,lpType=0,n=2):
    #滤波器的高和宽
    rows,cols = shape[:2]
    r,c = np.mgrid[0:rows:1,0:cols:1]
    c-=center[0]
    r-=center[1]
    d = np.power(c,2.0)+np.power(r,2.0)
    #构造低通滤波器
    lpFilter = np.zeros(shape,np.float32)
    if(radius<=0):
        return lpFilter
    if(lpType == 0):#理想低通滤波
        lpFilter = np.copy(d)
        lpFilter[lpFilter<pow(radius,2.0)]=1
        lpFilter[lpFilter>=pow(radius,2.0)]=0
    elif(lpType == 1): #巴特沃斯低通滤波
        lpFilter = 1.0/(1.0+np.power(np.sqrt(d)/radius,2*n))
    elif(lpType == 2): #高斯低通滤波
        lpFilter = np.exp(-d/(2.0*pow(radius,2.0)))
    return lpFilter
#主函数
if __name__ =="__main__":
    if len(sys.argv) > 1:
    #第一步：读入图像
        image = cv2.imread(sys.argv[1],cv2.CV_LOAD_IMAGE_GRAYSCALE)
    else:
        print "Usge:python LPFilter.py imageFile"
    #显示原图
    cv2.imshow("image",image)
    #第二步：每一元素乘以 (-1)^(r+c)
    fimage = np.zeros(image.shape,np.float32)
    for r in xrange(image.shape[0]):
        for c in xrange(image.shape[1]):
            if (r+c)%2:
                fimage[r][c] = -1*image[r][c]
            else:
                fimage[r][c] = image[r][c]
    #第三和四步：补零和快速傅里叶变换
    fImagefft2 = fft2Image(fimage)
    #傅里叶谱
    amplitude = amplitudeSpectrum(fImagefft2)
    #傅里叶谱的灰度级显示
    spectrum = graySpectrum(amplitude)
    cv2.imshow("originalSpectrum",spectrum)
    #找到傅里叶谱最大值的位置
    minValue,maxValue,minLoc,maxLoc = cv2.minMaxLoc(amplitude)
    #低通傅里叶谱灰度级的显示窗口
    cv2.namedWindow("lpFilterSpectrum",1)
    def nothing(*arg):
        pass
    #调节低通滤波类型
    cv2.createTrackbar("lpType","lpFilterSpectrum",lpType,MAX_LPTYPE,nothing)
    #调节截断频率
    cv2.createTrackbar("radius","lpFilterSpectrum",radius,MAX_RADIUS,nothing)
    #低通滤波结果
    result = np.zeros(spectrum.shape,np.float32)
    while True:
        #得到当前的截断频率、低通滤波类型
        radius = cv2.getTrackbarPos("radius","lpFilterSpectrum")
        lpType = cv2.getTrackbarPos("lpType","lpFilterSpectrum")
        #第五步：构建低通滤波器
        lpFilter = createLPFilter(spectrum.shape,maxLoc,radius,lpType)
        #第六步：低通滤波器和快速傅里叶变换对应位置相乘（点乘）
        rows,cols = spectrum.shape[:2]
        fImagefft2_lpFilter = np.zeros(fImagefft2.shape,fImagefft2.dtype)
        for i in xrange(2):
            fImagefft2_lpFilter[:rows,:cols,i] = fImagefft2[:rows,:cols,i]*lpFilter
        #低通傅里叶变换的傅里叶谱
        lp_amplitude = amplitudeSpectrum(fImagefft2_lpFilter)
        #显示低通滤波后的傅里叶谱的灰度级
        lp_spectrum = graySpectrum(lp_amplitude)
        cv2.imshow("lpFilterSpectrum", lp_spectrum)
        #第七和八步：对低通傅里叶变换执行傅里叶逆变换,并只取实部
        cv2.dft(fImagefft2_lpFilter,result,cv2.DFT_REAL_OUTPUT+cv2.DFT_INVERSE+cv2.DFT_SCALE)
        #第九步：乘以(-1)^(r+c)
        for r in xrange(rows):
            for c in xrange(cols):
                if (r+c)%2:
                    result[r][c]*=-1
        #第十步：数据类型转换,并进行灰度级显示，截取左上角，大小和输入图像相等
        for r in xrange(rows):
            for c in xrange(cols):
                if result[r][c] < 0:
                    result[r][c] = 0
                elif result[r][c] > 255:
                    result[r][c] = 255
        lpResult = result.astype(np.uint8)
        lpResult = lpResult[:image.shape[0],:image.shape[1]]
        cv2.imshow("LPFilter",lpResult)             
        ch = cv2.waitKey(5)
        if ch == 27:
            break
    cv2.destroyAllWindows()


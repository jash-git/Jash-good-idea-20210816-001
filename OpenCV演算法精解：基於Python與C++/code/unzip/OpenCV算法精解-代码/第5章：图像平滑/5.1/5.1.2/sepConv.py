# -*- coding: utf-8 -*-
import numpy as np
from scipy import signal
#主函数
if __name__ =="__main__":
    kernel1 = np.array([[1,2,3]],np.float32)
    kernel2 = np.array([[4],[5],[6]],np.float32)
    #计算两个核的全卷积
    kernel = signal.convolve2d(kernel1,kernel2,mode='full')

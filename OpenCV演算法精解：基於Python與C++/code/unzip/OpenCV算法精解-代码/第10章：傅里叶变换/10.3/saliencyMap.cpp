#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
void fft2Image(InputArray _src, OutputArray _dst);
//求幅度谱 amplitude spectrum
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
//求相位谱 phase spectrum
Mat phaseSpectrum(Mat _srcFFT);
int main(int argc, char*argv[])
{
	//读入图像（灰度化）
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("原图", image);
	//转换为 double 类型
	Mat fImage;
	image.convertTo(fImage, CV_64FC1,1.0/255);
	//快速傅里叶变换
	Mat fft2;
	fft2Image(fImage, fft2);
	//幅度谱（又称傅里叶谱）
	Mat amplitude;
	amplitudeSpectrum(fft2, amplitude);
	//对幅度谱进行对数运算
	Mat logAmplitude;
	cv::log(amplitude + 1.0, logAmplitude);
	//均值平滑
	Mat meanLogAmplitude;
	cv::blur(logAmplitude, meanLogAmplitude, Size(3, 3),Point(-1,-1));
	//谱残差
	Mat spectralResidual = logAmplitude - meanLogAmplitude;
	//相位谱
	Mat phase = phaseSpectrum(fft2);
	//余弦谱 cos(phase)
	Mat cosSpectrum(phase.size(), CV_64FC1);
	//正弦谱 sin(phase)
	Mat sinSpectrum(phase.size(), CV_64FC1);
	for (int r = 0; r < phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			cosSpectrum.at<double>(r, c) = cos(phase.at<double>(r, c));
			sinSpectrum.at<double>(r, c) = sin(phase.at<double>(r, c));
		}
	}
	//指数运算
	exp(spectralResidual, spectralResidual);
	Mat real = spectralResidual.mul(cosSpectrum);
	Mat imaginary = spectralResidual.mul(sinSpectrum);
	vector<Mat> realAndImag;
	realAndImag.push_back(real);
	realAndImag.push_back(imaginary);
	Mat complex;
	merge(realAndImag, complex);
	//快速傅里叶逆变换
	Mat ifft2;
	dft(complex, ifft2, DFT_COMPLEX_OUTPUT + DFT_INVERSE);
	//傅里叶逆变换的幅度
	Mat ifft2Amp;
	amplitudeSpectrum(ifft2, ifft2Amp);
	//平方运算
	pow(ifft2Amp, 2.0, ifft2Amp);
	//高斯平滑
	GaussianBlur(ifft2Amp, ifft2Amp, Size(11,11), 2.5);
	//显著性显示
	normalize(ifft2Amp, ifft2Amp, 1.0, 0, NORM_MINMAX);
	//提升对比度，进行伽马变换
	pow(ifft2Amp, 0.5, ifft2Amp);
	//数据类型转换
	Mat saliencyMap;
	ifft2Amp.convertTo(saliencyMap, CV_8UC1,255);
	imshow("显著性", saliencyMap);

	waitKey(0);
	return 0;
}
//快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst)
{
	//得到Mat类型
	Mat src = _src.getMat();
	//判断位深
	CV_Assert(src.type() == CV_32FC1 || src.type() == CV_64FC1);
	CV_Assert(src.channels() == 1 || src.channels() == 2);
	int rows = src.rows;
	int cols = src.cols;
	//为了进行快速的傅里叶变换，我们经行和列的扩充,找到最合适扩充值
	Mat padded;
	int rPadded = getOptimalDFTSize(rows);
	int cPadded = getOptimalDFTSize(cols);
	//进行边缘扩充,扩充值为零
	copyMakeBorder(src, padded, 0, rPadded - rows, 0, cPadded - cols, BORDER_CONSTANT, Scalar::all(0));
	//快速的傅里叶变换（双通道：用于存储实部 和 虚部）
	dft(padded, _dst, DFT_COMPLEX_OUTPUT);
}
//求幅度谱 amplitude spectrum
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	//判断傅里叶变换是两个通道
	CV_Assert(_srcFFT.channels() == 2);
	//分离通道
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//计算傅里叶变换的幅度谱 sqrt(pow(R,2)+pow(I,2))
	magnitude(FFT2Channel[0],FFT2Channel[1], _dstSpectrum);
}

//求相位谱 phase spectrum
Mat phaseSpectrum(Mat _srcFFT)
{
	//相位谱
	Mat phase;
	phase.create(_srcFFT.size(),CV_64FC1);
	//分离通道
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//计算相位谱
	for (int r = 0; r<phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			//实部 
			double real = FFT2Channel[0].at<double>(r, c);
			//虚部
			double imaginary = FFT2Channel[1].at<double>(r, c);
			//计算相位角
			phase.at<double>(r, c) = atan2(imaginary, real);
		}
	}
	return phase;
}
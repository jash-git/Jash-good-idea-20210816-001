#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
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
//求傅里叶变换的幅度谱 amplitude spectrum
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	//判断傅里叶变换是两个通道
	CV_Assert(_srcFFT.channels() == 2);
	//分离通道
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//计算傅里叶变换的幅度谱 sqrt(pow(R,2)+pow(I,2))
	magnitude(FFT2Channel[0], FFT2Channel[1], _dstSpectrum);
}
//傅里叶谱的灰度级显示
Mat graySpectrum(Mat spectrum)
{
	Mat dst;
	log(spectrum + 1, dst);
	//归一化
	normalize(dst, dst, 0, 1, NORM_MINMAX);
	//为了进行灰度级显示，做类型转换
	dst.convertTo(dst, CV_8UC1, 255, 0);
	return dst;
}
//求相位谱 phase spectrum
Mat phaseSpectrum(Mat _srcFFT)
{
	//相位谱
	Mat phase;
	phase.create(_srcFFT.size(), CV_64FC1);
	//分离通道
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//计算相位谱
	for (int r = 0; r<phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			//实部 虚部
			double real = FFT2Channel[0].at<double>(r, c);
			double imaginary = FFT2Channel[1].at<double>(r, c);
			// atan2 的返回值范围 [0,180] [-180,0]
			phase.at<double>(r, c) = atan2(imaginary, real);
		}
	}
	return phase;
}
int main(int argc, char*argv[])
{
	//输入图像
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
		return -1;
	//将图像转换为浮点型
	Mat fImg;
	img.convertTo(fImg, CV_64FC1, 1.0, 0);
	//乘以 -1^(r+c)
	int rows = fImg.rows;
	int cols = fImg.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if ((r + c) % 2)
				fImg.at<double>(r, c) *= -1;
		}
	}
	//快速傅里叶变换
	Mat fft2;
	fft2Image(fImg, fft2);
	//傅里叶变换的幅度谱
	Mat ampSpec;
	amplitudeSpectrum(fft2, ampSpec);
	//幅度谱的灰度级显示
	Mat graySpec = graySpectrum(ampSpec);
	imshow("幅度谱的灰度级显示", graySpec);
	//相位谱
	Mat phaSpec = phaseSpectrum(fft2);
	//相位谱的灰度级显示
	imshow("相位谱", phaSpec);
	waitKey(0);
	return 0;
}
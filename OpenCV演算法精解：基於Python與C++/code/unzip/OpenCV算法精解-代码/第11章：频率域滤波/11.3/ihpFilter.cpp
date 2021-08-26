#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
/*全局变量*/
Mat image;
Mat fImageFFT;//存储图像的快速傅里叶变换
Point maxLoc;//傅里叶谱的最大值的坐标
int radius = 10;//截止频率
const int Max_RADIUS = 100;

//理想高通滤波器
Mat ihpFilter;
Mat fImageFFT_ihpFilter;
Mat fImageFFT_ihpFilter_spectrum;
Mat result;
//第二步：快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst);

//傅里叶谱的灰度级:输入的是傅里叶变换,输出是傅里叶谱的灰度级
void fourierSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
void callback_ihpFilter(int, void*);
int main(int argc, char*argv[])
{
	/*第一步：读入图像矩阵*/
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有图片" << endl;
		return -1;
	}
	imshow("原图片", image);
	Mat fImage;
	image.convertTo(fImage, CV_32FC1, 1.0, 0.0);

	/*第二步:图像矩阵的每一个数乘以(-1)^(r+c)*/
	for (int r = 0; r < fImage.rows; r++)
	{
		for (int c = 0; c < fImage.cols; c++)
		{
			if ((r + c) % 2)
				fImage.at<float>(r, c) *= -1;
		}
	}

	/*第三步：快速傅里叶变换*/
	fft2Image(fImage, fImageFFT);
	//傅里叶变换的傅里叶谱
	Mat fImageFFT_spectrum;
	//傅里叶谱的灰度级显示
	fourierSpectrum(fImageFFT, fImageFFT_spectrum);
	imshow("图像的傅里叶谱", fImageFFT_spectrum);
	//得到傅里叶谱最大值的位置
	minMaxLoc(fImageFFT_spectrum, NULL, NULL, NULL, &maxLoc);
	/*理想高通滤波器*/
	namedWindow("理想高通傅里叶谱", 1);
	createTrackbar("半径:", "理想高通傅里叶谱", &radius, Max_RADIUS, callback_ihpFilter);
	waitKey(0);
	return 0;
}
void callback_ihpFilter(int, void*)
{
	/*第四步：构建理想高通滤波器*/
	ihpFilter.create(fImageFFT.size(), CV_32FC1);

	for (int r = 0; r < ihpFilter.rows; r++)
	{
		for (int c = 0; c < ihpFilter.cols; c++)
		{
			if (sqrt(pow(abs(float(r - maxLoc.y)), 2) + pow(abs(float(c - maxLoc.x)), 2)) > radius)
				ihpFilter.at<float>(r, c) = 1;
			else
				ihpFilter.at<float>(r, c) = 0;
		}
	}

	/*第五步：理想高通滤波器和图像的快速傅里叶变换进行点乘*/
	fImageFFT_ihpFilter.create(fImageFFT.size(), fImageFFT.type());
	for (int r = 0; r < fImageFFT_ihpFilter.rows; r++)
	{
		for (int c = 0; c < fImageFFT_ihpFilter.cols; c++)
		{
			//分别取出当前位置的快速傅里叶变换和理想高通滤波器的值
			Vec2f temp_fImageFFT = fImageFFT.at<Vec2f>(r, c);
			float temp_ihpFilter = ihpFilter.at<float>(r, c);

			//理想高通滤波器和图像的快速傅里叶变换对应位置相乘
			fImageFFT_ihpFilter.at<Vec2f>(r, c) = temp_fImageFFT*temp_ihpFilter;
		}
	}

	//显示高斯低通傅里叶谱
	fourierSpectrum(fImageFFT_ihpFilter, fImageFFT_ihpFilter_spectrum);
	imshow("理想高通傅里叶谱", fImageFFT_ihpFilter_spectrum);

	/*第六步：对理想高通傅里叶变换执行傅里叶逆变换，并只取实部*/
	dft(fImageFFT_ihpFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);

	/*第七步：同乘以(-1)^(x+y)*/
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	/*第八步：取左上角，大小和原图片的大小相等*/
	result.convertTo(result, CV_8UC1, 1.0, 0);
	result = result(Rect(0, 0, image.cols, image.rows));
	imshow("经过理想高通滤波后的图片", result);

}
//快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst)
{
	//得到Mat类型
	Mat src = _src.getMat();

	//判断位深
	CV_Assert(src.type() == CV_32FC1 || src.type() == CV_64FC1);
	CV_Assert(src.channels() == 1 || src.channels() == 2);

	//为了进行快速的傅里叶变换，我们经行和列的扩充,找到最合适扩充值
	Mat padded;
	int rPadded = getOptimalDFTSize(src.rows);
	int cPadded = getOptimalDFTSize(src.cols);

	//进行边缘扩充,扩充值为零
	copyMakeBorder(src, padded, 0, rPadded - src.rows, 0, cPadded - src.cols, BORDER_CONSTANT, Scalar::all(0));

	//快速的傅里叶变换（双通道：用于存储实部 和 虚部）
	dft(padded, _dst, DFT_COMPLEX_OUTPUT);
}
//得到傅里叶谱:输入的是傅里叶变换,输出是傅里叶谱
void fourierSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	//判断傅里叶变换是两个通道
	CV_Assert(_srcFFT.channels() == 2);

	//分配内存
	Mat dstSpectrum;
	dstSpectrum.create(_srcFFT.size(), _srcFFT.type());

	//分离通道
	vector<Mat> imageCenterFFT2Channel;
	split(_srcFFT, imageCenterFFT2Channel);

	//计算傅里叶变换的
	magnitude(imageCenterFFT2Channel[0], imageCenterFFT2Channel[1], dstSpectrum);

	//做一次对比度的拉伸
	log(dstSpectrum + 1, dstSpectrum);

	//归一化
	normalize(dstSpectrum, dstSpectrum, 0, 1, NORM_MINMAX);

	//为了进行灰度级显示，做类型转换
	dstSpectrum.convertTo(_dstSpectrum, CV_8UC1, 255, 0);
}
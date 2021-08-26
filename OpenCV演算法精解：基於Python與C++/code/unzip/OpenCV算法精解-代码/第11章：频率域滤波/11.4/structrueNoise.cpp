#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
Mat image;//输入的图像矩阵
Mat fImageFFT;//图像的快速傅里叶变换
Point maxLoc;//傅里叶谱的最大值的坐标（中心点坐标）
//快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst);
string windowName = "幅度谱的灰度级";
//傅里叶变换的傅里叶谱
Mat fImageFFT_spectrum;
//鼠标事件
bool drawing_box = false;
Point downPoint;
Rect rectFilter;
bool gotRectFilter = false;
void mouseRectHandler(int event, int x, int y, int, void*)
{
	switch (event)
	{
		//按下鼠标左键
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		//记录起点
		downPoint = Point(x, y);
		break;
		//移动鼠标
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			//鼠标移动到 downPoint 的右下角
			if (x >= downPoint.x && y >= downPoint.y)
			{
				rectFilter.x = downPoint.x;
				rectFilter.y = downPoint.y;
				rectFilter.width = x - downPoint.x;
				rectFilter.height = y - downPoint.y;
			}
			//鼠标移到到 downPoint 的右上角
			if (x >= downPoint.x && y <= downPoint.y)
			{
				rectFilter.x = downPoint.x;
				rectFilter.y = y;
				rectFilter.width = x - downPoint.x;
				rectFilter.height = downPoint.y - y;
			}
			//鼠标移动到 downPoint 的左上角
			if (x <= downPoint.x && y <= downPoint.y)
			{
				rectFilter.x = x;
				rectFilter.y = y;
				rectFilter.width = downPoint.x - x;
				rectFilter.height = downPoint.y - y;
			}
			//鼠标移动到 downPoint 的左下角
			if (x <= downPoint.x && y >= downPoint.y)
			{
				rectFilter.x = x;
				rectFilter.y = downPoint.y;
				rectFilter.width = downPoint.x - x;
				rectFilter.height = y - downPoint.y;
			}
		}
		break;
	//松开鼠标左键
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		gotRectFilter = true;
		break;
	default:
		break;
	}
}

//幅度谱
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
//幅度谱的灰度级显示
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
int main(int argc, char*argv[])
{
	/* -- 第一步：读入图像矩阵 -- */
	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("原图", image);
	Mat fImage;
	image.convertTo(fImage, CV_32FC1, 1.0, 0.0);
	/* -- 第二步:图像矩阵的每一个数乘以 (-1)^(r+c) -- */
	for (int r = 0; r < fImage.rows; r++)
	{
		for (int c = 0; c < fImage.cols; c++)
		{
			if ((r + c) % 2)
				fImage.at<float>(r, c) *= -1;
		}
	}
	/* -- 第三、四步：快速傅里叶变换 -- */
	fft2Image(fImage, fImageFFT);
	//傅里叶谱
	Mat amplSpec;
	amplitudeSpectrum(fImageFFT, amplSpec);
	//傅里叶谱的灰度级显示
	Mat spectrum = graySpectrum(amplSpec);
	//找到傅里叶谱的最大值的坐标
	minMaxLoc(amplSpec, NULL, NULL, NULL, &maxLoc);
	/* -- 第五步：自定义滤波 -- */
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	setMouseCallback(windowName, mouseRectHandler, NULL);
	for (;;)
	{
		spectrum(rectFilter).setTo(0);
		/* -- 第六步：自定义滤波器与傅里叶变换点乘 -- */
		fImageFFT(rectFilter).setTo(Scalar::all(0));
		imshow(windowName, spectrum);
		//按下 "Esc" 键退出编辑
		if (waitKey(10)== 27)
			break;
	}
	/* -- 第七、八步：傅里叶逆变换，并只保留实部 -- */
	Mat result;
	dft(fImageFFT, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* -- 第九步：同乘以 (-1)^(r+c) --*/
	int rows = result.rows;
	int cols = result.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	//数据类型转换
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/* -- 第十步：裁剪图片，取左上部*/
	result = result(Rect(0, 0, image.cols, image.rows));
	imshow("经过自定义滤波后的图片", result);
	waitKey(0);
	return 0;
}
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

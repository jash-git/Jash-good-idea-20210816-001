#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat image;//输入的图像矩阵
Mat fImageFFT;//图像的快速傅里叶变换
Point maxLoc;//傅里叶谱的最大值的坐标
int radius = 50;//径向中心
const int Max_RADIUS = 100;
int bandWid = 40;//带宽
const int MAX_BANDWID = 50;//最大带宽
Mat brFilter;//带阻滤波器
int brType = 0;//带阻滤波器的类型
const int MAX_BPTYPE = 2;
Mat fImageFFT_brFilter;//带阻傅里叶变换
Mat fImageFFT_brFilter_spectrum;//带阻傅里叶变换的傅里叶谱
Mat result;//带阻低通滤波后的效果
string brFilterspectrum = "带阻傅里叶谱";
//快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst);
//傅里叶谱的灰度级显示：输入的是傅里叶变换，输出是傅里叶谱的灰度级
void fourierSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
void callback_brFilter(int, void*);
//带阻滤波的种类
//枚举类型：理想带阻滤波器,，巴特沃斯带阻滤波器，高斯带阻滤波器
enum BRFILTER_TYPE { IBR_FILTER = 0, BBR_FILTER = 1, GBR_FILTER = 2 };
//构建带阻滤波器
Mat createBRFilter(Size _size, Point center, float _radius, float _bandWidth, int type, int n = 2);
int main(int argc, char*argv[])
{
	/* -- 第一步：读入图像矩阵 -- */
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		return -1;
	}
	Mat fImage;
	image.convertTo(fImage, CV_32FC1, 1.0, 0.0);
	/* -- 第二步：图像矩阵的每一个数乘以 (-1)^(r+c) -- */
	for (int r = 0; r < fImage.rows; r++)
	{
		for (int c = 0; c < fImage.cols; c++)
		{
			if ((r + c) % 2)
				fImage.at<float>(r, c) *= -1;
		}
	}
	/* -- 第三步：快速傅里叶变换 -- */
	fft2Image(fImage, fImageFFT);
	//傅里叶变换的傅里叶谱
	Mat fImageFFT_spectrum;
	//傅里叶谱的灰度级显示
	fourierSpectrum(fImageFFT, fImageFFT_spectrum);
	//找到傅里叶谱的最大值的坐标
	minMaxLoc(fImageFFT_spectrum, NULL, NULL, NULL, &maxLoc);
	/* -- 带阻滤波 -- */
	namedWindow(brFilterspectrum,WINDOW_AUTOSIZE);
	createTrackbar("带阻类型:", brFilterspectrum, &brType, MAX_BPTYPE, callback_brFilter);
	createTrackbar("径向中心:", brFilterspectrum, &radius, Max_RADIUS, callback_brFilter);
	createTrackbar("带宽:", brFilterspectrum, &bandWid, MAX_BANDWID, callback_brFilter);
	callback_brFilter(0, 0);
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
void callback_brFilter(int, void*)
{
	/* -- 第四步：构造带阻滤波器 -- */
	brFilter = createBRFilter(fImageFFT.size(), maxLoc, radius, bandWid, brType);
	/* -- 第五步：带阻滤波器和图像快速傅里叶变换点乘 --*/
	fImageFFT_brFilter.create(fImageFFT.size(), fImageFFT.type());
	for (int r = 0; r < fImageFFT_brFilter.rows; r++)
	{
		for (int c = 0; c < fImageFFT_brFilter.cols; c++)
		{
			//分别取出当前位置的快速傅里叶变换和理想低通滤波器的值
			Vec2f temp_fImageFFT = fImageFFT.at<Vec2f>(r, c);
			float temp_brFilter = brFilter.at<float>(r, c);

			//带阻滤波器和图像的快速傅里叶变换对应位置相乘
			fImageFFT_brFilter.at<Vec2f>(r, c) = temp_fImageFFT*temp_brFilter;
		}
	}
	//显示带通傅里叶谱
	fourierSpectrum(fImageFFT_brFilter, fImageFFT_brFilter_spectrum);
	imshow(brFilterspectrum, fImageFFT_brFilter_spectrum);
	imwrite("brSpectrum.jpg", fImageFFT_brFilter_spectrum);
	/* -- 第六步：对带阻傅里叶变换执行傅里叶逆变换，并只取实部 -- */
	dft(fImageFFT_brFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* -- 第七步：同乘以(-1)^(x+y) -- */
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/*--第八步:截取左上部分,大小等于输入图像的大小*/
	result = result(Rect(0, 0, image.cols, image.rows)).clone();
	imshow("经过带阻低通滤波后的图片", result);
	imwrite("brresult.jpg", result);
}

//求傅里叶谱的灰度级显示:输入的是傅里叶变换,输出是傅里叶谱的灰度级
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
//构造带阻滤波器
Mat createBRFilter(Size _size, Point center, float _radius, float _bandWidth, int type, int n)
{
	Mat _bpFilter(_size, CV_32FC1);
	int rows = _size.height;
	int cols = _size.width;
	CV_Assert(_bandWidth / 2 <= _radius);
	//构造理想带阻滤波器
	if (type == IBR_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (sqrt(norm2) <= _radius + _bandWidth / 2 && sqrt(norm2) >= _radius - _bandWidth / 2)
					_bpFilter.at<float>(r, c) = 0;
				else
					_bpFilter.at<float>(r, c) = 1;
			}
		}
	}
	//构造巴特沃斯带阻滤波器
	if (type == BBR_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c<cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (norm2 != pow(_radius, 2))
					_bpFilter.at<float>(r, c) = 1.0 / (1.0 + pow(sqrt(norm2)*_bandWidth / (norm2 - pow(_radius, 2)), 2 * n));
				else
					_bpFilter.at<float>(r, c) = 0;
			}
		}
	}
	//构造高斯带阻滤波
	if (type == GBR_FILTER)
	{
		for (int r = 0; r< rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (norm2 != 0)
					_bpFilter.at<float>(r, c) = 1.0 - exp(-pow((norm2 - pow(_radius, 2)) / (_bandWidth*sqrt(norm2)), 2));
				else
					_bpFilter.at<float>(r, c) = 1;
			}
		}
	}
	return _bpFilter;
}
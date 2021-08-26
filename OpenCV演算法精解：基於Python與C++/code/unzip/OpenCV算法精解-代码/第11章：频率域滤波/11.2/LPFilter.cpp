#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat I;//输入的图像矩阵
Mat F;//图像的快速傅里叶变换
Point maxLoc;//傅里叶谱的最大值的坐标
int radius = 20;//截断频率
const int Max_RADIUS = 100;//设置最大的截断频率
Mat lpFilter;//低通滤波器
int lpType = 0;//低通滤波器的类型
const int MAX_LPTYPE = 2;
Mat F_lpFilter;//低通傅里叶变换
Mat FlpSpectrum;//低通傅里叶变换的傅里叶谱灰度级
Mat result;//低通滤波后的效果
string lpFilterspectrum = "低通傅里叶谱";//显示窗口的名称
//快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst);
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
void callback_lpFilter(int, void*);
/*
低通滤波的类型：
(理想低通滤波器，巴特沃斯低通滤波器，高斯低通滤波器)
*/
enum LPFILTER_TYPE { ILP_FILTER = 0, BLP_FILTER = 1, GLP_FILTER = 2 };
//构建低通滤波器
Mat createLPFilter(Size size, Point center, float radius, int type, int n=2);
int main(int argc, char*argv[])
{
	/* -- 第一步：读入图像矩阵 -- */
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	imwrite("I1.jpg", I);
	//数据类型转换，转换为 浮点型
	Mat fI;
	I.convertTo(fI, CV_32FC1, 1.0, 0.0);
	/* -- 第二步：每一个数乘以(-1)^(r+c) -- */
	for (int r = 0; r < fI.rows; r++)
	{
		for (int c = 0; c < fI.cols; c++)
		{
			if ((r + c) % 2)
				fI.at<float>(r, c) *= -1;
		}
	}
	/* -- 第三、四步：补零和快速傅里叶变换 -- */
	fft2Image(fI, F);
	//傅里叶谱
	Mat amplSpec;
	amplitudeSpectrum(F, amplSpec);
	//傅里叶谱的灰度级显示
	Mat spectrum = graySpectrum(amplSpec);
	imshow("原傅里叶谱的灰度级显示", spectrum);
	imwrite("spectrum.jpg", spectrum);
	//找到傅里叶谱的最大值的坐标
	minMaxLoc(spectrum, NULL, NULL, NULL, &maxLoc);
	/* -- 低通滤波 -- */
	namedWindow(lpFilterspectrum, WINDOW_AUTOSIZE);
	createTrackbar("低通类型:", lpFilterspectrum, &lpType, MAX_LPTYPE, callback_lpFilter);
	createTrackbar("半径:", lpFilterspectrum, &radius, Max_RADIUS, callback_lpFilter);
	callback_lpFilter(0, 0);
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
//回调函数：调整低通滤波的类型，及截断频率
void callback_lpFilter(int, void*)
{
	/* -- 第五步：构造低通滤波器 -- */
	lpFilter = createLPFilter(F.size(), maxLoc, radius, lpType, 2);
	/*-- 第六步：低通滤波器和图像快速傅里叶变换点乘 --*/
	F_lpFilter.create(F.size(), F.type());
	for (int r = 0; r < F_lpFilter.rows; r++)
	{
		for (int c = 0; c < F_lpFilter.cols; c++)
		{
			//分别取出当前位置的快速傅里叶变换和理想低通滤波器的值
			Vec2f F_rc = F.at<Vec2f>(r, c);
			float lpFilter_rc = lpFilter.at<float>(r, c);
			//低通滤波器和图像的快速傅里叶变换对应位置相乘
			F_lpFilter.at<Vec2f>(r, c) = F_rc*lpFilter_rc;
		}
	}

	//低通傅里叶变换的傅里叶谱
	amplitudeSpectrum(F_lpFilter,FlpSpectrum);
	//低通傅里叶谱的灰度级的显示
	FlpSpectrum = graySpectrum(FlpSpectrum);
	imshow(lpFilterspectrum, FlpSpectrum);
	imwrite("FlpSpectrum.jpg", FlpSpectrum);
	/* -- 第七、八步：对低通傅里叶变换执行傅里叶逆变换，并只取实部 -- */
	dft(F_lpFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* -- 第九步：同乘以(-1)^(x+y) -- */
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	//注意将结果转换 CV_8U 类型
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/* -- 第十步：截取左上部分,大小等于输入图像的大小 --*/
	result = result(Rect(0, 0, I.cols, I.rows)).clone();
	imshow("经过低通滤波后的图片", result);
	imwrite("lF.jpg", result);
}
//构造低通滤波器
Mat createLPFilter(Size size, Point center, float radius, int type, int n=2)
{
	Mat lpFilter = Mat::zeros(size, CV_32FC1);
	int rows = size.height;
	int cols = size.width;
	if (radius <= 0)
		return lpFilter;
	//构造理想低通滤波器
	if (type == ILP_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (sqrt(norm2) < radius)
					lpFilter.at<float>(r, c) = 1;
				else
					lpFilter.at<float>(r, c) = 0;
			}
		}
	}
	//构造巴特沃斯低通滤波器
	if (type == BLP_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c<cols; c++)
			{
				lpFilter.at<float>(r, c) = float(1.0 / (1.0 + pow(sqrt(pow(r - center.y, 2.0) + pow(c - center.x, 2.0)) /radius, 2.0*n)));
			}
		}
	}
	//构造高斯低通滤波
	if (type == GLP_FILTER)
	{
		for (int r = 0; r< rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				lpFilter.at<float>(r, c) = float(exp(-(pow(c - center.x, 2.0) + pow(r - center.y, 2.0)) / (2 * pow(radius, 2.0))));
			}
		}
	}
	return lpFilter;
}
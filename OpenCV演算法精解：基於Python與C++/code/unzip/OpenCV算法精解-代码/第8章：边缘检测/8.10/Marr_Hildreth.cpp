#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//构建 LoG 算子
Mat createLoGKernel(float sigma, Size ksize);
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
//零交叉点：方法1
void zero_cross_defalut(InputArray _src, OutputArray _dst);
//零交叉点：方法2
void zero_cross_mean(InputArray _src, OutputArray _dst);
//零交叉点的计算方法
enum ZERO_CROSS_TYPE { ZERO_CROSS_DEFALUT = 0, ZERO_CROSS_MEAN = 1 };
// Marr_Hildreth 边缘检测算法
Mat Marr_Hildreth(InputArray image, Size loGSize, float sigma, ZERO_CROSS_TYPE type);

//输入的图像
Mat image;
//输出的边缘图像
Mat marrHiImage;
//窗口的半径
int halfWin = 2;
const int MAX_HALFWIN = 30;
int sigma = 1;
const int MAX_SIGMA = 100;
void callBack_win_sig(int, void*)
{
	//LoG 算子窗口的大小为 (2*halfWin+1,2*halfWin+1)，标准差为  sigma/10.0
	marrHiImage = Marr_Hildreth(image, Size(2 * halfWin + 1, 2 * halfWin + 1), sigma / 10.0, ZERO_CROSS_DEFALUT);
	imshow("Marr_Hildreth 边缘检测", marrHiImage);
}
//主函数
int main(int argc, char*argv[])
{
	//输入图像矩阵
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有图片" << endl;
		return -1;
	}
	imshow("原图", image);
	namedWindow("Marr_Hildreth 边缘检测", WINDOW_AUTOSIZE);
	createTrackbar("窗口半径：", "Marr_Hildreth 边缘检测", &halfWin, MAX_HALFWIN, callBack_win_sig);
	createTrackbar("标准差：", "Marr_Hildreth 边缘检测", &sigma, MAX_SIGMA, callBack_win_sig);
	callBack_win_sig(0, 0);
	waitKey(0);
	return 0;
}
//构建 LoG 卷积核，ksize 的宽和高均为奇数
Mat createLoGKernel(float sigma, Size ksize)
{
	// LoG 算子的宽高，且两者均为奇数
	int winH = ksize.height;
	int winW = ksize.width;
	CV_Assert(winH >= 1 && winW >= 1);
	CV_Assert(winH % 2 == 1 && winW % 2 == 1);
	//方差
	float sigmaSquare = pow(sigma, 2);
	//LoG 核
	Mat logKernel(ksize, CV_32FC1);
	//中心点的坐标
	int cr = (winH - 1) / 2;
	int cc = (winW - 1) / 2;
	for (int r = 0; r< winH; r++)
	{
		for (int c = 0; c < winW; c++)
		{
			float norm2 = pow(float(r - cr), 2) + pow(float(c - cc), 2);
			logKernel.at<float>(r, c) = 1.0 / sigmaSquare*(norm2 / sigmaSquare - 2)*exp(-norm2 / (2 * sigmaSquare));
		}
	}
	return logKernel;
}

//零交叉点:方法1
void zero_cross_defalut(InputArray _src, OutputArray _dst)
{
	Mat src = _src.getMat();
	//判断位深
	CV_Assert(src.type() == CV_32FC1);
	_dst.create(src.size(), CV_8UC1);
	Mat dst = _dst.getMat();
	//输入图像矩阵的宽高
	int rows = src.rows;
	int cols = src.cols;
	//零交叉点
	for (int r = 1; r < rows - 2; r++)
	{
		for (int c = 1; c < cols - 2; c++)
		{
			//上 / 下方向
			if (src.at<float>(r - 1, c)*src.at<float>(r + 1, c) < 0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
			//左 / 右方向
			if (src.at<float>(r, c - 1) * src.at<float>(r, c + 1) < 0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
			//左上 / 右下方向
			if (src.at<float>(r - 1, c - 1)*src.at<float>(r + 1, c + 1) < 0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
			//右上 / 左下 方向
			if (src.at<float>(r - 1, c + 1)*src.at<float>(r + 1, c - 1)<0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
		}
	}
}

//零交叉：方法2
void zero_cross_mean(InputArray _src, OutputArray _dst)
{
	Mat src = _src.getMat();
	//判断位深
	_dst.create(src.size(), CV_8UC1);
	Mat dst = _dst.getMat();
	int rows = src.rows;
	int cols = src.cols;
	double minValue;
	double maxValue;
	//存储四个方向的均值
	Mat temp(1, 4, CV_32FC1);
	//零交叉点
	for (int r = 0 + 1; r < rows - 1; r++)
	{
		for (int c = 0 + 1; c < cols - 1; c++)
		{
			//左上方
			Mat left_top(src, Rect(c - 1, r - 1, 2, 2));
			temp.at<float>(0, 0) = mean(left_top)[0];
			//右上方
			Mat right_top(src, Rect(c, r - 1, 2, 2));
			temp.at<float>(0, 1) = mean(right_top)[0];
			//左下方
			Mat left_bottom(src, Rect(c - 1, r, 2, 2));
			temp.at<float>(0, 2) = mean(left_top)[0];
			//右下方
			Mat right_bottom(src, Rect(c, r, 2, 2));
			temp.at<float>(0, 3) = mean(right_bottom)[0];
			minMaxLoc(temp, &minValue, &maxValue);
			//最大值和最小值异号，为过零点
			if (minValue*maxValue < 0)
				dst.at<uchar>(r, c) = 255;
		}
	}
}
// Marr_Hildreth 边缘检测算法
Mat Marr_Hildreth(InputArray image, Size loGSize, float sigma, ZERO_CROSS_TYPE type)
{
	//第一步：创建 LoG 算子
	Mat loGKernel = createLoGKernel(sigma, loGSize);
	//第二步：图像 和 LoG 算子的卷积
	Mat img_Cov_loGKernel;
	conv2D(image, loGKernel, img_Cov_loGKernel, CV_32FC1, Point(-1, -1), BORDER_CONSTANT);
	//第三步：过零点
	Mat zeroCrossImage;
	switch (type)
	{
	case ZERO_CROSS_DEFALUT:
		zero_cross_defalut(img_Cov_loGKernel, zeroCrossImage);
		break;
	case ZERO_CROSS_MEAN:
		zero_cross_mean(img_Cov_loGKernel, zeroCrossImage);
		break;
	default:
		CV_Error(CV_StsBadArg, "Unknown ZERO_CROSS type");
	}
	return zeroCrossImage;
}

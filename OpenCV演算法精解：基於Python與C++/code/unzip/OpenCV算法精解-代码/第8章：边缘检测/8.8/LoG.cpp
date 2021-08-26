#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//得到一维的 （x^2 /(2*sigma^2)-1）Gauss(x,sigma) 和 一维的 Gauss(x,sigma)
void getSepLoGKernel(float sigma,int length,Mat & kernelX,Mat & kernelY)
{
	//分配内存
	kernelX.create(Size(length, 1), CV_32FC1);
	kernelY.create(Size(1, length), CV_32FC1);
	int center = (length - 1) / 2;
	double sigma2 = pow(sigma, 2.0);
	double cofficient = 1.0 / (sqrt(2 * CV_PI)*sigma);
	for (int c = 0; c < length; c++)
	{
		float norm2 = pow(c - center, 2.0);
		kernelY.at<float>(c,0) = cofficient*exp(-norm2 / (2 * sigma2));
		kernelX.at<float>(0, c) = (norm2 / sigma2 - 1.0)*kernelY.at<float>(c, 0);
	}
}
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
/*可分离的离散二维卷积,先垂直方向的卷积，然后进行水平方向的卷积*/
void sepConv2D_Y_X(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与垂直方向卷积核的卷积
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	//上面得到的卷积结果，然后接着和水平方向的卷积核卷积
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}
/*可分离的离散二维卷积，先水平方向的卷积,然后接着进行垂直方向的卷积，最后的输出类型是 CV_32FC1 或者 CV_64FC1*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与水平方向卷积核的卷积
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, CV_32F, anchor, borderType);
	//上面得到的卷积结果，然后接着和垂直方向的卷积核卷积
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
// LoG 卷积
Mat LoG(InputArray image,float sigma,int win)
{
	Mat kernelX, kernelY;
	//得到两个分离核
	getSepLoGKernel(sigma, win, kernelX, kernelY);
	//先水平卷积再垂直卷积
	Mat covXY;
	sepConv2D_X_Y(image, covXY, CV_32FC1, kernelX, kernelY);
	//卷积核转置
	Mat kernelX_T = kernelX.t();
	Mat kernelY_T = kernelY.t();
	//先垂直卷积再水平卷积
	Mat covYX;
	sepConv2D_Y_X(image,covYX,CV_32FC1,kernelX_T,kernelY_T);
	//计算两个卷积结果的和，得到 LoG 卷积
	Mat LoGCov;
	add(covXY, covYX, LoGCov);
	return LoGCov;
}
int main(int argc, char*argv[])
{
	//输入图像
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	// LoG 卷积
	float sigma = 4;
	int win = 25;
	Mat loG = LoG(image, sigma, win);
	//数据类型转换，转换为 CV_8U
	/*
	// 二值边缘
	Mat threshEdge=Mat::zeros(loG.size(), CV_8UC1);
	int rows = threshEdge.rows;
	int cols = threshEdge.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (loG.at<float>(r, c) > 0)
				threshEdge.at<uchar>(r, c) = 255;
		}
	}
	*/
	//以 0 为阈值，生成边缘二值图
	Mat edge;
	threshold(loG, edge, 0, 255, THRESH_BINARY);
	imshow("二值边缘图", edge);
	waitKey(0);
	return 0;
}
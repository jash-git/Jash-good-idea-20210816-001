#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//构建高斯卷积算子
Mat createGaussKernel(float sigma, int H, int W)
{
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	if (sigma <= 0)
		sigma = sqrt(float(W + H));
	//第一步:构建 H 行 W 列的矩阵
	Mat gaussMatrix(Size(W, H), CV_32FC1);
	int cH = (H - 1) / 2;
	int cW = (W - 1) / 2;
	float coefficient = 1.0 / (sqrt(2 * CV_PI)*sigma);
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			float norm2 = pow(r - cH, 2.0) + pow(c - cW, 2.0);
			gaussMatrix.at<float>(r, c) = coefficient*exp(-norm2 / (2 * pow(sigma, 2)));
		}
	}
	//第二步：计算矩阵的和
	float sumGM = sum(gaussMatrix)[0];
	//第三步: gaussMatrix 除以和 sumGM
	Mat gaussKernel = gaussMatrix / sumGM;
	return gaussKernel;
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
//高斯平滑：返回的数据类型是浮点型
Mat  gaussBlur(const Mat & image, Size winSize, float sigma, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核的宽高均为奇数
	CV_Assert(winSize.width % 2 == 1 && winSize.height % 2 == 1);
	//构建垂直方向的高斯卷积算子
	Mat gKernel_y = getGaussianKernel(sigma, winSize.height, CV_64F);
	//构建水平方向的高斯卷积算子
	Mat gKernel_x = getGaussianKernel(sigma, winSize.width, CV_64F);
	gKernel_x = gKernel_x.t();//转置
	//分离的高斯卷积
	Mat blurImage;
	sepConv2D_Y_X(image, blurImage, CV_32FC1, gKernel_y, gKernel_x, Point(-1, -1));
	return blurImage;
}
int main(int argc, char*argv[])
{
	//输入图像矩阵
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有图片" << endl;
		return 0;
	}
	imshow("原图", image);
	/*如果输入的图像的是 8 位图*/
	Mat blurImage = gaussBlur(image, Size(21,21), 3);
	//数据类型转换
	for (int r = 0; r < image.rows; r++)
	{
		for (int c = 0; c < image.cols; c++)
		{
			float pixel = blurImage.at<float>(r, c);
			blurImage.at<float>(r, c) = roundf(pixel);
		}
	}
	blurImage.convertTo(blurImage, CV_8UC1);
	imshow("高斯平滑-8位图", blurImage);
	/*如果输入的图像是归一化的*/
	Mat image_0_1;
	image.convertTo(image_0_1, CV_32FC1, 1.0 / 255);
	Mat blurImage_0_1 = gaussBlur(image_0_1, Size(21, 21), 3);
	imshow("高斯平滑-0-1", blurImage_0_1);
	waitKey(0);
	return 0;
}
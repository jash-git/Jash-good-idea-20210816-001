#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
/*可分离的离散二维卷积,先水平方向的卷积,然后接着进行垂直方向的卷积*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与水平方向卷积核的卷积
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);
	//上面得到的卷积结果，然后接着和垂直方向的卷积核卷积，得到最终的输出
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
//高斯卷积
Mat gaussConv(Mat I,float sigma,int s)
{
	//创建水平方向上的非归一化的高斯核
	Mat xkernel = Mat::zeros(1, s, CV_32FC1);
	//中心位置
	int cs = (s - 1) / 2;
	//方差
	float sigma2 = pow(sigma, 2.0);
	for (int c = 0; c < s; c++)
	{
		float norm2 = pow(float(c - cs), 2.0);
		xkernel.at<float>(0, c) = exp(-norm2 / (2 * sigma2));
	}
	//将 xkernel 转置，得到垂直方向上的卷积核
	Mat ykernel = xkernel.t();
	//分离卷积核的卷积运算
	Mat gauConv;
	sepConv2D_X_Y(I, gauConv, CV_32F, xkernel, ykernel);
	gauConv.convertTo(gauConv, CV_32F, 1.0 / sigma2);
	return gauConv;
}
//高斯差分
Mat DoG(Mat I, float sigma, int s, float k=1.1)
{
	//与标准差为 sigma 的非归一化的高斯核卷积
	Mat Ig = gaussConv(I, sigma, s);
	//与标准差为 k*sigma 的非归一化的高斯核卷积
	Mat Igk = gaussConv(I, k*sigma, s);
	//两个高斯卷积结果做差
	Mat doG = Igk - Ig;
	return doG;
}
int main(int argc, char*argv[])
{
	//输入图像矩阵
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//高斯差分
	float sigma = 6;
	int s = 37;
	float k = 1.05;
	Mat doG=DoG(I, sigma, s, k);
	//阈值处理
	Mat edge;
	threshold(doG, edge, 0, 255, THRESH_BINARY);
	//显示二值边缘
	imshow("高斯差分边缘", edge);
	imwrite("DoG.jpg", edge);
	waitKey(0);
	return 0;
}
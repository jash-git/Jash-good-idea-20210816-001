#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
Mat edge;//边缘图
int Thresh = 255;//阈值
const int MAX_THRSH = 255;
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, CV_32FC1, kernelFlip, anchor, 0.0, borderType);
}
/*laplacian 卷积*/
void laplacian(InputArray src, OutputArray dst, int ddepth,int borderType = BORDER_DEFAULT)
{
	Mat lapKernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	conv2D(src, lapKernel, dst, ddepth, Point(-1, -1), borderType);
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;//阈值处理后的阈值
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRSH, cv::THRESH_BINARY);
	imshow("阈值处理后的边缘强度", thresh_edge);
}
//主函数
int main(int argc, char*argv[])
{
	/*第一步：输入灰度图像矩阵*/
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有图片" << endl;
		return -1;
	}
	/*第二步： laplacian 卷积*/
	Mat img_lap;
	laplacian(image, img_lap, CV_32FC1);
	//数据类型的转换，卷积结果的灰度级显示
	convertScaleAbs(img_lap, edge, 1, 0);
	imshow("边缘强度", edge);
	imwrite("img3_lap.jpg", edge);
	//阈值处理后的边缘强度
	namedWindow("阈值处理后的边缘强度", cv::WINDOW_AUTOSIZE);
	createTrackbar("阈值", "阈值处理后的边缘强度", &Thresh, MAX_THRSH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}
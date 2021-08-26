#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
Mat edge;//边缘图
int Thresh = 25;//阈值
const int MAX_THRESH = 255;
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, CV_32FC1, kernelFlip, anchor, 0.0, borderType);
}
/*roberts 卷积*/
void roberts(InputArray src, OutputArray dst, int ddepth, int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));
	Mat roberts_1 = (Mat_<float>(2, 2) << 1, 0, 0, -1);
	Mat roberts_2 = (Mat_<float>(2, 2) << 0, 1, -1, 0);
	//当 x 不等于零时，src 和 roberts_1 卷积
	if (x != 0)
	{
		conv2D(src, roberts_1, dst, ddepth, Point(0, 0), borderType);
	}
	//当 y 不等于零时，src 和 roberts_2 卷积
	if (y != 0)
	{
		conv2D(src, roberts_2, dst, ddepth, Point(0, 0), borderType);
	}
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;//阈值处理后的阈值
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRESH, cv::THRESH_BINARY);
	imshow("阈值处理后的边缘强度", thresh_edge);
	imwrite("thresh_edge.jpg", thresh_edge);
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
	/*第二步： roberts 卷积*/
	//图像矩阵和 roberts_1 卷积核卷积
	Mat img_roberts_1;
	roberts(image, img_roberts_1, CV_32FC1, 1, 0);
	//图像矩阵和 roberts_2 卷积核卷积
	Mat img_roberts_2;
	roberts(image, img_roberts_2, CV_32FC1, 0, 1);
	//两个卷积结果的灰度级显示
	Mat abs_img_roberts_1, abs_img_roberts_2;
	convertScaleAbs(img_roberts_1, abs_img_roberts_1, 1, 0);
	convertScaleAbs(img_roberts_2, abs_img_roberts_2, 1, 0);
	imshow("135°方向上的边缘", abs_img_roberts_1);
	imwrite("img_robert_135_edge.jpg", abs_img_roberts_1);
	imshow("45°方向上的边缘", abs_img_roberts_2);
	imwrite("img_robert_45_edge.jpg", abs_img_roberts_2);
	/*第三步：通过第二步得到的两个卷积结果，求出最终的边缘强度*/
	//这里采用平方根的方式
	Mat img_roberts_1_2, img_roberts_2_2;
	pow(img_roberts_1, 2.0, img_roberts_1_2);
	pow(img_roberts_2, 2.0, img_roberts_2_2);
	sqrt(img_roberts_1_2 + img_roberts_2_2, edge);
	//数据类型转换，边缘强度的灰度级显示
	edge.convertTo(edge, CV_8UC1);
	imshow("边缘强度", edge);
	imwrite("img_robert_edge.jpg", edge);
	//阈值处理后的边缘强度
	namedWindow("阈值处理后的边缘强度", cv::WINDOW_AUTOSIZE);
	createTrackbar("阈值", "阈值处理后的边缘强度", &Thresh, MAX_THRESH, callback_thresh);
	callback_thresh(0, 0);
	//显示浮雕效果
	Mat reliefFigure = img_roberts_1 + 128;
	Mat reliefImage;
	reliefFigure.convertTo(reliefImage, CV_8UC1);
	imshow("浮雕图效果", reliefImage);
	imwrite("reliefImage.jpg", reliefImage);
	waitKey(0);
	return 0;
}
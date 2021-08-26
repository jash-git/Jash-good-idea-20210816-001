#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
Mat edge;//边缘图
int Thresh = 255;//阈值
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
void scharr(InputArray src, OutputArray dst, int ddepth, int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));
	Mat scharr_x = (Mat_<float>(3, 3) << 3, 0, -3, 10, 0, -10, 3, 0, -3);
	Mat scharr_y = (Mat_<float>(3, 3) << 3, 10, 3, 0, 0, 0, -3, -10, -3);
	//当 x 不等于零时，src 和 scharr_x 卷积
	if (x != 0)
	{
		conv2D(src, scharr_x, dst, ddepth, Point(-1, -1),borderType);
	}
	//当 y 不等于零时，src 和 scharr_y 卷积
	if (y != 0)
	{
		conv2D(src, scharr_y, dst, ddepth, Point(-1, -1), borderType);
	}
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;//阈值处理后的阈值
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRESH, cv::THRESH_BINARY);
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
	/*第二步： scharr 卷积*/
	//图像矩阵和 scharr_x 卷积核卷积
	Mat img_scharr_x;
	scharr(image, img_scharr_x, CV_32FC1, 1, 0);
	//图像矩阵和 scharr_y 卷积核卷积
	Mat img_scharr_y;
	scharr(image, img_scharr_y, CV_32FC1, 0, 1);
	//两个卷积结果的灰度级显示
	Mat abs_img_scharr_x, abs_img_scharr_y;
	convertScaleAbs(img_scharr_x, abs_img_scharr_x, 1, 0);
	convertScaleAbs(img_scharr_y, abs_img_scharr_y, 1, 0);
	imshow("垂直方向的边缘", abs_img_scharr_x);
	imwrite("img1_sch_v_edge.jpg", abs_img_scharr_x);
	imshow("水平方向的边缘", abs_img_scharr_y);
	imwrite("img1_sch_h_edge.jpg", abs_img_scharr_y);
	/*第三步：通过第二步得到的两个卷积结果，求出最终的边缘强度*/
	//这里采用平方根的方式
	Mat img_scharr_x2, img_scharr_y2;
	pow(img_scharr_x, 2.0, img_scharr_x2);
	pow(img_scharr_y, 2.0, img_scharr_y2);
	sqrt(img_scharr_x2 + img_scharr_y2, edge);
	//数据类型转换，边缘强度的灰度级显示
	edge.convertTo(edge, CV_8UC1);
	imshow("边缘强度", edge);
	imwrite("img1_sch_edge.jpg", edge);
	//阈值处理后的边缘强度
	namedWindow("阈值处理后的边缘强度", cv::WINDOW_AUTOSIZE);
	createTrackbar("阈值", "阈值处理后的边缘强度", &Thresh, MAX_THRESH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}
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

/*可分离的离散二维卷积,先水平方向的卷积,然后接着进行垂直方向的卷积*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与水平方向卷积核的卷积
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);
	//上面得到的卷积结果，然后接着和垂直方向的卷积核卷积，得到最终的输出
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
/*可分离的离散二维卷积,先垂直方向的卷积，然后进行水平方向的卷积*/
void sepConv2D_Y_X(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与垂直方向卷积核的卷积
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	//上面得到的卷积结果，然后接着和水平方向的卷积核卷积，得到最终的输出
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}

/*
	prewitt卷积运算
*/
void prewitt(InputArray src,OutputArray dst, int ddepth,int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));
	//如果 x!=0，src 和 prewitt_x卷积核进行卷积运算
	if (x != 0)
	{
		//可分离的prewitt_x卷积核
		Mat prewitt_x_y = (Mat_<float>(3, 1) << 1, 1, 1);
		Mat prewitt_x_x = (Mat_<float>(1, 3) << 1, 0, -1);
		//可分离的离散的二维卷积
		sepConv2D_Y_X(src, dst, ddepth, prewitt_x_y, prewitt_x_x, Point(-1, -1), borderType);
	}
	if (y != 0)
	{
		//可分离的prewitt_y卷积核
		Mat prewitt_y_x = (Mat_<float>(1, 3) << 1, 1, 1);
		Mat prewitt_y_y = (Mat_<float>(3, 1) << 1, 0, -1);
		//可分离的离散二维卷积
		sepConv2D_X_Y(src, dst, ddepth, prewitt_y_x, prewitt_y_y, Point(-1, -1), borderType);
	}
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
	/*第一步:输入图像矩阵(灰度图)*/
	
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有图片" << endl;
		return -1;
	}

	/*第二步:previwitt卷积*/

	//图像矩阵和 prewitt_x卷积核的卷积
	Mat img_prewitt_x;
	prewitt(image, img_prewitt_x,CV_32FC1,1, 0);
	//图像矩阵与prewitt_y卷积核卷积
	Mat img_prewitt_y;
	prewitt(image, img_prewitt_y, CV_32FC1, 0, 1);

	/*第三步:水平方向和垂直方向的边缘强度*/
	//数据类型转换,边缘强度的灰度级显示
	Mat abs_img_prewitt_x, abs_img_prewitt_y;
	convertScaleAbs(img_prewitt_x, abs_img_prewitt_x, 1, 0);
	convertScaleAbs(img_prewitt_y, abs_img_prewitt_y, 1, 0);
	imshow("垂直方向的边缘", abs_img_prewitt_x);
	//imwrite("img1_v_edge.jpg", abs_img_prewitt_x);
	imshow("水平方向的边缘", abs_img_prewitt_y);
	//imwrite("img1_h_edge.jpg", abs_img_prewitt_y);
	/*第四步：通过第三步得到的两个方向的边缘强度,求出最终的边缘强度*/
	//这里采用平方根的方式
	Mat img_prewitt_x2, image_prewitt_y2;
	pow(img_prewitt_x,2.0,img_prewitt_x2);
	pow(img_prewitt_y,2.0,image_prewitt_y2);
	sqrt(img_prewitt_x2 + image_prewitt_y2, edge);
	//数据类型转换,边缘的强度灰度级显示
	edge.convertTo(edge, CV_8UC1);
	imshow("边缘强度",edge);
	//imwrite("img1_edge.jpg", edge);
	Mat tempedge;
	threshold(edge, tempedge, 25, MAX_THRSH, cv::THRESH_BINARY);
	imwrite("img3_thresh_edge_25.jpg", tempedge);
	//阈值处理后的边缘强度
	namedWindow("阈值处理后的边缘强度", cv::WINDOW_AUTOSIZE);
	createTrackbar("阈值", "阈值处理后的边缘强度", &Thresh,MAX_THRSH,callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}
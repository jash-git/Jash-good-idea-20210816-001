#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
Mat I;//原图
Mat pI;//投影变换后的图
Point2f IPoint,pIPoint;
int i = 0,j = 0;
Point2f src[4];//存储原坐标
Point2f dst[4];//存储对应变换的坐标
//通过以下鼠标事件，在原图中取四个坐标
void mouse_I(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		//记录坐标
		IPoint = Point2f(x, y);
		break;
	case CV_EVENT_LBUTTONUP:
		src[i] = IPoint;
		circle(I, src[i], 7, Scalar(0),3);//标记
		i += 1;
		break;
	default:
		break;
	}
}
//通过以下鼠标事件，要输出的图中取四个坐标
void mouse_pI(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		//记录坐标
		pIPoint = Point2f(x, y);
		break;
	case CV_EVENT_LBUTTONUP:
		dst[j] = pIPoint;
		circle(pI, dst[j], 7, Scalar(0), 3);//标记
		j += 1;
		break;
	default:
		break;
	}
}
int main(int argc, char*argv[])
{
	//输入原图
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return 0;
	//输出图像
	pI = 200 * Mat::ones(I.size(), CV_8UC1);
	//在原图窗口上，定义鼠标事件
	namedWindow("I", 1);
	setMouseCallback("I", mouse_I, NULL);
	//在输出窗口上，定义鼠标事件
	namedWindow("pI", 1);
	setMouseCallback("pI", mouse_pI, NULL);
	imshow("I", I);
	imshow("pI", pI);
	while(!(i == 4 && j == 4))
	{
		imshow("I", I);
		imshow("pI", pI);
		if (waitKey(50) == 'q')
			break;
	}
	imshow("I", I);
	imshow("pI", pI);
	imwrite("I.jpg", I);
	imwrite("pI.jpg", pI);
	//移除鼠标事件 
	setMouseCallback("I", NULL, NULL);
	setMouseCallback("pI", NULL, NULL);
	//计算投影变换矩阵
	Mat p = getPerspectiveTransform(src, dst);
	//投影变换
	Mat result;
	warpPerspective(I, result, p, pI.size());
	imshow("投影后的效果", result);
	imwrite("result.jpg", result);
	waitKey(0);
	return 0;
}

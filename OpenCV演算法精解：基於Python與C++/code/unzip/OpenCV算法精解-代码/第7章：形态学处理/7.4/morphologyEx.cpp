#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//输入图像
Mat I;
//输出图像
Mat d;
//结构元
Mat element;
string window = "形态学处理";
//结构元半径
int r = 1;
int MAX_R = 20;
//迭代次数
int i = 1;
int MAX_I = 20;
//回调函数，调节r和i
void callBack(int, void*)
{
	//创建结构元
	element = getStructuringElement(MORPH_RECT,Size(2*r+1,2*r+1));
	//形态学处理
	morphologyEx(I, d, cv::MORPH_HITMISS, element,Point(-1,-1),i);
	//显示形态处理的效果
	imshow(window, d);
}
int main(int argc, char*argv[])
{
	//输入图像
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return 0;
	//显示原图
	imshow("原图", I);
	//创建显示形态学结果显示窗口
	namedWindow(window, 1);
	//创建调节r的进度条
	createTrackbar("半径", window, &r, MAX_R, callBack);
	//创建调节i的进度条
	createTrackbar("迭代次数", window, &i, MAX_I, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}
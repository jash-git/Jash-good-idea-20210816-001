#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int mian(int argc, char*argv[])
{
	//输入图像
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//创建矩形结构元
	Mat s = cv::getStructuringElement(cv::MORPH_RECT, Size(3, 3));
	//腐蚀图像
	Mat E;
	cv::erode(I, E, s,Point(-1,-1),2);
	//显示图像
	imshow("I", I);
	imshow("erode", E);
	waitKey(0);
	return 0;
}
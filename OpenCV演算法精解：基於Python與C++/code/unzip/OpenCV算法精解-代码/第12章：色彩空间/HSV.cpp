#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//
Mat image;
Mat fImage;// image 归一化
Mat hsvImage;// BGR2HSV
Mat svImg;
//图像大小
int width, height;
//显示窗口
string winName = "调整饱和度和亮度";
int S = 0;
int V = 0;
int MAX_VALUE = 100;//调整步长为 1/100
void callBack_SV(int, void*);
int main(int argc, char*argv[])
{
	//输入彩色图像
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image.data || image.channels() != 3)
		return -1;
	imshow("原图", image);
	//图像大小
	width = image.cols;
	height = image.rows;
	// image 归一化
	image.convertTo(fImage, CV_32FC3, 1.0 / 255, 0);
	namedWindow(winName, WINDOW_AUTOSIZE);
	//调整和亮度
	createTrackbar("饱和度(S)", winName, &S, MAX_VALUE, callBack_SV);
	//调整饱和度
	createTrackbar("亮度(V)", winName, &V, MAX_VALUE, callBack_SV);
	callBack_SV(0, 0);
	waitKey(0);
	return 0;
}
void callBack_SV(int, void*)
{
	// 归一化 的 BGR 格式 转换为 HSV 格式
	// 0 =< H <= 360 ， 0=< S < = 1，0=< V <= 1
	cvtColor(fImage, hsvImage, COLOR_BGR2HSV);
	//
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//调整饱和度和亮度
			Vec3f hsv = hsvImage.at<Vec3f>(r, c);
			hsv = Vec3f(hsv[0],
				(1+S / double(MAX_VALUE))*hsv[1] > 1 ? 1 : (1 + S / double(MAX_VALUE))*hsv[1],
				(1+ V / double(MAX_VALUE))*hsv[2] > 1 ? 1 : (1 + V / double(MAX_VALUE))*hsv[2]);
			hsvImage.at<Vec3f>(r, c) = hsv;
		}
	}
	// HSV 转换为 RGB
	cvtColor(hsvImage, svImg, COLOR_HSV2BGR);
	//lsImg.convertTo(lsImg, CV_8UC1, 1.0, 0);
	imshow(winName, svImg);
}
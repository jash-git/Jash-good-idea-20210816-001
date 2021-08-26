#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat image;//输入的彩色图像
Mat fImage;// image 归一化后的结果
Mat hlsImage;// BGR2HLS
Mat lsImg;//调整饱和度和亮度后图像
//图像大小
int width, height;
//显示窗口
string winName = "调整饱和度和亮度";
int L=60;
int S=60;
int MAX_VALUE = 100;//调整步长为 1/100
void callBack_LS(int, void*);
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
	createTrackbar("饱和度(S)", winName, &S, MAX_VALUE, callBack_LS);
	//调整饱和度
	createTrackbar("亮度(L)", winName, &L, MAX_VALUE, callBack_LS);
	callBack_LS(0, 0);
	waitKey(0);
	return 0;
}
void callBack_LS(int, void*)
{
	// 归一化 的 BGR 格式 转换为 HLS 格式
	// 0 =< H <= 360 ， 0=< L < = 1，0=< S <= 1
	cvtColor(fImage, hlsImage, COLOR_BGR2HLS);
	//
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//调整亮度和亮度
			Vec3f hls = hlsImage.at<Vec3f>(r, c);
			// 通过加法
			/*
			hls = Vec3f(hls[0], 
				hls[1] +L/double(MAX_VALUE) > 1 ? 1 : hls[1] + L/double(MAX_VALUE), 
				hls[2] + S/double(MAX_VALUE) > 1 ? 1 : hls[2] + S/double(MAX_VALUE));
			*/
			//通过乘法
			hls = Vec3f(hls[0],
				(1 + L / double(MAX_VALUE))*hls[1] > 1 ? 1 : (1 + L / double(MAX_VALUE))*hls[1],
				(1 + S / double(MAX_VALUE))*hls[2] > 1 ? 1 : (1 + S / double(MAX_VALUE))*hls[2]
			);
			hlsImage.at<Vec3f>(r, c) = hls;
		}
	}
	// HLS 转换为 RGB
	cvtColor(hlsImage,lsImg, COLOR_HLS2BGR);
	lsImg.convertTo(lsImg, CV_8UC3, 255);
	imshow(winName, lsImg);
	imwrite("lsImg.jpg", lsImg);
}
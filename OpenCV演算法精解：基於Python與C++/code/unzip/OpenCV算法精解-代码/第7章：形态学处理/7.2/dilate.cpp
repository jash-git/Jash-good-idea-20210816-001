#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int r = 1;//结构元半径
int MAX_R = 20;//设置最大半径
Mat I;//输入图像
Mat D;//输出图像
//回调函数，调节 r
void callBack(int, void *)
{
	//创建只有垂直方向的矩形结构元
	Mat s = getStructuringElement(MORPH_RECT, Size(1, 2 * r + 1));
	//膨胀操作
	dilate(I, D, s);
	//显示膨胀结果
	imshow("dilate", D);
}
int main(int argc, char*argv[])
{
	//输入图像
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//显示原图
	imshow("I", I);
	//创建显示膨胀结果的显示窗口
	namedWindow("dilate", WINDOW_AUTOSIZE);
	// 创建调节 r 的进度条
	createTrackbar("半径", "dilate", &r, MAX_R, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}
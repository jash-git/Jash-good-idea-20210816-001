#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	//读入图像
	Mat img = imread(argv[1], IMREAD_ANYCOLOR);
	//旋转 90 180 270 
	Mat rImg;
	rotate(img, rImg, ROTATE_90_CLOCKWISE);
	//显示原图和旋转的结果
	imshow("原图", img);
	imshow("旋转", rImg);
	waitKey(0);
	return 0;
}
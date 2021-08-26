#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	//读入
	Mat src = imread(argv[1], IMREAD_ANYCOLOR);
	// 对数极坐标变换
	Mat dst;
	Point2f center(508, 503);
	float M = 100;
	logPolar(src, dst, center, M, WARP_FILL_OUTLIERS);
	//显示对数极坐标变换的效果
	imshow("对数极坐标变换", dst);
	imshow("原图", src);
	waitKey(0);
	return 0;
}
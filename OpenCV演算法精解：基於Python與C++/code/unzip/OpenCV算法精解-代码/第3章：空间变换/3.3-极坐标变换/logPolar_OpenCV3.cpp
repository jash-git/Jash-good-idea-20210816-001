#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	//����
	Mat src = imread(argv[1], IMREAD_ANYCOLOR);
	// ����������任
	Mat dst;
	Point2f center(508, 503);
	float M = 100;
	logPolar(src, dst, center, M, WARP_FILL_OUTLIERS);
	//��ʾ����������任��Ч��
	imshow("����������任", dst);
	imshow("ԭͼ", src);
	waitKey(0);
	return 0;
}
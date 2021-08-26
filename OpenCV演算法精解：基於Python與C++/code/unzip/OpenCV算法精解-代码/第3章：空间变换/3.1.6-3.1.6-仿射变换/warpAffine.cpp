#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(int argc, char* argv[])
{
	//输入图像
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	/*第一种方式：利用 warpAffine 进行缩放*/
	//缩放仿射矩阵，等比例缩小2倍
	Mat s = (Mat_<float>(2, 3) << 0.5, 0, 0, 0, 0.5, 0);
	Mat dst1;
	warpAffine(I, dst1,s,Size(I.cols/2,I.rows/2));//图像缩放
	/*第二种方式：利用 resize 等比例缩小两倍*/
	Mat dst2;
	resize(I, dst2, Size(I.cols / 2, I.rows / 2), 0.5, 0.5);
	imshow("I", I);
	imshow("warpAffine", dst1);
	imshow("resize", dst2);
	waitKey(0);
	return 0;
}
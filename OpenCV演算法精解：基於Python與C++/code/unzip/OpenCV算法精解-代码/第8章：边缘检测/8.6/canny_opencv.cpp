#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	// ‰»ÎÕºœÒ
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	//canny ±ﬂ‘µºÏ≤‚
	imwrite("image.jpg", image);
	Mat edge;
	Canny(image, edge, 60, 180, 3);
	imshow("cannyEdge", edge);
	imwrite("cannyEdge.jpg", edge);
	waitKey(0);
	return 0;
}
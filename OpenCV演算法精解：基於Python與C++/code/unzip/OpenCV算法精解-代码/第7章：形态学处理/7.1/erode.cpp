#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int mian(int argc, char*argv[])
{
	//����ͼ��
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//�������νṹԪ
	Mat s = cv::getStructuringElement(cv::MORPH_RECT, Size(3, 3));
	//��ʴͼ��
	Mat E;
	cv::erode(I, E, s,Point(-1,-1),2);
	//��ʾͼ��
	imshow("I", I);
	imshow("erode", E);
	waitKey(0);
	return 0;
}
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat img = imread(argv[1], IMREAD_ANYCOLOR);
	//��ת 90 180 270 
	Mat rImg;
	rotate(img, rImg, ROTATE_90_CLOCKWISE);
	//��ʾԭͼ����ת�Ľ��
	imshow("ԭͼ", img);
	imshow("��ת", rImg);
	waitKey(0);
	return 0;
}
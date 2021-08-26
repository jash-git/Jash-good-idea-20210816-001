#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
Mat image;//����ͼ��
int thresh = 100;
const int MAX_THRESH = 255;
//�ص��������ֶ�������ֵ
void callback_thresh(int, void*)
{
	Mat threshImage;
	threshold(image, threshImage, thresh, MAX_THRESH, cv::THRESH_BINARY);
	imshow("��ֵ�����Ķ�ֵͼ", threshImage);
}
int main(int argc, char*argv[])
{
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û������ͼƬ" << endl;
		return -1;
	}
	//��ֵ�����ı�Եǿ��
	namedWindow("��ֵ�����Ķ�ֵͼ", cv::WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", "��ֵ�����Ķ�ֵͼ", &thresh, MAX_THRESH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}
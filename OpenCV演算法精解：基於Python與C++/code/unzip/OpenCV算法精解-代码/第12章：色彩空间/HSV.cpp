#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//
Mat image;
Mat fImage;// image ��һ��
Mat hsvImage;// BGR2HSV
Mat svImg;
//ͼ���С
int width, height;
//��ʾ����
string winName = "�������ͶȺ�����";
int S = 0;
int V = 0;
int MAX_VALUE = 100;//��������Ϊ 1/100
void callBack_SV(int, void*);
int main(int argc, char*argv[])
{
	//�����ɫͼ��
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image.data || image.channels() != 3)
		return -1;
	imshow("ԭͼ", image);
	//ͼ���С
	width = image.cols;
	height = image.rows;
	// image ��һ��
	image.convertTo(fImage, CV_32FC3, 1.0 / 255, 0);
	namedWindow(winName, WINDOW_AUTOSIZE);
	//����������
	createTrackbar("���Ͷ�(S)", winName, &S, MAX_VALUE, callBack_SV);
	//�������Ͷ�
	createTrackbar("����(V)", winName, &V, MAX_VALUE, callBack_SV);
	callBack_SV(0, 0);
	waitKey(0);
	return 0;
}
void callBack_SV(int, void*)
{
	// ��һ�� �� BGR ��ʽ ת��Ϊ HSV ��ʽ
	// 0 =< H <= 360 �� 0=< S < = 1��0=< V <= 1
	cvtColor(fImage, hsvImage, COLOR_BGR2HSV);
	//
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//�������ͶȺ�����
			Vec3f hsv = hsvImage.at<Vec3f>(r, c);
			hsv = Vec3f(hsv[0],
				(1+S / double(MAX_VALUE))*hsv[1] > 1 ? 1 : (1 + S / double(MAX_VALUE))*hsv[1],
				(1+ V / double(MAX_VALUE))*hsv[2] > 1 ? 1 : (1 + V / double(MAX_VALUE))*hsv[2]);
			hsvImage.at<Vec3f>(r, c) = hsv;
		}
	}
	// HSV ת��Ϊ RGB
	cvtColor(hsvImage, svImg, COLOR_HSV2BGR);
	//lsImg.convertTo(lsImg, CV_8UC1, 1.0, 0);
	imshow(winName, svImg);
}
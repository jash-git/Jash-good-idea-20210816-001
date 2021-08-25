#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//Ϊ�����ڱ���������ʹ�ã��������ó�ȫ�ֵ�
int value;
void callBack(int, void*);  //�������ص�����
Mat img1, img2;

int main()
{
	img1 = imread("lena.png");
	if (!img1.data)
	{
		cout << "��ȷ���Ƿ�������ȷ��ͼ���ļ�" << endl;
		return -1;
	}
	namedWindow("�������ı�ͼ������");
	imshow("�������ı�ͼ������", img1);
	value = 100;  //����������ʱ�ĳ�ֵ
				  //����������
	createTrackbar("����ֵ�ٷֱ�", "�������ı�ͼ������", &value, 600, callBack, 0);
	waitKey();
}

static void callBack(int, void*)
{
	float a = value / 100.0;
	img2 = img1 * a;
	imshow("�������ı�ͼ������", img2);
}
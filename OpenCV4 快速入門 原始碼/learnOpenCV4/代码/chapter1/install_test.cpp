#include <opencv2\opencv.hpp>  //����OpenCV 4.0ͷ�ļ�
#include <iostream>

using namespace std;
using namespace cv;  //opencv�������ռ�

int main(int argc, char ** argv) 
{
	Mat img;  //����һ������ͼ�����
	img = imread("G:/opencv/lena.png");  //��ȡͼ�񣬸���ͼƬ����λ����д·������
	if (img.empty())  //�ж�ͼ���ļ��Ƿ����
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("test", img);  //��ʾͼ��
	waitKey(0);  //�ȴ���������
	return 0;  //�������
}
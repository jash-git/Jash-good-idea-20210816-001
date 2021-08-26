#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
#include<vector>
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//������ת����
	RotatedRect rRect(Point2f(200,200),Point2f(90,150),-60);
	//������ת���ε��ĸ����㣬�洢Ϊһ�� 4 �� 2 �еĵ�ͨ�� float ���͵� Mat
	Mat vertices;
	boxPoints(rRect, vertices);
	//��ӡ�ĸ�����
	cout << vertices << endl;
	//�ں�ɫ�����ϻ�������ת����
	Mat img=Mat::zeros(Size(400, 400), CV_8UC1);
	for (int i = 0; i < 4; i++)
	{
		//���ڵĵ�
		Point p1 = vertices.row(i);
		int j = (i + 1) % 4;
		Point p2 = vertices.row(j);
		//����ֱ��
		line(img, p1, p2, Scalar(255), 3);
	}
	//��ʾ��ת����
	imshow("��ת����", img);
	waitKey(0);
	return 0;
}
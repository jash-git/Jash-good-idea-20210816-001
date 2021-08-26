#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<vector>
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//��һ��������ͼ��
	Mat img = imread(argv[1], IMREAD_GRAYSCALE);
	if (!img.data)
		return -1;
	//�ڶ�������Ե��⣬�õ���Ե��ֵͼ
	GaussianBlur(img, img, Size(3, 3), 0.5);
	Mat binaryImg;
	Canny(img, binaryImg, 50, 200);
	imshow("��ʾ��Ե", binaryImg);
	imwrite("cannyEdge.jpg", binaryImg);
	//����������Ե������
	vector<vector<Point>> contours;
	vector<Vec4i> hei;
	findContours(binaryImg, contours, hei, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,Point(0,0));
	
	//���Ĳ�����ÿһ����������ϣ���������ת����
	int num = contours.size();//����������
	for (int i = 0; i < num; i++)
	{
		//��С���ֱ������
		Rect rect = boundingRect(Mat(contours[i]));
		if (rect.area()>2000)//ɸѡ��������� 10000 �ľ���
		{
			//��ԭͼ�л����������
			rectangle(img, rect, Scalar(255),2);
			cout << rect.area() << endl;
		}
	}
	imshow("img", img);
	imwrite("img0.jpg", img);
	waitKey(0);
	return 0;
 }
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat img1 = imread("left01.jpg");
	Mat img2 = imread("circle.png");
	if (!(img1.data && img2.data))
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}
	Mat gray1, gray2;
	cvtColor(img1, gray1, COLOR_BGR2GRAY);
	cvtColor(img2, gray2, COLOR_BGR2GRAY);

	//������Ŀ�ߴ�
	Size board_size1 = Size(9, 6);   //����궨���ڽǵ���Ŀ���У��У�
	Size board_size2 = Size(7, 7);   //Բ�α궨��Բ����Ŀ���У��У�

	//���ǵ�
	vector<Point2f> img1_points, img2_points;  
	findChessboardCorners(gray1, board_size1, img1_points);  //���㷽��궨��ǵ�
	findCirclesGrid(gray2, board_size2, img2_points);  //����Բ�α궨����

	//ϸ���ǵ�����
	find4QuadCornerSubpix(gray1, img1_points, Size(5, 5));  //ϸ������궨��ǵ�����
	find4QuadCornerSubpix(gray2, img2_points, Size(5, 5));  //ϸ��Բ�α궨��ǵ�����

	//���ƽǵ�����
	drawChessboardCorners(img1, board_size1, img1_points, true);
	drawChessboardCorners(img2, board_size2, img2_points, true);

	//��ʾ���
	imshow("���α궨��ǵ�����", img1);
	imshow("Բ�α궨��ǵ�����", img2);
	waitKey(0);
	return 0;
}
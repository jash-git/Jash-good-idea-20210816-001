#include <opencv2\opencv.hpp>
#include <fstream> 
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	//��ȡ����ͼ��
	vector<Mat> imgs;
	string imageName;
	ifstream fin("calibdata.txt");
	while (getline(fin,imageName))
	{
		Mat img = imread(imageName);
		imgs.push_back(img);
	}

	Size board_size = Size(9, 6);  //����궨���ڽǵ���Ŀ���У��У�
	vector<vector<Point2f>> imgsPoints;
	for (int i = 0; i < imgs.size(); i++)
	{
		Mat img1 = imgs[i];
		Mat gray1;
		cvtColor(img1, gray1, COLOR_BGR2GRAY);
		vector<Point2f> img1_points;
		findChessboardCorners(gray1, board_size, img1_points);  //���㷽��궨��ǵ�
		find4QuadCornerSubpix(gray1, img1_points, Size(5, 5));  //ϸ������궨��ǵ�����
		imgsPoints.push_back(img1_points);
	}

	//�������̸�ÿ���ڽǵ�Ŀռ���ά����
	Size squareSize = Size(10, 10);  //���̸�ÿ���������ʵ�ߴ�
	vector<vector<Point3f>> objectPoints;
	for (int i = 0; i < imgsPoints.size(); i++)
	{
		vector<Point3f> tempPointSet;
		for (int j = 0; j < board_size.height; j++)
		{
			for (int k = 0; k < board_size.width; k++)
			{
				Point3f realPoint;
				// ����궨��Ϊ��������ϵ��zƽ�棬��z=0
				realPoint.x = j*squareSize.width;
				realPoint.y = k*squareSize.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		objectPoints.push_back(tempPointSet);
	}

	/* ��ʼ��ÿ��ͼ���еĽǵ��������ٶ�ÿ��ͼ���ж����Կ��������ı궨�� */
	vector<int> point_number;
	for (int i = 0; i<imgsPoints.size(); i++)
	{
		point_number.push_back(board_size.width*board_size.height);
	}

	//ͼ��ߴ�
	Size imageSize;
	imageSize.width = imgs[0].cols;
	imageSize.height = imgs[0].rows;

	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));  //������ڲ�������
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));  //�������5������ϵ����k1,k2,p1,p2,k3
	vector<Mat> rvecs;  //ÿ��ͼ�����ת����
	vector<Mat> tvecs;  //ÿ��ͼ���ƽ����
	calibrateCamera(objectPoints, imgsPoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, 0);
	cout << "������ڲξ���=" << endl << cameraMatrix << endl;
	cout << "�������ϵ��" << distCoeffs << endl;
	waitKey(0);
	return 0;
}
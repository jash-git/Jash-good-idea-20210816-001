#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	//��ȡ����ͼ��
	Mat img = imread("left01.jpg");
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	vector<Point2f> imgPoints;
	Size boardSize = Size(9, 6);
	findChessboardCorners(gray, boardSize, imgPoints);  //���㷽��궨��ǵ�
	find4QuadCornerSubpix(gray, imgPoints, Size(5, 5));  //ϸ������궨��ǵ�����

	//�������̸�ÿ���ڽǵ�Ŀռ���ά����
	Size squareSize = Size(10, 10);  //���̸�ÿ���������ʵ�ߴ�
	vector<Point3f> PointSets;
	for (int j = 0; j < boardSize.height; j++)
	{
		for (int k = 0; k < boardSize.width; k++)
		{
			Point3f realPoint;
			// ����궨��Ϊ��������ϵ��zƽ�棬��z=0
			realPoint.x = j*squareSize.width;
			realPoint.y = k*squareSize.height;
			realPoint.z = 0;
			PointSets.push_back(realPoint);
		}
	}

	//����ǰ�ļ���õ����ڲξ���ͻ������
	Mat cameraMatrix = (Mat_<float>(3, 3) << 532.016297, 0, 332.172519,
		                                     0, 531.565159, 233.388075,
		                                     0, 0, 1);
	Mat distCoeffs = (Mat_<float>(1, 5) << -0.285188, 0.080097, 0.001274,
                                           - 0.002415, 0.106579);
	
	//��PnP�㷨������ת��ƽ����
	Mat rvec, tvec;
	solvePnP(PointSets, imgPoints, cameraMatrix, distCoeffs, rvec, tvec);
	cout << "��������ϵ�任���������ϵ����ת������" << rvec << endl;
	//��ת����ת����ת����
	Mat R;
	Rodrigues(rvec, R);
	cout << "��ת����ת������ת����" << endl << R << endl;

	//��PnP+Ransac�㷨������ת������ƽ������
	Mat rvecRansac, tvecRansac;
	solvePnPRansac(PointSets, imgPoints, cameraMatrix, distCoeffs, rvecRansac, tvecRansac);
	Mat RRansac;
	Rodrigues(rvecRansac, RRansac);
	cout << "��ת����ת������ת����" << endl << RRansac << endl;
	waitKey(0);
	return 0;
}
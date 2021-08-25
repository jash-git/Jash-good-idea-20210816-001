#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	/**********���������õ���ͼ���Ǵ����嵥10-10������궨ʱ�ĵ�һ��ͼ��**********/
	/***************����������Ǳ궨ʱ�õ���*****************/

	//����ǰ�ļ���õ����ڲξ���ͻ������
	Mat cameraMatrix = (Mat_<float>(3, 3) << 532.016297, 0, 332.172519,
		                                     0, 531.565159, 233.388075,
		                                     0, 0, 1);
	Mat distCoeffs = (Mat_<float>(1, 5) << -0.285188, 0.080097, 0.001274,
                                           - 0.002415, 0.106579);
	//�����嵥10-10�м���ĵ�һ��ͼ���������ϵ����������ϵ֮��Ĺ�ϵ
	Mat rvec = (Mat_<float>(1, 3) <<-1.977853, -2.002220, 0.130029);
	Mat tvec = (Mat_<float>(1, 3) << -26.88155,-42.79936, 159.19703);

	//���ɵ�һ��ͼ�����ڽǵ����ά��������
	Size boardSize = Size(9, 6);
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
	
	//������ά������������������ϵʱ��Ĺ�ϵ�����ڽǵ���������
	vector<Point2f> imagePoints;
	projectPoints(PointSets, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);


	/***********����ͼ�����ڽǵ����ʵ�������******************/
	Mat img = imread("left01.jpg");
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	vector<Point2f> imgPoints;
	findChessboardCorners(gray, boardSize, imgPoints);  //���㷽��궨��ǵ�
	find4QuadCornerSubpix(gray, imgPoints, Size(5, 5));  //ϸ������궨��ǵ�����

	//�������ֵ��ͼ���м������ʵʱ֮���ƽ�����
	float e = 0;
	for (int i = 0; i < imagePoints.size(); i++)
	{
		float eX = pow(imagePoints[i].x - imgPoints[i].x, 2);
		float eY = pow(imagePoints[i].y - imgPoints[i].y, 2);
		e = e + sqrt(eX + eY);
	}
	e = e / imagePoints.size();
	cout << "������������ʵ����֮������" << e << endl;
	waitKey(0);
	return 0;
}
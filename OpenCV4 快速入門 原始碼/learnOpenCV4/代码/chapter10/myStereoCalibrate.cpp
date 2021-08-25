#include <opencv2\opencv.hpp>
#include <fstream> 
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

//������̸��ڽǵ���ͼ��������ĺ���
void getImgsPoints(vector<Mat> imgs, vector<vector<Point2f>> &Points, Size boardSize)
{
	for (int i = 0; i < imgs.size(); i++)
	{
		Mat img1 = imgs[i];
		Mat gray1;
		cvtColor(img1, gray1, COLOR_BGR2GRAY);
		vector<Point2f> img1_points;
		findChessboardCorners(gray1, boardSize, img1_points);  //���㷽��궨��ǵ�
		find4QuadCornerSubpix(gray1, img1_points, Size(5, 5));  //ϸ������궨��ǵ�����
		Points.push_back(img1_points);
	}
}

int main()
{
	//��ȡ����ͼ��
	vector<Mat> imgLs;
	vector<Mat> imgRs;
	string imgLName;
	string imgRName;
	ifstream finL("steroCalibDataL.txt");
	ifstream finR("steroCalibDataR.txt");
	while (getline(finL, imgLName) && getline(finR, imgRName))
	{
		Mat imgL = imread(imgLName);
		Mat imgR = imread(imgRName);
		if (!imgL.data && !imgR.data)
		{
			cout << "��ȷ�Ƿ�������ȷ��ͼ���ļ�" << endl;
			return -1;
		}
		imgLs.push_back(imgL);
		imgRs.push_back(imgR);
	}

	//��ȡ���̸��ڽǵ����������ͼ���е�����
	Size board_size = Size(9, 6);  //����궨���ڽǵ���Ŀ���У��У�
	vector<vector<Point2f>> imgLsPoints;
	vector<vector<Point2f>> imgRsPoints;
	getImgsPoints(imgLs, imgLsPoints, board_size);  //�����Ӻ���
	getImgsPoints(imgRs, imgRsPoints, board_size);  //�����Ӻ���


													//�������̸�ÿ���ڽǵ�Ŀռ���ά����
	Size squareSize = Size(10, 10);  //���̸�ÿ���������ʵ�ߴ�
	vector<vector<Point3f>> objectPoints;
	for (int i = 0; i < imgLsPoints.size(); i++)
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

	//ͼ��ߴ�
	Size imageSize;
	imageSize.width = imgLs[0].cols;
	imageSize.height = imgLs[0].rows;

	Mat Matrix1, dist1, Matrix2, dist2, rvecs, tvecs;
	calibrateCamera(objectPoints, imgLsPoints, imageSize, Matrix1, dist1, rvecs, tvecs, 0);
	calibrateCamera(objectPoints, imgRsPoints, imageSize, Matrix2, dist2, rvecs, tvecs, 0);
	
	//���б궨
	Mat R, T, E, F;  //��ת����ƽ���������������󡢻�������
	stereoCalibrate(objectPoints, imgLsPoints, imgRsPoints, Matrix1, dist1, Matrix2, dist2, imageSize, R, T, E, F, CALIB_USE_INTRINSIC_GUESS);

	cout << "�����������ϵ����ת����" << endl << R << endl;
	cout << "�����������ϵ��ƽ��������" << endl << T << endl;
	waitKey(0);
	return 0;
}
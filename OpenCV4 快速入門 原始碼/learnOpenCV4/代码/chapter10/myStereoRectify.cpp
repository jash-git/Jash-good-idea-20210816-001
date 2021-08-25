#include <opencv2\opencv.hpp>
#include <fstream> 
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void getImgsPoints(vector<Mat> imgs, vector<vector<Point2f>> &imgsPoints, Size board_size)
{
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
		imgLs.push_back(imgL);
		imgRs.push_back(imgR);
	}

	Size board_size = Size(9, 6);  //����궨���ڽǵ���Ŀ���У��У�
	vector<vector<Point2f>> imgLsPoints;
	vector<vector<Point2f>> imgRsPoints;
	getImgsPoints(imgLs, imgLsPoints, board_size);
	getImgsPoints(imgRs, imgRsPoints, board_size);

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

	//˫Ŀ������б궨
	Mat R, T, E, F;
	stereoCalibrate(objectPoints, imgLsPoints, imgRsPoints, Matrix1, dist1, Matrix2, dist2, imageSize, R, T, E, F, CALIB_USE_INTRINSIC_GUESS);

	//����У���任����
	Mat R1, R2, P1, P2,Q;
	stereoRectify(Matrix1, dist1, Matrix2, dist2, imageSize, R, T, R1, R2, P1, P2, Q, 0);

	//����У��ӳ�����
	Mat map11, map12, map21, map22;
	initUndistortRectifyMap(Matrix1, dist1, R1, P1, imageSize, CV_16SC2, map11, map12);
	initUndistortRectifyMap(Matrix2, dist2, R2, P2, imageSize, CV_16SC2, map21, map22);

	for (int i = 0; i < imgLs.size(); i++)
	{
		//����У��ӳ��
		Mat img1r, img2r;
		remap(imgLs[i], img1r, map11, map12, INTER_LINEAR);
		remap(imgRs[i], img2r, map21, map22, INTER_LINEAR);

		//ƴ��ͼ��
		Mat result;
		hconcat(img1r, img2r, result);

		//����ֱ�ߣ����ڱȽ�ͬһ���ڽǵ�y���Ƿ�һ��
		line(result, Point(-1, imgLsPoints[i][0].y), Point(result.cols, imgLsPoints[i][0].y), Scalar(0, 0, 255), 2);
		imshow("У������", result);
		waitKey(0);
	}
	return 0;
}

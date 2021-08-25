#include <opencv2\opencv.hpp>
#include <iostream>
#include <fstream> 
#include <vector>

using namespace std;
using namespace cv;

//ʹ��initUndistortRectifyMap()������remap()����У��ͼ��
void initUndistAndRemap(vector<Mat> imgs,  //����ԭͼ������
	                    Mat cameraMatrix,  //����õ�������ڲ�
	                    Mat distCoeffs,    //����õ����������ϵ��
	                    Size imageSize,    //ͼ��ĳߴ�
	                    vector<Mat> &undistImgs)  //У��������ͼ��
{
	//����ӳ���������
	Mat R = Mat::eye(3, 3, CV_32F);
	Mat mapx = Mat(imageSize, CV_32FC1);
	Mat mapy = Mat(imageSize, CV_32FC1);
	initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, imageSize, CV_32FC1, mapx, mapy);

	//У��ͼ��
	for (int i = 0; i < imgs.size(); i++)
	{
		Mat undistImg;
		remap(imgs[i], undistImg, mapx, mapy, INTER_LINEAR);
		undistImgs.push_back(undistImg);
	}
}

//��undistort()����ֱ�Ӽ���У��ͼ��
void undist(vector<Mat> imgs,   //����ԭͼ������
	        Mat cameraMatrix,   //����õ�������ڲ�
	        Mat distCoeffs,     //����õ����������ϵ��
	        vector<Mat> &undistImgs)  //У��������ͼ��
{
	for (int i = 0; i < imgs.size(); i++)
	{
		Mat undistImg;
		undistort(imgs[i], undistImg, cameraMatrix, distCoeffs);
		undistImgs.push_back(undistImg);
	}
}

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

	//����ǰ�ļ���õ����ڲξ���
	Mat cameraMatrix = (Mat_<float>(3, 3) << 532.016297, 0, 332.172519, 
		                                     0, 531.565159, 233.388075, 
		                                     0, 0, 1);
	//����ǰ�ļ���õ����ڲξ���
	Mat distCoeffs = (Mat_<float>(1, 5) << -0.285188, 0.080097, 0.001274, -0.002415, 0.106579);
	vector<Mat> undistImgs;
	Size imageSize;
	imageSize.width = imgs[0].cols;
	imageSize.height = imgs[0].rows;

	//ʹ��initUndistortRectifyMap()������remap()����У��ͼ��
	initUndistAndRemap(imgs,cameraMatrix,distCoeffs,imageSize,undistImgs);

	//��undistort()����ֱ�Ӽ���У��ͼ����һ�д���ȡ��ע�ͼ���
	//undist(imgs, cameraMatrix, distCoeffs, undistImgs);

	//��ʾУ��ǰ���ͼ��
	for (int i = 0; i < imgs.size(); i++)
	{
		string windowNumber = to_string(i);
		imshow("δУ��ͼ��"+ windowNumber, imgs[i]);
		imshow("У����ͼ��"+ windowNumber, undistImgs[i]);
	}

	waitKey(0);
	return 0;
}
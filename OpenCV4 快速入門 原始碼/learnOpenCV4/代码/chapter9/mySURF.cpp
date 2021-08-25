#include <opencv2\opencv.hpp>
#include <xfeatures2d.hpp>  //SURF������ͷ�ļ�
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;  
using namespace xfeatures2d;  //SURF�����������ռ�

int main()
{
	Mat img = imread("lena.png");
	if (!img.data)
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}

	//����SURF�����������
	Ptr<SURF> surf = SURF::create(500,  //�ؼ�����ֵ
		                            4,  //4�������
		                            3,  //ÿ���������3��
		                         true,  //ʹ��128ά������
		                        false);  //����ؼ��㷽��

	//����SURF�ؼ���
	vector<KeyPoint> Keypoints;
	surf->detect(img, Keypoints);  //ȷ���ؼ���

	//����SURF������
	Mat descriptions;
	surf->compute(img, Keypoints, descriptions);  //����������
	
	//����������
	Mat imgAngel;
	img.copyTo(imgAngel);
	//���Ʋ����ǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, img,Scalar(255,255,255));
	//���ƺ��нǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, imgAngel, Scalar(255, 255, 255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//��ʾ���
	imshow("�����ǶȺʹ�С�Ľ��", img);
	imshow("���нǶȺʹ�С�Ľ��", imgAngel);
	waitKey(0); 
	return 0;
}
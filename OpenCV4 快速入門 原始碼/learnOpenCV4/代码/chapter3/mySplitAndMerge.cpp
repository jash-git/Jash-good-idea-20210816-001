#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat HSV;
	cvtColor(img, HSV, COLOR_RGB2HSV);
	Mat imgs0, imgs1, imgs2;  //���ڴ���������͵Ľ��
	Mat imgv0, imgv1, imgv2;  //���ڴ��vector���͵Ľ��
	Mat result0, result1, result2;  //��ͨ���ϲ��Ľ��

									//������������Ķ�ͨ��������ϲ�
	Mat imgs[3];
	split(img, imgs);
	imgs0 = imgs[0];
	imgs1 = imgs[1];
	imgs2 = imgs[2];
	imshow("RGB-Bͨ��", imgs0);  //��ʾ�����Bͨ��������ֵ
	imshow("RGB-Gͨ��", imgs1);  //��ʾ�����Gͨ��������ֵ
	imshow("RGB-Rͨ��", imgs2);  //��ʾ�����Rͨ��������ֵ
	imgs[2] = img;  //�������е�ͼ��ͨ������ɲ�ͳһ
	merge(imgs, 3, result0);  //�ϲ�ͼ��
							  //imshow("result0", result0);  //imshow�����ʾ4��ͨ������˽����Image Watch�в鿴
	Mat zero = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
	imgs[0] = zero;
	imgs[2] = zero;
	merge(imgs, 3, result1);  //���ڻ�ԭGͨ������ʵ������ϲ����Ϊ��ɫ
	imshow("result1", result1);  //��ʾ�ϲ����

								 //����vector�����Ķ�ͨ��������ϲ�
	vector<Mat> imgv;
	split(HSV, imgv);
	imgv0 = imgv.at(0);
	imgv1 = imgv.at(1);
	imgv2 = imgv.at(2);
	imshow("HSV-Hͨ��", imgv0);  //��ʾ�����Hͨ��������ֵ
	imshow("HSV-Sͨ��", imgv1);  //��ʾ�����Sͨ��������ֵ
	imshow("HSV-Vͨ��", imgv2);  //��ʾ�����Vͨ��������ֵ
	imgv.push_back(HSV);  //��vector�е�ͼ��ͨ������ɲ�ͳһ
	merge(imgv, result2);  //�ϲ�ͼ��
						   //imshow("result2", result2);  /imshow�����ʾ4��ͨ������˽����Image Watch�в鿴
	waitKey(0);
	return 0;
}
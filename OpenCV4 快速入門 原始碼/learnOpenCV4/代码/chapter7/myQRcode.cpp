#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("qrcode2.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}	Mat gray, qrcode_bin;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	QRCodeDetector qrcodedetector;
	vector<Point> points;
	string information;
	bool isQRcode;
	isQRcode = qrcodedetector.detect(gray, points);  //ʶ���ά��
	if (isQRcode)
	{
		//�����ά��
		information = qrcodedetector.decode(gray, points, qrcode_bin);
		cout << points << endl;  //�����ά���ĸ����������
	}
	else
	{
		cout << "�޷�ʶ���ά�룬��ȷ��ͼ��ʱ���ж�ά��" << endl;
		return -1;
	}
	//���ƶ�ά��ı߿�
	for (int i = 0; i < points.size(); i++)
	{
		if (i == points.size() - 1)
		{
			line(img, points[i], points[0], Scalar(0, 0, 255), 2, 8);
			break;
		}
		line(img, points[i], points[i + 1], Scalar(0, 0, 255), 2, 8);
	}
	//���������������ͼƬ��
	putText(img, information.c_str(), Point(20, 30), 0, 1.0, Scalar(0, 0, 255), 2, 8);

	//���ú���ֱ�Ӷ�λ��ά�벢����
	string information2;
	vector<Point> points2;
	information2 = qrcodedetector.detectAndDecode(gray, points2);
	cout << points2 << endl;
	putText(img, information2.c_str(), Point(20, 55), 0, 1.0, Scalar(0, 0, 0), 2, 8);

	//������
	imshow("result", img);
	namedWindow("qrcode_bin", WINDOW_NORMAL);
	imshow("qrcode_bin", qrcode_bin);
	waitKey(0);
	return 0;
}
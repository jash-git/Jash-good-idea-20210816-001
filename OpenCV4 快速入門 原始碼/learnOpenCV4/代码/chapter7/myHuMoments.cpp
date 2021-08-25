#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	Mat img = imread("approx.png");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	// ��ֵ��
	Mat gray, binary;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 105, 255, THRESH_BINARY);

	//����������ϸС����
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, k);

	// ��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, 0, 2, Point());
	for (int n = 0; n < contours.size(); n++)
	{
		Moments M;
		M = moments(contours[n], true);
		Mat hu;
		HuMoments(M, hu);  //����Hu��
		cout << hu << endl;
	}
	return 0;
}
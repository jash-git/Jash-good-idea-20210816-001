#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	//��ͼ����о���任
	Mat img = imread("rice.png");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("ԭͼ", img);
	Mat rice, riceBW;

	//��ͼ��ת�ɶ�ֵͼ������ͳ����ͨ��
	cvtColor(img, rice, COLOR_BGR2GRAY);
	threshold(rice, riceBW, 50, 255, THRESH_BINARY);

	//���������ɫ���������ֲ�ͬ��ͨ��
	RNG rng(10086);
	Mat out, stats, centroids;
	//ͳ��ͼ������ͨ��ĸ���
	int number = connectedComponentsWithStats(riceBW, out, stats, centroids, 8, CV_16U);
	vector<Vec3b> colors;
	for (int i = 0; i < number; i++)
	{
		//ʹ�þ��ȷֲ��������ȷ����ɫ
		Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3);
	}

	//�Բ�ͬ��ɫ��ǳ���ͬ����ͨ��
	Mat result = Mat::zeros(rice.size(), img.type());
	int w = result.cols;
	int h = result.rows;
	for (int i = 1; i < number; i++)
	{
		// ����λ��
		int center_x = centroids.at<double>(i, 0);
		int center_y = centroids.at<double>(i, 1);
		//���α߿�
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int w = stats.at<int>(i, CC_STAT_WIDTH);
		int h = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		// ����λ�û���
		circle(img, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
		// ��Ӿ���
		Rect rect(x, y, w, h);
		rectangle(img, rect, colors[i], 1, 8, 0);
		putText(img, format("%d", i), Point(center_x, center_y),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		cout << "number: " << i << ",area: " << area << endl;
	}
	//��ʾ���
	imshow("��Ǻ��ͼ��", img);

	waitKey(0);
	return 0;
}

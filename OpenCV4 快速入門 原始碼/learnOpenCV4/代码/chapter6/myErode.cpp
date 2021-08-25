#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
//���ư���������
void drawState(Mat &img, int number, Mat centroids, Mat stats, String str) {
	RNG rng(10086);
	vector<Vec3b> colors;
	for (int i = 0; i < number; i++)
	{
		//ʹ�þ��ȷֲ��������ȷ����ɫ
		Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3);
	}

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

		// ����λ�û���
		circle(img, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
		// ��Ӿ���
		Rect rect(x, y, w, h);
		rectangle(img, rect, colors[i], 1, 8, 0);
		putText(img, format("%d", i), Point(center_x, center_y),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
	}
	imshow(str, img);
}

int main()
{
	//�������ڸ�ʴ��ԭͼ��
	Mat src = (Mat_<uchar>(6, 6) << 0, 0, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255,
		0, 255, 255, 255, 255, 0,
		0, 255, 255, 255, 255, 0,
		0, 255, 255, 255, 255, 0,
		0, 0, 0, 0, 0, 0);
	Mat struct1, struct2;
	struct1 = getStructuringElement(0, Size(3, 3));  //���νṹԪ��
	struct2 = getStructuringElement(1, Size(3, 3));  //ʮ�ֽṹԪ��

	Mat erodeSrc;  //��Ÿ�ʴ���ͼ��
	erode(src, erodeSrc, struct2);
	namedWindow("src", WINDOW_GUI_NORMAL);
	namedWindow("erodeSrc", WINDOW_GUI_NORMAL);
	imshow("src", src);
	imshow("erodeSrc", erodeSrc);

	Mat LearnCV_black = imread("LearnCV_black.png", IMREAD_ANYCOLOR);
	Mat LearnCV_write = imread("LearnCV_write.png", IMREAD_ANYCOLOR);
	Mat erode_black1, erode_black2, erode_write1, erode_write2;
	//�ڱ���ͼ��ʴ
	erode(LearnCV_black, erode_black1, struct1);
	erode(LearnCV_black, erode_black2, struct2);
	imshow("LearnCV_black", LearnCV_black);
	imshow("erode_black1", erode_black1);
	imshow("erode_black2", erode_black2);

	//�ױ�����ʴ
	erode(LearnCV_write, erode_write1, struct1);
	erode(LearnCV_write, erode_write2, struct2);
	imshow("LearnCV_write", LearnCV_write);
	imshow("erode_write1", erode_write1);
	imshow("erode_write2", erode_write2);

	//��֤��ʴ��С��ͨ���ȥ��
	Mat img = imread("rice.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat img2;
	copyTo(img, img2, img);  //��¡һ��������ͼ�����ں���ͼ�����
	Mat rice, riceBW;

	//��ͼ��ת�ɶ�ֵͼ������ͳ����ͨ��
	cvtColor(img, rice, COLOR_BGR2GRAY);
	threshold(rice, riceBW, 50, 255, THRESH_BINARY);

	Mat out, stats, centroids;
	//ͳ��ͼ������ͨ��ĸ���
	int number = connectedComponentsWithStats(riceBW, out, stats, centroids, 8, CV_16U);
	drawState(img, number, centroids, stats, "δ��ʴʱͳ����ͨ��");  //����ͼ��

	erode(riceBW, riceBW, struct1);  //��ͼ����и�ʴ
	number = connectedComponentsWithStats(riceBW, out, stats, centroids, 8, CV_16U);
	drawState(img2, number, centroids, stats, "��ʴ��ͳ����ͨ��");  //����ͼ��

	waitKey(0);
	return 0;
}

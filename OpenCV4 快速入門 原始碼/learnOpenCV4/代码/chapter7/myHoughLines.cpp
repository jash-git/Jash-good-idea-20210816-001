#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void drawLine(Mat &img, //Ҫ���ֱ�ߵ�ͼ��
	vector<Vec2f> lines,   //����ֱ������
	double rows,   //ԭͼ����������ߣ�
	double cols,  //ԭͼ�����������
	Scalar scalar,  //����ֱ�ߵ���ɫ
	int n  //����ֱ�ߵ��߿�
)
{
	Point pt1, pt2;
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];  //ֱ�߾�������ԭ��ľ���
		float theta = lines[i][1];  //ֱ�߹�����ԭ�㴹����x��н�
		double a = cos(theta);  //�нǵ�����ֵ
		double b = sin(theta);  //�нǵ�����ֵ
		double x0 = a*rho, y0 = b*rho;  //ֱ���������ԭ��Ĵ��ߵĽ���
		double length = max(rows, cols);  //ͼ��߿�����ֵ
										  //����ֱ���ϵ�һ��
		pt1.x = cvRound(x0 + length  * (-b));
		pt1.y = cvRound(y0 + length  * (a));
		//����ֱ������һ��
		pt2.x = cvRound(x0 - length  * (-b));
		pt2.y = cvRound(y0 - length  * (a));
		//�������һ��ֱ��
		line(img, pt1, pt2, scalar, n);
	}
}

int main()
{
	Mat img = imread("HoughLines.jpg", IMREAD_GRAYSCALE);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat edge;

	//����Եͼ�񣬲���ֵ��
	Canny(img, edge, 80, 180, 3, false);
	threshold(edge, edge, 170, 255, THRESH_BINARY);

	//�ò�ͬ���ۼ������м��ֱ��
	vector<Vec2f> lines1, lines2;
	HoughLines(edge, lines1, 1, CV_PI / 180, 50, 0, 0);
	HoughLines(edge, lines2, 1, CV_PI / 180, 150, 0, 0);

	//��ԭͼ���л���ֱ��
	Mat img1, img2;
	img.copyTo(img1);
	img.copyTo(img2);
	drawLine(img1, lines1, edge.rows, edge.cols, Scalar(255), 2);
	drawLine(img2, lines2, edge.rows, edge.cols, Scalar(255), 2);

	//��ʾͼ��
	imshow("edge", edge);
	imshow("img", img);
	imshow("img1", img1);
	imshow("img2", img2);
	waitKey(0);
	return 0;
}
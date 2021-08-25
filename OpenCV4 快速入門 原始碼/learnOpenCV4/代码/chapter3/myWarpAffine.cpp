#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat rotation0, rotation1, img_warp0, img_warp1;
	double angle = 30;  //����ͼ����ת�ĽǶ�
	Size dst_size(img.rows, img.cols);  //�������ͼ��ĳߴ�
	Point2f center(img.rows / 2.0, img.cols / 2.0);  //����ͼ�����ת����
	rotation0 = getRotationMatrix2D(center, angle, 1);  //�������任����
	warpAffine(img, img_warp0, rotation0, dst_size);  //���з���任
	imshow("img_warp0", img_warp0);
	//���ݶ������������з���任
	Point2f src_points[3];
	Point2f dst_points[3];
	src_points[0] = Point2f(0, 0);  //ԭʼͼ���е�������
	src_points[1] = Point2f(0, (float)(img.cols - 1));
	src_points[2] = Point2f((float)(img.rows - 1), (float)(img.cols - 1));
	dst_points[0] = Point2f((float)(img.rows)*0.11, (float)(img.cols)*0.20);  //����任��ͼ���е�������
	dst_points[1] = Point2f((float)(img.rows)*0.15, (float)(img.cols)*0.70);
	dst_points[2] = Point2f((float)(img.rows)*0.81, (float)(img.cols)*0.85);
	rotation1 = getAffineTransform(src_points, dst_points);  //���ݶ�Ӧ����ȡ����任����
	warpAffine(img, img_warp1, rotation1, dst_size);  //���з���任
	imshow("img_warp1", img_warp1);
	waitKey(0);
	return 0;
}
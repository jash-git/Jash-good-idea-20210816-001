#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("noobcvqr.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Point2f src_points[4];
	Point2f dst_points[4];
	//ͨ��Image Watch�鿴�Ķ�ά���ĸ��ǵ�����
	src_points[0] = Point2f(94.0, 374.0);
	src_points[1] = Point2f(507.0, 380.0);
	src_points[2] = Point2f(1.0, 623.0);
	src_points[3] = Point2f(627.0, 627.0);
	//����͸�ӱ任���ά���ĸ��ǵ������
	dst_points[0] = Point2f(0.0, 0.0);
	dst_points[1] = Point2f(627.0, 0.0);
	dst_points[2] = Point2f(0.0, 627.0);
	dst_points[3] = Point2f(627.0, 627.0);
	Mat rotation, img_warp;
	rotation = getPerspectiveTransform(src_points, dst_points);  //����͸�ӱ任����
	warpPerspective(img, img_warp, rotation, img.size());  //͸�ӱ任ͶӰ
	imshow("img", img);
	imshow("img_warp", img_warp);
	waitKey(0);
	return 0;
}
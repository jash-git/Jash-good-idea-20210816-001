#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
Mat I;//ԭͼ
Mat pI;//ͶӰ�任���ͼ
Point2f IPoint,pIPoint;
int i = 0,j = 0;
Point2f src[4];//�洢ԭ����
Point2f dst[4];//�洢��Ӧ�任������
//ͨ����������¼�����ԭͼ��ȡ�ĸ�����
void mouse_I(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		//��¼����
		IPoint = Point2f(x, y);
		break;
	case CV_EVENT_LBUTTONUP:
		src[i] = IPoint;
		circle(I, src[i], 7, Scalar(0),3);//���
		i += 1;
		break;
	default:
		break;
	}
}
//ͨ����������¼���Ҫ�����ͼ��ȡ�ĸ�����
void mouse_pI(int event, int x, int y, int flags, void *param)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		//��¼����
		pIPoint = Point2f(x, y);
		break;
	case CV_EVENT_LBUTTONUP:
		dst[j] = pIPoint;
		circle(pI, dst[j], 7, Scalar(0), 3);//���
		j += 1;
		break;
	default:
		break;
	}
}
int main(int argc, char*argv[])
{
	//����ԭͼ
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return 0;
	//���ͼ��
	pI = 200 * Mat::ones(I.size(), CV_8UC1);
	//��ԭͼ�����ϣ���������¼�
	namedWindow("I", 1);
	setMouseCallback("I", mouse_I, NULL);
	//����������ϣ���������¼�
	namedWindow("pI", 1);
	setMouseCallback("pI", mouse_pI, NULL);
	imshow("I", I);
	imshow("pI", pI);
	while(!(i == 4 && j == 4))
	{
		imshow("I", I);
		imshow("pI", pI);
		if (waitKey(50) == 'q')
			break;
	}
	imshow("I", I);
	imshow("pI", pI);
	imwrite("I.jpg", I);
	imwrite("pI.jpg", pI);
	//�Ƴ�����¼� 
	setMouseCallback("I", NULL, NULL);
	setMouseCallback("pI", NULL, NULL);
	//����ͶӰ�任����
	Mat p = getPerspectiveTransform(src, dst);
	//ͶӰ�任
	Mat result;
	warpPerspective(I, result, p, pI.size());
	imshow("ͶӰ���Ч��", result);
	imwrite("result.jpg", result);
	waitKey(0);
	return 0;
}

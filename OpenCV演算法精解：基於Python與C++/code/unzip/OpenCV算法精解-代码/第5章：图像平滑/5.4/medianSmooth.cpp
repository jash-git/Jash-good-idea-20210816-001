#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
//��ֵƽ��
Mat medianSmooth(const Mat & I, Size size, int borderType = BORDER_DEFAULT)
{
	CV_Assert(I.type() == CV_8UC1);
	int H = size.height;
	int W = size.width;
	//���ڵĳ����Ϊ������һ��������������ȵ�
	CV_Assert(H > 0 && W > 0);
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	//��ԭͼ�������б�Ե����
	int h = (H - 1) / 2;
	int w = (W - 1) / 2;
	Mat Ip;
	copyMakeBorder(I, Ip, h, h, w, w, borderType);
	//����ͼ��Ŀ��
	int rows = I.rows;
	int cols = I.cols;
	//��ֵƽ��������ͼ��
	Mat medianI(I.size(), CV_8UC1);
	int i = 0, j = 0;
	//������λ��
	int index = (H*W - 1) / 2;
	for (int r = h; r < h + rows; r++)
	{
		for (int c = w; c < w + cols; c++)
		{
			//ȡ�Ե�ǰλ��Ϊ����,��СΪ size ������
			Mat region = Ip(Rect(c-w, r-h, W,H)).clone();
			//�Ը�����ת�����о���
			region = region.reshape(1, 1);
			//����
			cv::sort(region, region, CV_SORT_EVERY_ROW);
			//ȡ����
			uchar mValue = region.at<uchar>(0, index);
			medianI.at<uchar>(i, j) = mValue;
			j++;
		}
		i++;
		j = 0;
	}
	return medianI;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	//��ֵƽ��
	Mat medianImage = medianSmooth(image, Size(7, 7));
	imshow("ԭͼ", image);
	imshow("��ֵƽ��", medianImage);
	waitKey(0);
	return 0;
}
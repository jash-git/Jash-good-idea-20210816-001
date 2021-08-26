#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//���پ�ֵƽ��������ͼ�����������Ϊ������
Mat fastMeanBlur(Mat img, Size winSize, int borderType, Scalar value=Scalar())
{
	//�жϴ��ڵĿ��������
	int hei = winSize.height;
	int wid = winSize.width;
	CV_Assert(hei % 2 == 1 && wid % 2 == 1);
	//���ڰ뾶
	int hh = (hei-1) / 2;
	int ww = (wid - 1) / 2;
	//���ڵ���������� ���� ��
	float area = float(hei*wid);
	//�߽�����
	Mat paddImg;
	cv::copyMakeBorder(img, paddImg,hh, hh, ww, ww, borderType, value);
	//ͼ�����
	Mat inte;
	cv::integral(paddImg, inte, CV_32FC1);
	//����ͼ�����Ŀ��
	int rows = img.rows;
	int cols = img.cols;
	int r = 0, c = 0;
	Mat meanImg = Mat::zeros(img.size(),CV_32FC1);
	for (int h = hh; h < hh+rows; h++)
	{
		for (int w = ww; w < ww+cols; w++)
		{
			float bottomRight = inte.at<float>(h + hh + 1, w + ww + 1);
			float topLeft = inte.at<float>(h - hh , w - ww);
			float topRight = inte.at<float>(h+hh+1,w-ww);
			float bottomLeft = inte.at<float>(h-hh,w+ww+1);
			meanImg.at<float>(r, c) = (bottomRight + topLeft - topRight - bottomLeft) / area;
			c++;
		}
		r++;
		c = 0;
	}
	return meanImg;
}
int main(int argc, char*argv[])
{
	//����ͼ�����
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
		return -1;
	//ͼ��������ֵ���Ӿ��
	Mat meanImg = fastMeanBlur(img, Size(5, 5), cv::BORDER_REFLECT101);
	//��������ת��
	meanImg.convertTo(meanImg, CV_8UC1, 1.0, 0);
	//��ʾԭͼ
	imshow("ԭͼ", img);
	imshow("��ֵƽ��", meanImg);
	waitKey(0);
	return 0;
}
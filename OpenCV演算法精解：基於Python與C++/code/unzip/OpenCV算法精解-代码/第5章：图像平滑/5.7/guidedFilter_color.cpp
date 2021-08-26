#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//�����˲� ����ֵ����Ϊ 64FC1 
Mat guidedFilter(Mat I, Mat p, int r, float eps, float s)
{
	//����ͼ��Ŀ��
	int rows = I.rows;
	int cols = I.cols;
	//��Сͼ��
	Mat small_I, small_p;
	Size smallSize(int(round(s*cols)), int(round(s*rows)));
	resize(I, small_I, smallSize,0,0,CV_INTER_CUBIC);
	resize(p, small_p, smallSize, 0, 0, CV_INTER_CUBIC);
	//���ž�ֵƽ���Ĵ��ڰ뾶
	int small_r = int(round(r*s));//ȷ��������
	Size winSize(2 * small_r + 1, 2 * small_r + 1);
	//��ֵƽ��
	Mat mean_small_I, mean_small_p;
	boxFilter(small_I, mean_small_I, CV_64FC1, winSize);
	boxFilter(small_p, mean_small_p, CV_64FC1, winSize);
	// small_I .* small_p �ľ�ֵƽ��
	Mat small_Ip = small_I.mul(small_p);
	Mat mean_small_Ip;
	boxFilter(small_Ip, mean_small_Ip, CV_64FC1,winSize);
	//Э����
	Mat cov_small_Ip = mean_small_Ip - mean_small_I.mul(mean_small_p);
	//��ֵƽ��
	Mat mean_small_II;
	boxFilter(small_I.mul(small_I), mean_small_II, CV_64FC1,winSize);
	//����
	Mat var_small_I = mean_small_II - mean_small_I.mul(mean_small_I);
	Mat small_a = cov_small_Ip/(var_small_I + eps);
	Mat small_b = mean_small_p - small_a.mul(mean_small_I);
	//�� small_a �� small_b ���о�ֵƽ��
	Mat mean_small_a, mean_small_b;
	boxFilter(small_a, mean_small_a, CV_64FC1, winSize);
	boxFilter(small_b, mean_small_b, CV_64FC1, winSize);
	//�Ŵ�
	Mat mean_a, mean_b;
	resize(mean_small_a, mean_a, I.size(), 0, 0, CV_INTER_LINEAR);
	resize(mean_small_b, mean_b, I.size(), 0, 0, CV_INTER_LINEAR);
	Mat q = mean_a.mul(I) + mean_b;
	return q;
}
//��ɫ�����˲�
Mat guidedFilterColor(Mat I, int r, float eps, float s)
{
	//����ͨ��
	vector<Mat> Is;
	split(I, Is);
	//ÿһ��ͨ�����е����˲�
	vector<Mat> qs;
	qs.clear();
	for (int i = 0; i < 3; i++)
	{
		Mat q = guidedFilter(Is[i], Is[i], r, eps, s);
		qs.push_back(q);
	}
	//����ͨ������
	Mat q_color;
	merge(qs, q_color);
	return q_color;
}
//ϸ����ǿ
Mat guidedEnchance(Mat I, int r, float eps, float s)
{
	//�����˲���ƽ����
	Mat q = guidedFilterColor(I, r, eps, s);
	Mat I_enhanced = (I - q) * 5 + q;
	//��һ��
	normalize(I_enhanced, I_enhanced, 1.0, 0,NORM_MINMAX);
	return I_enhanced;
}
int main(int argc, char*argv[])
{
	//�����ɫͼ��
	Mat image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
	if (!image.data || image.channels()!=3)
		return -1;
	//ͼ���һ��
	image.convertTo(image, CV_64FC1, 1.0 / 255);
	imshow("ԭͼ", image);
	//��ɫ�����˲�(ƽ��)
	Mat result = guidedFilterColor(image,7,0.04,0.3);
	imshow("�����˲�", result);
	//ϸ����ǿ
	Mat I_enhanced = guidedEnchance(image, 16, 0.01,0.4);
	imshow("ϸ����ǿ", I_enhanced);
	waitKey(0);
	return 0;
}
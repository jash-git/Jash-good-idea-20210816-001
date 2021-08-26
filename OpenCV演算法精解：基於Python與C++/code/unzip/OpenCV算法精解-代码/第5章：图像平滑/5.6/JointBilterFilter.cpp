#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//�����ռ����Ȩ��ģ��
Mat getClosenessWeight(double sigma_g, Size size)
{
	//Ȩ��ģ��Ŀ��
	int W = size.width;
	int H = size.height;
	//ģ�������
	int cW = (W - 1) / 2;
	int cH = (H - 1) / 2;
	//Ȩ��ģ��
	Mat closenessWeight = Mat::zeros(size, CV_64FC1);
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			double norm2 = pow(double(r - cH), 2.0) + pow(double(c - cW), 2.0);
			double sigma_g2 = 2.0*pow(sigma_g, 2.0);
			//��ֵ
			closenessWeight.at<double>(r, c) = exp(-norm2/ sigma_g2);
		}
	}
	return closenessWeight;
}
//����˫���˲�
Mat jointBLF(Mat I, Size size, float sigma_g, float sigma_d, int borterType = BORDER_DEFAULT)
{
	//�����ռ�����Ȩ��ģ��
	Mat closeWeight = getClosenessWeight(sigma_g, size);
	//�� I ���и�˹ƽ��
	Mat Ig;
	GaussianBlur(I, Ig, size, sigma_g);
	//ģ�������
	int cH = (size.height - 1) / 2;
	int cW = (size.width - 1) / 2;
	//��ԭͼ�͸�˹ƽ���Ľ������߽�
	Mat Ip,Igp;
	copyMakeBorder(I, Ip, cH, cH, cW, cW, borterType);
	copyMakeBorder(Ig, Igp, cH, cH, cW, cW, borterType);
	//ԭͼ�����Ŀ���
	int rows = I.rows;
	int cols = I.cols;
	int i = 0, j= 0;
	//����˫���˲�
	Mat jblf = Mat::zeros(I.size(), CV_64FC1);
	for (int r = cH; r < cH + rows; r++)
	{
		for (int c = cW; c < cW + cols; c++)
		{
			//��ǰλ�õ�ֵ
			double pixel = Igp.at<double>(r, c);
			//��ȡ��ǰλ�õ�����
			Mat region = Igp(Rect(c-cW,r-cH,size.width,size.height));
			//��ǰλ�õ�������Ȩ��ģ��
			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			cv::exp(-0.5*similarityWeight / pow(sigma_d, 2.0), similarityWeight);
			//������Ȩ��ģ��Ϳռ����Ȩ��ģ����
			Mat weight = closeWeight.mul(similarityWeight);
			//Ȩ��ģ��Ĺ�һ��
			weight = weight / cv::sum(weight)[0];
			//Ȩ��ģ��������Ӧλ��������
			Mat Iregion= Ip(Rect(c - cW, r - cH, size.width, size.height));
			jblf.at<double>(i, j) = sum(Iregion.mul(weight))[0];
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return jblf;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//��������Ϊ CV_64F
	Mat fI;
	I.convertTo(fI, CV_64F, 1.0, 0);
	//����˫���˲�
	Mat jblf = jointBLF(fI, Size(33, 33), 7, 2);
	//��ʾ����˫���˲�
	Mat jblf8U;
	jblf.convertTo(jblf8U, CV_8U, 1, 0);
	imshow("����˫���˲�", jblf);
	imshow("ԭͼ", I);
	waitKey(0);
	return 0;
}
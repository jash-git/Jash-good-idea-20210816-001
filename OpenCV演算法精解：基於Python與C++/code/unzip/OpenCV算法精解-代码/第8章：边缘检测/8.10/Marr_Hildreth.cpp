#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//���� LoG ����
Mat createLoGKernel(float sigma, Size ksize);
/*��ɢ�Ķ�ά�������*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//�����˳ʱ����ת180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//���ÿһ������,�����ӦԪ�����Ȼ�����
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
//�㽻��㣺����1
void zero_cross_defalut(InputArray _src, OutputArray _dst);
//�㽻��㣺����2
void zero_cross_mean(InputArray _src, OutputArray _dst);
//�㽻���ļ��㷽��
enum ZERO_CROSS_TYPE { ZERO_CROSS_DEFALUT = 0, ZERO_CROSS_MEAN = 1 };
// Marr_Hildreth ��Ե����㷨
Mat Marr_Hildreth(InputArray image, Size loGSize, float sigma, ZERO_CROSS_TYPE type);

//�����ͼ��
Mat image;
//����ı�Եͼ��
Mat marrHiImage;
//���ڵİ뾶
int halfWin = 2;
const int MAX_HALFWIN = 30;
int sigma = 1;
const int MAX_SIGMA = 100;
void callBack_win_sig(int, void*)
{
	//LoG ���Ӵ��ڵĴ�СΪ (2*halfWin+1,2*halfWin+1)����׼��Ϊ  sigma/10.0
	marrHiImage = Marr_Hildreth(image, Size(2 * halfWin + 1, 2 * halfWin + 1), sigma / 10.0, ZERO_CROSS_DEFALUT);
	imshow("Marr_Hildreth ��Ե���", marrHiImage);
}
//������
int main(int argc, char*argv[])
{
	//����ͼ�����
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return -1;
	}
	imshow("ԭͼ", image);
	namedWindow("Marr_Hildreth ��Ե���", WINDOW_AUTOSIZE);
	createTrackbar("���ڰ뾶��", "Marr_Hildreth ��Ե���", &halfWin, MAX_HALFWIN, callBack_win_sig);
	createTrackbar("��׼�", "Marr_Hildreth ��Ե���", &sigma, MAX_SIGMA, callBack_win_sig);
	callBack_win_sig(0, 0);
	waitKey(0);
	return 0;
}
//���� LoG ����ˣ�ksize �Ŀ�͸߾�Ϊ����
Mat createLoGKernel(float sigma, Size ksize)
{
	// LoG ���ӵĿ�ߣ������߾�Ϊ����
	int winH = ksize.height;
	int winW = ksize.width;
	CV_Assert(winH >= 1 && winW >= 1);
	CV_Assert(winH % 2 == 1 && winW % 2 == 1);
	//����
	float sigmaSquare = pow(sigma, 2);
	//LoG ��
	Mat logKernel(ksize, CV_32FC1);
	//���ĵ������
	int cr = (winH - 1) / 2;
	int cc = (winW - 1) / 2;
	for (int r = 0; r< winH; r++)
	{
		for (int c = 0; c < winW; c++)
		{
			float norm2 = pow(float(r - cr), 2) + pow(float(c - cc), 2);
			logKernel.at<float>(r, c) = 1.0 / sigmaSquare*(norm2 / sigmaSquare - 2)*exp(-norm2 / (2 * sigmaSquare));
		}
	}
	return logKernel;
}

//�㽻���:����1
void zero_cross_defalut(InputArray _src, OutputArray _dst)
{
	Mat src = _src.getMat();
	//�ж�λ��
	CV_Assert(src.type() == CV_32FC1);
	_dst.create(src.size(), CV_8UC1);
	Mat dst = _dst.getMat();
	//����ͼ�����Ŀ��
	int rows = src.rows;
	int cols = src.cols;
	//�㽻���
	for (int r = 1; r < rows - 2; r++)
	{
		for (int c = 1; c < cols - 2; c++)
		{
			//�� / �·���
			if (src.at<float>(r - 1, c)*src.at<float>(r + 1, c) < 0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
			//�� / �ҷ���
			if (src.at<float>(r, c - 1) * src.at<float>(r, c + 1) < 0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
			//���� / ���·���
			if (src.at<float>(r - 1, c - 1)*src.at<float>(r + 1, c + 1) < 0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
			//���� / ���� ����
			if (src.at<float>(r - 1, c + 1)*src.at<float>(r + 1, c - 1)<0)
			{
				dst.at<uchar>(r, c) = 255;
				continue;
			}
		}
	}
}

//�㽻�棺����2
void zero_cross_mean(InputArray _src, OutputArray _dst)
{
	Mat src = _src.getMat();
	//�ж�λ��
	_dst.create(src.size(), CV_8UC1);
	Mat dst = _dst.getMat();
	int rows = src.rows;
	int cols = src.cols;
	double minValue;
	double maxValue;
	//�洢�ĸ�����ľ�ֵ
	Mat temp(1, 4, CV_32FC1);
	//�㽻���
	for (int r = 0 + 1; r < rows - 1; r++)
	{
		for (int c = 0 + 1; c < cols - 1; c++)
		{
			//���Ϸ�
			Mat left_top(src, Rect(c - 1, r - 1, 2, 2));
			temp.at<float>(0, 0) = mean(left_top)[0];
			//���Ϸ�
			Mat right_top(src, Rect(c, r - 1, 2, 2));
			temp.at<float>(0, 1) = mean(right_top)[0];
			//���·�
			Mat left_bottom(src, Rect(c - 1, r, 2, 2));
			temp.at<float>(0, 2) = mean(left_top)[0];
			//���·�
			Mat right_bottom(src, Rect(c, r, 2, 2));
			temp.at<float>(0, 3) = mean(right_bottom)[0];
			minMaxLoc(temp, &minValue, &maxValue);
			//���ֵ����Сֵ��ţ�Ϊ�����
			if (minValue*maxValue < 0)
				dst.at<uchar>(r, c) = 255;
		}
	}
}
// Marr_Hildreth ��Ե����㷨
Mat Marr_Hildreth(InputArray image, Size loGSize, float sigma, ZERO_CROSS_TYPE type)
{
	//��һ�������� LoG ����
	Mat loGKernel = createLoGKernel(sigma, loGSize);
	//�ڶ�����ͼ�� �� LoG ���ӵľ��
	Mat img_Cov_loGKernel;
	conv2D(image, loGKernel, img_Cov_loGKernel, CV_32FC1, Point(-1, -1), BORDER_CONSTANT);
	//�������������
	Mat zeroCrossImage;
	switch (type)
	{
	case ZERO_CROSS_DEFALUT:
		zero_cross_defalut(img_Cov_loGKernel, zeroCrossImage);
		break;
	case ZERO_CROSS_MEAN:
		zero_cross_mean(img_Cov_loGKernel, zeroCrossImage);
		break;
	default:
		CV_Error(CV_StsBadArg, "Unknown ZERO_CROSS type");
	}
	return zeroCrossImage;
}

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//�����˲�
Mat guidedFilter(Mat I, Mat p, int r, float eps)
{
	//����ͼ��Ŀ��
	int rows = I.rows;
	int cols = I.cols;
	//��ֵƽ��
	Mat mean_I, mean_p;
	boxFilter(I, mean_I,CV_64FC1 ,Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	boxFilter(p, mean_p, CV_64FC1,Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	// I.*p �ľ�ֵƽ��
	Mat Ip = I.mul(p);
	Mat mean_Ip;
	boxFilter(Ip, mean_Ip, CV_64FC1,Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	//Э����
	Mat cov_Ip = mean_Ip - mean_I.mul(mean_p);
	// I.*I �ľ�ֵƽ��
	Mat mean_II;
	boxFilter(I.mul(I), mean_II, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	// ����
	Mat var_I = mean_II - mean_I.mul(mean_I);
	Mat a = cov_Ip / (var_I + eps);
	Mat b = mean_p - a.mul(mean_I);
	// �� a �� b ���о�ֵƽ��
	Mat mean_a, mean_b;
	boxFilter(a, mean_a, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	boxFilter(b, mean_b, CV_64FC1, Size(2 * r + 1, 2 * r + 1), Point(-1, -1));
	Mat q = mean_a.mul(I) + mean_b;
	return q;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat p = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data ||!p.data)
		return - 1;
	//��ʾԭͼ
	imshow("I", I);
	imwrite("I.jpg", I);
	//ͼ���һ��
	Mat fI,fp;
	I.convertTo(fI, CV_64FC1, 1.0 / 255);
	p.convertTo(fp, CV_64FC1, 1.0 / 255);
	//�����˲�
	//ͼ��ƽ��
	Mat q = guidedFilter(fI, fp, 17, 0.1);
	imshow("q", q);
	Mat resultq;
	q.convertTo(resultq, CV_8UC1, 255, 0);
	imwrite("q71.jpg", resultq);
	//ϸ����ǿ
	Mat I_enhanced = (fI - q)* 5 + q;
	normalize(I_enhanced, I_enhanced, 1, 0, NORM_MINMAX, CV_32FC1);
	imshow("I_enhanced", I_enhanced);
	Mat resultEnhanced;
	I_enhanced.convertTo(resultEnhanced, CV_8UC1, 255, 0);
	imwrite("en.jpg", resultEnhanced);
	waitKey(0);
	return 0;
}
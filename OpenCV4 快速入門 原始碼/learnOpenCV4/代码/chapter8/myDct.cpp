#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat kernel = (Mat_<float>(5, 5) << 1, 2, 3, 4, 5,
		                               2, 3, 4, 5, 6,
		                               3, 4, 5, 6, 7,
		                               4, 5, 6, 7, 8,
		                               5, 6, 7, 8, 9);
	Mat a, b;
	dct(kernel, a);
	idct(a, b);

	//��ͼ����д���
	Mat img = imread("lena.png");
	if (!img.data)
	{
		cout << "����ͼ�����,��ȷ��ͼ�������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("ԭͼ��", img);
	
	//������ѱ任�ߴ�
	int width = 2 * getOptimalDFTSize((img.cols + 1) / 2);
	int height = 2 * getOptimalDFTSize((img.rows + 1) / 2);
	
	//��չͼ��ߴ�
	int T = 0;
	int B = height - T - img.rows;
	int L = 0;
	int R = width - L - img.rows;
	Mat appropriate;
	copyMakeBorder(img, appropriate, T, B, L, R, BORDER_CONSTANT, Scalar(0));

	//������ͨ����Ҫ�ֱ����DCT�任
	vector<Mat> channels;
	split(appropriate, channels);

	//��ȡNGR��ɫ����ͨ����ֵ
	Mat one = channels.at(0);	
	Mat two = channels.at(1);
	Mat three = channels.at(2);

	//����DCT�任
	Mat oneDCT, twoDCT, threeDCT;
	dct(Mat_<float>(one), oneDCT);
	dct(Mat_<float>(two), twoDCT);
	dct(Mat_<float>(three), threeDCT);

	//�����������ͨ��
	vector<Mat> channelsDCT;
	channelsDCT.push_back(Mat_<uchar>(oneDCT));
	channelsDCT.push_back(Mat_<uchar>(twoDCT));
	channelsDCT.push_back(Mat_<uchar>(threeDCT));

	//���ͼ��
	Mat result;
	merge(channelsDCT, result);
	imshow("DCTͼ��", result);
	waitKey();
	return 0;
}
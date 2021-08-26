#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
/*ȫ�ֱ���*/
Mat image;
Mat fImageFFT;//�洢ͼ��Ŀ��ٸ���Ҷ�任
Point maxLoc;//����Ҷ�׵����ֵ������
int radius = 10;//��ֹƵ��
const int Max_RADIUS = 100;

//�����ͨ�˲���
Mat ihpFilter;
Mat fImageFFT_ihpFilter;
Mat fImageFFT_ihpFilter_spectrum;
Mat result;
//�ڶ��������ٸ���Ҷ�任
void fft2Image(InputArray _src, OutputArray _dst);

//����Ҷ�׵ĻҶȼ�:������Ǹ���Ҷ�任,����Ǹ���Ҷ�׵ĻҶȼ�
void fourierSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
void callback_ihpFilter(int, void*);
int main(int argc, char*argv[])
{
	/*��һ��������ͼ�����*/
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return -1;
	}
	imshow("ԭͼƬ", image);
	Mat fImage;
	image.convertTo(fImage, CV_32FC1, 1.0, 0.0);

	/*�ڶ���:ͼ������ÿһ��������(-1)^(r+c)*/
	for (int r = 0; r < fImage.rows; r++)
	{
		for (int c = 0; c < fImage.cols; c++)
		{
			if ((r + c) % 2)
				fImage.at<float>(r, c) *= -1;
		}
	}

	/*�����������ٸ���Ҷ�任*/
	fft2Image(fImage, fImageFFT);
	//����Ҷ�任�ĸ���Ҷ��
	Mat fImageFFT_spectrum;
	//����Ҷ�׵ĻҶȼ���ʾ
	fourierSpectrum(fImageFFT, fImageFFT_spectrum);
	imshow("ͼ��ĸ���Ҷ��", fImageFFT_spectrum);
	//�õ�����Ҷ�����ֵ��λ��
	minMaxLoc(fImageFFT_spectrum, NULL, NULL, NULL, &maxLoc);
	/*�����ͨ�˲���*/
	namedWindow("�����ͨ����Ҷ��", 1);
	createTrackbar("�뾶:", "�����ͨ����Ҷ��", &radius, Max_RADIUS, callback_ihpFilter);
	waitKey(0);
	return 0;
}
void callback_ihpFilter(int, void*)
{
	/*���Ĳ������������ͨ�˲���*/
	ihpFilter.create(fImageFFT.size(), CV_32FC1);

	for (int r = 0; r < ihpFilter.rows; r++)
	{
		for (int c = 0; c < ihpFilter.cols; c++)
		{
			if (sqrt(pow(abs(float(r - maxLoc.y)), 2) + pow(abs(float(c - maxLoc.x)), 2)) > radius)
				ihpFilter.at<float>(r, c) = 1;
			else
				ihpFilter.at<float>(r, c) = 0;
		}
	}

	/*���岽�������ͨ�˲�����ͼ��Ŀ��ٸ���Ҷ�任���е��*/
	fImageFFT_ihpFilter.create(fImageFFT.size(), fImageFFT.type());
	for (int r = 0; r < fImageFFT_ihpFilter.rows; r++)
	{
		for (int c = 0; c < fImageFFT_ihpFilter.cols; c++)
		{
			//�ֱ�ȡ����ǰλ�õĿ��ٸ���Ҷ�任�������ͨ�˲�����ֵ
			Vec2f temp_fImageFFT = fImageFFT.at<Vec2f>(r, c);
			float temp_ihpFilter = ihpFilter.at<float>(r, c);

			//�����ͨ�˲�����ͼ��Ŀ��ٸ���Ҷ�任��Ӧλ�����
			fImageFFT_ihpFilter.at<Vec2f>(r, c) = temp_fImageFFT*temp_ihpFilter;
		}
	}

	//��ʾ��˹��ͨ����Ҷ��
	fourierSpectrum(fImageFFT_ihpFilter, fImageFFT_ihpFilter_spectrum);
	imshow("�����ͨ����Ҷ��", fImageFFT_ihpFilter_spectrum);

	/*���������������ͨ����Ҷ�任ִ�и���Ҷ��任����ֻȡʵ��*/
	dft(fImageFFT_ihpFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);

	/*���߲���ͬ����(-1)^(x+y)*/
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	/*�ڰ˲���ȡ���Ͻǣ���С��ԭͼƬ�Ĵ�С���*/
	result.convertTo(result, CV_8UC1, 1.0, 0);
	result = result(Rect(0, 0, image.cols, image.rows));
	imshow("���������ͨ�˲����ͼƬ", result);

}
//���ٸ���Ҷ�任
void fft2Image(InputArray _src, OutputArray _dst)
{
	//�õ�Mat����
	Mat src = _src.getMat();

	//�ж�λ��
	CV_Assert(src.type() == CV_32FC1 || src.type() == CV_64FC1);
	CV_Assert(src.channels() == 1 || src.channels() == 2);

	//Ϊ�˽��п��ٵĸ���Ҷ�任�����Ǿ��к��е�����,�ҵ����������ֵ
	Mat padded;
	int rPadded = getOptimalDFTSize(src.rows);
	int cPadded = getOptimalDFTSize(src.cols);

	//���б�Ե����,����ֵΪ��
	copyMakeBorder(src, padded, 0, rPadded - src.rows, 0, cPadded - src.cols, BORDER_CONSTANT, Scalar::all(0));

	//���ٵĸ���Ҷ�任��˫ͨ�������ڴ洢ʵ�� �� �鲿��
	dft(padded, _dst, DFT_COMPLEX_OUTPUT);
}
//�õ�����Ҷ��:������Ǹ���Ҷ�任,����Ǹ���Ҷ��
void fourierSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	//�жϸ���Ҷ�任������ͨ��
	CV_Assert(_srcFFT.channels() == 2);

	//�����ڴ�
	Mat dstSpectrum;
	dstSpectrum.create(_srcFFT.size(), _srcFFT.type());

	//����ͨ��
	vector<Mat> imageCenterFFT2Channel;
	split(_srcFFT, imageCenterFFT2Channel);

	//���㸵��Ҷ�任��
	magnitude(imageCenterFFT2Channel[0], imageCenterFFT2Channel[1], dstSpectrum);

	//��һ�ζԱȶȵ�����
	log(dstSpectrum + 1, dstSpectrum);

	//��һ��
	normalize(dstSpectrum, dstSpectrum, 0, 1, NORM_MINMAX);

	//Ϊ�˽��лҶȼ���ʾ��������ת��
	dstSpectrum.convertTo(_dstSpectrum, CV_8UC1, 255, 0);
}
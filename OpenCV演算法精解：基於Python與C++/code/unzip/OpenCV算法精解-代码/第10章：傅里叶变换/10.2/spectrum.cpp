#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//���ٸ���Ҷ�任
void fft2Image(InputArray _src, OutputArray _dst)
{
	//�õ�Mat����
	Mat src = _src.getMat();
	//�ж�λ��
	CV_Assert(src.type() == CV_32FC1 || src.type() == CV_64FC1);
	CV_Assert(src.channels() == 1 || src.channels() == 2);
	int rows = src.rows;
	int cols = src.cols;
	//Ϊ�˽��п��ٵĸ���Ҷ�任�����Ǿ��к��е�����,�ҵ����������ֵ
	Mat padded;
	int rPadded = getOptimalDFTSize(rows);
	int cPadded = getOptimalDFTSize(cols);
	//���б�Ե����,����ֵΪ��
	copyMakeBorder(src, padded, 0, rPadded - rows, 0, cPadded - cols, BORDER_CONSTANT, Scalar::all(0));
	//���ٵĸ���Ҷ�任��˫ͨ�������ڴ洢ʵ�� �� �鲿��
	dft(padded, _dst, DFT_COMPLEX_OUTPUT);
}
//����Ҷ�任�ķ����� amplitude spectrum
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	//�жϸ���Ҷ�任������ͨ��
	CV_Assert(_srcFFT.channels() == 2);
	//����ͨ��
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//���㸵��Ҷ�任�ķ����� sqrt(pow(R,2)+pow(I,2))
	magnitude(FFT2Channel[0], FFT2Channel[1], _dstSpectrum);
}
//����Ҷ�׵ĻҶȼ���ʾ
Mat graySpectrum(Mat spectrum)
{
	Mat dst;
	log(spectrum + 1, dst);
	//��һ��
	normalize(dst, dst, 0, 1, NORM_MINMAX);
	//Ϊ�˽��лҶȼ���ʾ��������ת��
	dst.convertTo(dst, CV_8UC1, 255, 0);
	return dst;
}
//����λ�� phase spectrum
Mat phaseSpectrum(Mat _srcFFT)
{
	//��λ��
	Mat phase;
	phase.create(_srcFFT.size(), CV_64FC1);
	//����ͨ��
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//������λ��
	for (int r = 0; r<phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			//ʵ�� �鲿
			double real = FFT2Channel[0].at<double>(r, c);
			double imaginary = FFT2Channel[1].at<double>(r, c);
			// atan2 �ķ���ֵ��Χ [0,180] [-180,0]
			phase.at<double>(r, c) = atan2(imaginary, real);
		}
	}
	return phase;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
		return -1;
	//��ͼ��ת��Ϊ������
	Mat fImg;
	img.convertTo(fImg, CV_64FC1, 1.0, 0);
	//���� -1^(r+c)
	int rows = fImg.rows;
	int cols = fImg.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if ((r + c) % 2)
				fImg.at<double>(r, c) *= -1;
		}
	}
	//���ٸ���Ҷ�任
	Mat fft2;
	fft2Image(fImg, fft2);
	//����Ҷ�任�ķ�����
	Mat ampSpec;
	amplitudeSpectrum(fft2, ampSpec);
	//�����׵ĻҶȼ���ʾ
	Mat graySpec = graySpectrum(ampSpec);
	imshow("�����׵ĻҶȼ���ʾ", graySpec);
	//��λ��
	Mat phaSpec = phaseSpectrum(fft2);
	//��λ�׵ĻҶȼ���ʾ
	imshow("��λ��", phaSpec);
	waitKey(0);
	return 0;
}
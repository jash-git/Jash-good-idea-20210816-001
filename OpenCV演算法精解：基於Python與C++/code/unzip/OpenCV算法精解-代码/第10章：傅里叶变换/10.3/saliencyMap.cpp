#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
void fft2Image(InputArray _src, OutputArray _dst);
//������� amplitude spectrum
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
//����λ�� phase spectrum
Mat phaseSpectrum(Mat _srcFFT);
int main(int argc, char*argv[])
{
	//����ͼ�񣨻ҶȻ���
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("ԭͼ", image);
	//ת��Ϊ double ����
	Mat fImage;
	image.convertTo(fImage, CV_64FC1,1.0/255);
	//���ٸ���Ҷ�任
	Mat fft2;
	fft2Image(fImage, fft2);
	//�����ף��ֳƸ���Ҷ�ף�
	Mat amplitude;
	amplitudeSpectrum(fft2, amplitude);
	//�Է����׽��ж�������
	Mat logAmplitude;
	cv::log(amplitude + 1.0, logAmplitude);
	//��ֵƽ��
	Mat meanLogAmplitude;
	cv::blur(logAmplitude, meanLogAmplitude, Size(3, 3),Point(-1,-1));
	//�ײв�
	Mat spectralResidual = logAmplitude - meanLogAmplitude;
	//��λ��
	Mat phase = phaseSpectrum(fft2);
	//������ cos(phase)
	Mat cosSpectrum(phase.size(), CV_64FC1);
	//������ sin(phase)
	Mat sinSpectrum(phase.size(), CV_64FC1);
	for (int r = 0; r < phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			cosSpectrum.at<double>(r, c) = cos(phase.at<double>(r, c));
			sinSpectrum.at<double>(r, c) = sin(phase.at<double>(r, c));
		}
	}
	//ָ������
	exp(spectralResidual, spectralResidual);
	Mat real = spectralResidual.mul(cosSpectrum);
	Mat imaginary = spectralResidual.mul(sinSpectrum);
	vector<Mat> realAndImag;
	realAndImag.push_back(real);
	realAndImag.push_back(imaginary);
	Mat complex;
	merge(realAndImag, complex);
	//���ٸ���Ҷ��任
	Mat ifft2;
	dft(complex, ifft2, DFT_COMPLEX_OUTPUT + DFT_INVERSE);
	//����Ҷ��任�ķ���
	Mat ifft2Amp;
	amplitudeSpectrum(ifft2, ifft2Amp);
	//ƽ������
	pow(ifft2Amp, 2.0, ifft2Amp);
	//��˹ƽ��
	GaussianBlur(ifft2Amp, ifft2Amp, Size(11,11), 2.5);
	//��������ʾ
	normalize(ifft2Amp, ifft2Amp, 1.0, 0, NORM_MINMAX);
	//�����Աȶȣ�����٤��任
	pow(ifft2Amp, 0.5, ifft2Amp);
	//��������ת��
	Mat saliencyMap;
	ifft2Amp.convertTo(saliencyMap, CV_8UC1,255);
	imshow("������", saliencyMap);

	waitKey(0);
	return 0;
}
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
//������� amplitude spectrum
void amplitudeSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum)
{
	//�жϸ���Ҷ�任������ͨ��
	CV_Assert(_srcFFT.channels() == 2);
	//����ͨ��
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//���㸵��Ҷ�任�ķ����� sqrt(pow(R,2)+pow(I,2))
	magnitude(FFT2Channel[0],FFT2Channel[1], _dstSpectrum);
}

//����λ�� phase spectrum
Mat phaseSpectrum(Mat _srcFFT)
{
	//��λ��
	Mat phase;
	phase.create(_srcFFT.size(),CV_64FC1);
	//����ͨ��
	vector<Mat> FFT2Channel;
	split(_srcFFT, FFT2Channel);
	//������λ��
	for (int r = 0; r<phase.rows; r++)
	{
		for (int c = 0; c < phase.cols; c++)
		{
			//ʵ�� 
			double real = FFT2Channel[0].at<double>(r, c);
			//�鲿
			double imaginary = FFT2Channel[1].at<double>(r, c);
			//������λ��
			phase.at<double>(r, c) = atan2(imaginary, real);
		}
	}
	return phase;
}
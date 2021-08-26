#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
Mat image;//�����ͼ�����
Mat fImageFFT;//ͼ��Ŀ��ٸ���Ҷ�任
Point maxLoc;//����Ҷ�׵����ֵ�����꣨���ĵ����꣩
//���ٸ���Ҷ�任
void fft2Image(InputArray _src, OutputArray _dst);
string windowName = "�����׵ĻҶȼ�";
//����Ҷ�任�ĸ���Ҷ��
Mat fImageFFT_spectrum;
//����¼�
bool drawing_box = false;
Point downPoint;
Rect rectFilter;
bool gotRectFilter = false;
void mouseRectHandler(int event, int x, int y, int, void*)
{
	switch (event)
	{
		//����������
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		//��¼���
		downPoint = Point(x, y);
		break;
		//�ƶ����
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			//����ƶ��� downPoint �����½�
			if (x >= downPoint.x && y >= downPoint.y)
			{
				rectFilter.x = downPoint.x;
				rectFilter.y = downPoint.y;
				rectFilter.width = x - downPoint.x;
				rectFilter.height = y - downPoint.y;
			}
			//����Ƶ��� downPoint �����Ͻ�
			if (x >= downPoint.x && y <= downPoint.y)
			{
				rectFilter.x = downPoint.x;
				rectFilter.y = y;
				rectFilter.width = x - downPoint.x;
				rectFilter.height = downPoint.y - y;
			}
			//����ƶ��� downPoint �����Ͻ�
			if (x <= downPoint.x && y <= downPoint.y)
			{
				rectFilter.x = x;
				rectFilter.y = y;
				rectFilter.width = downPoint.x - x;
				rectFilter.height = downPoint.y - y;
			}
			//����ƶ��� downPoint �����½�
			if (x <= downPoint.x && y >= downPoint.y)
			{
				rectFilter.x = x;
				rectFilter.y = downPoint.y;
				rectFilter.width = downPoint.x - x;
				rectFilter.height = y - downPoint.y;
			}
		}
		break;
	//�ɿ�������
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		gotRectFilter = true;
		break;
	default:
		break;
	}
}

//������
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
//�����׵ĻҶȼ���ʾ
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
int main(int argc, char*argv[])
{
	/* -- ��һ��������ͼ����� -- */
	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("ԭͼ", image);
	Mat fImage;
	image.convertTo(fImage, CV_32FC1, 1.0, 0.0);
	/* -- �ڶ���:ͼ������ÿһ�������� (-1)^(r+c) -- */
	for (int r = 0; r < fImage.rows; r++)
	{
		for (int c = 0; c < fImage.cols; c++)
		{
			if ((r + c) % 2)
				fImage.at<float>(r, c) *= -1;
		}
	}
	/* -- �������Ĳ������ٸ���Ҷ�任 -- */
	fft2Image(fImage, fImageFFT);
	//����Ҷ��
	Mat amplSpec;
	amplitudeSpectrum(fImageFFT, amplSpec);
	//����Ҷ�׵ĻҶȼ���ʾ
	Mat spectrum = graySpectrum(amplSpec);
	//�ҵ�����Ҷ�׵����ֵ������
	minMaxLoc(amplSpec, NULL, NULL, NULL, &maxLoc);
	/* -- ���岽���Զ����˲� -- */
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	setMouseCallback(windowName, mouseRectHandler, NULL);
	for (;;)
	{
		spectrum(rectFilter).setTo(0);
		/* -- ���������Զ����˲����븵��Ҷ�任��� -- */
		fImageFFT(rectFilter).setTo(Scalar::all(0));
		imshow(windowName, spectrum);
		//���� "Esc" ���˳��༭
		if (waitKey(10)== 27)
			break;
	}
	/* -- ���ߡ��˲�������Ҷ��任����ֻ����ʵ�� -- */
	Mat result;
	dft(fImageFFT, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* -- �ھŲ���ͬ���� (-1)^(r+c) --*/
	int rows = result.rows;
	int cols = result.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	//��������ת��
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/* -- ��ʮ�����ü�ͼƬ��ȡ���ϲ�*/
	result = result(Rect(0, 0, image.cols, image.rows));
	imshow("�����Զ����˲����ͼƬ", result);
	waitKey(0);
	return 0;
}
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

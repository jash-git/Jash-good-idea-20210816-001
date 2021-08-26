#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat image;//�����ͼ�����
Mat fImageFFT;//ͼ��Ŀ��ٸ���Ҷ�任
Point maxLoc;//����Ҷ�׵����ֵ������
int radius = 50;//��������
const int Max_RADIUS = 100;
int bandWid = 40;//����
const int MAX_BANDWID = 50;//������
Mat brFilter;//�����˲���
int brType = 0;//�����˲���������
const int MAX_BPTYPE = 2;
Mat fImageFFT_brFilter;//���踵��Ҷ�任
Mat fImageFFT_brFilter_spectrum;//���踵��Ҷ�任�ĸ���Ҷ��
Mat result;//�����ͨ�˲����Ч��
string brFilterspectrum = "���踵��Ҷ��";
//���ٸ���Ҷ�任
void fft2Image(InputArray _src, OutputArray _dst);
//����Ҷ�׵ĻҶȼ���ʾ��������Ǹ���Ҷ�任������Ǹ���Ҷ�׵ĻҶȼ�
void fourierSpectrum(InputArray _srcFFT, OutputArray _dstSpectrum);
void callback_brFilter(int, void*);
//�����˲�������
//ö�����ͣ���������˲���,��������˹�����˲�������˹�����˲���
enum BRFILTER_TYPE { IBR_FILTER = 0, BBR_FILTER = 1, GBR_FILTER = 2 };
//���������˲���
Mat createBRFilter(Size _size, Point center, float _radius, float _bandWidth, int type, int n = 2);
int main(int argc, char*argv[])
{
	/* -- ��һ��������ͼ����� -- */
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		return -1;
	}
	Mat fImage;
	image.convertTo(fImage, CV_32FC1, 1.0, 0.0);
	/* -- �ڶ�����ͼ������ÿһ�������� (-1)^(r+c) -- */
	for (int r = 0; r < fImage.rows; r++)
	{
		for (int c = 0; c < fImage.cols; c++)
		{
			if ((r + c) % 2)
				fImage.at<float>(r, c) *= -1;
		}
	}
	/* -- �����������ٸ���Ҷ�任 -- */
	fft2Image(fImage, fImageFFT);
	//����Ҷ�任�ĸ���Ҷ��
	Mat fImageFFT_spectrum;
	//����Ҷ�׵ĻҶȼ���ʾ
	fourierSpectrum(fImageFFT, fImageFFT_spectrum);
	//�ҵ�����Ҷ�׵����ֵ������
	minMaxLoc(fImageFFT_spectrum, NULL, NULL, NULL, &maxLoc);
	/* -- �����˲� -- */
	namedWindow(brFilterspectrum,WINDOW_AUTOSIZE);
	createTrackbar("��������:", brFilterspectrum, &brType, MAX_BPTYPE, callback_brFilter);
	createTrackbar("��������:", brFilterspectrum, &radius, Max_RADIUS, callback_brFilter);
	createTrackbar("����:", brFilterspectrum, &bandWid, MAX_BANDWID, callback_brFilter);
	callback_brFilter(0, 0);
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
void callback_brFilter(int, void*)
{
	/* -- ���Ĳ�����������˲��� -- */
	brFilter = createBRFilter(fImageFFT.size(), maxLoc, radius, bandWid, brType);
	/* -- ���岽�������˲�����ͼ����ٸ���Ҷ�任��� --*/
	fImageFFT_brFilter.create(fImageFFT.size(), fImageFFT.type());
	for (int r = 0; r < fImageFFT_brFilter.rows; r++)
	{
		for (int c = 0; c < fImageFFT_brFilter.cols; c++)
		{
			//�ֱ�ȡ����ǰλ�õĿ��ٸ���Ҷ�任�������ͨ�˲�����ֵ
			Vec2f temp_fImageFFT = fImageFFT.at<Vec2f>(r, c);
			float temp_brFilter = brFilter.at<float>(r, c);

			//�����˲�����ͼ��Ŀ��ٸ���Ҷ�任��Ӧλ�����
			fImageFFT_brFilter.at<Vec2f>(r, c) = temp_fImageFFT*temp_brFilter;
		}
	}
	//��ʾ��ͨ����Ҷ��
	fourierSpectrum(fImageFFT_brFilter, fImageFFT_brFilter_spectrum);
	imshow(brFilterspectrum, fImageFFT_brFilter_spectrum);
	imwrite("brSpectrum.jpg", fImageFFT_brFilter_spectrum);
	/* -- ���������Դ��踵��Ҷ�任ִ�и���Ҷ��任����ֻȡʵ�� -- */
	dft(fImageFFT_brFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* -- ���߲���ͬ����(-1)^(x+y) -- */
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/*--�ڰ˲�:��ȡ���ϲ���,��С��������ͼ��Ĵ�С*/
	result = result(Rect(0, 0, image.cols, image.rows)).clone();
	imshow("���������ͨ�˲����ͼƬ", result);
	imwrite("brresult.jpg", result);
}

//����Ҷ�׵ĻҶȼ���ʾ:������Ǹ���Ҷ�任,����Ǹ���Ҷ�׵ĻҶȼ�
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
//��������˲���
Mat createBRFilter(Size _size, Point center, float _radius, float _bandWidth, int type, int n)
{
	Mat _bpFilter(_size, CV_32FC1);
	int rows = _size.height;
	int cols = _size.width;
	CV_Assert(_bandWidth / 2 <= _radius);
	//������������˲���
	if (type == IBR_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (sqrt(norm2) <= _radius + _bandWidth / 2 && sqrt(norm2) >= _radius - _bandWidth / 2)
					_bpFilter.at<float>(r, c) = 0;
				else
					_bpFilter.at<float>(r, c) = 1;
			}
		}
	}
	//���������˹�����˲���
	if (type == BBR_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c<cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (norm2 != pow(_radius, 2))
					_bpFilter.at<float>(r, c) = 1.0 / (1.0 + pow(sqrt(norm2)*_bandWidth / (norm2 - pow(_radius, 2)), 2 * n));
				else
					_bpFilter.at<float>(r, c) = 0;
			}
		}
	}
	//�����˹�����˲�
	if (type == GBR_FILTER)
	{
		for (int r = 0; r< rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (norm2 != 0)
					_bpFilter.at<float>(r, c) = 1.0 - exp(-pow((norm2 - pow(_radius, 2)) / (_bandWidth*sqrt(norm2)), 2));
				else
					_bpFilter.at<float>(r, c) = 1;
			}
		}
	}
	return _bpFilter;
}
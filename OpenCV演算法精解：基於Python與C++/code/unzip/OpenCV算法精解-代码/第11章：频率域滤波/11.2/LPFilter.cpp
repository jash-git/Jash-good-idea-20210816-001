#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat I;//�����ͼ�����
Mat F;//ͼ��Ŀ��ٸ���Ҷ�任
Point maxLoc;//����Ҷ�׵����ֵ������
int radius = 20;//�ض�Ƶ��
const int Max_RADIUS = 100;//�������Ľض�Ƶ��
Mat lpFilter;//��ͨ�˲���
int lpType = 0;//��ͨ�˲���������
const int MAX_LPTYPE = 2;
Mat F_lpFilter;//��ͨ����Ҷ�任
Mat FlpSpectrum;//��ͨ����Ҷ�任�ĸ���Ҷ�׻Ҷȼ�
Mat result;//��ͨ�˲����Ч��
string lpFilterspectrum = "��ͨ����Ҷ��";//��ʾ���ڵ�����
//���ٸ���Ҷ�任
void fft2Image(InputArray _src, OutputArray _dst);
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
void callback_lpFilter(int, void*);
/*
��ͨ�˲������ͣ�
(�����ͨ�˲�����������˹��ͨ�˲�������˹��ͨ�˲���)
*/
enum LPFILTER_TYPE { ILP_FILTER = 0, BLP_FILTER = 1, GLP_FILTER = 2 };
//������ͨ�˲���
Mat createLPFilter(Size size, Point center, float radius, int type, int n=2);
int main(int argc, char*argv[])
{
	/* -- ��һ��������ͼ����� -- */
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	imwrite("I1.jpg", I);
	//��������ת����ת��Ϊ ������
	Mat fI;
	I.convertTo(fI, CV_32FC1, 1.0, 0.0);
	/* -- �ڶ�����ÿһ��������(-1)^(r+c) -- */
	for (int r = 0; r < fI.rows; r++)
	{
		for (int c = 0; c < fI.cols; c++)
		{
			if ((r + c) % 2)
				fI.at<float>(r, c) *= -1;
		}
	}
	/* -- �������Ĳ�������Ϳ��ٸ���Ҷ�任 -- */
	fft2Image(fI, F);
	//����Ҷ��
	Mat amplSpec;
	amplitudeSpectrum(F, amplSpec);
	//����Ҷ�׵ĻҶȼ���ʾ
	Mat spectrum = graySpectrum(amplSpec);
	imshow("ԭ����Ҷ�׵ĻҶȼ���ʾ", spectrum);
	imwrite("spectrum.jpg", spectrum);
	//�ҵ�����Ҷ�׵����ֵ������
	minMaxLoc(spectrum, NULL, NULL, NULL, &maxLoc);
	/* -- ��ͨ�˲� -- */
	namedWindow(lpFilterspectrum, WINDOW_AUTOSIZE);
	createTrackbar("��ͨ����:", lpFilterspectrum, &lpType, MAX_LPTYPE, callback_lpFilter);
	createTrackbar("�뾶:", lpFilterspectrum, &radius, Max_RADIUS, callback_lpFilter);
	callback_lpFilter(0, 0);
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
//�ص�������������ͨ�˲������ͣ����ض�Ƶ��
void callback_lpFilter(int, void*)
{
	/* -- ���岽�������ͨ�˲��� -- */
	lpFilter = createLPFilter(F.size(), maxLoc, radius, lpType, 2);
	/*-- ����������ͨ�˲�����ͼ����ٸ���Ҷ�任��� --*/
	F_lpFilter.create(F.size(), F.type());
	for (int r = 0; r < F_lpFilter.rows; r++)
	{
		for (int c = 0; c < F_lpFilter.cols; c++)
		{
			//�ֱ�ȡ����ǰλ�õĿ��ٸ���Ҷ�任�������ͨ�˲�����ֵ
			Vec2f F_rc = F.at<Vec2f>(r, c);
			float lpFilter_rc = lpFilter.at<float>(r, c);
			//��ͨ�˲�����ͼ��Ŀ��ٸ���Ҷ�任��Ӧλ�����
			F_lpFilter.at<Vec2f>(r, c) = F_rc*lpFilter_rc;
		}
	}

	//��ͨ����Ҷ�任�ĸ���Ҷ��
	amplitudeSpectrum(F_lpFilter,FlpSpectrum);
	//��ͨ����Ҷ�׵ĻҶȼ�����ʾ
	FlpSpectrum = graySpectrum(FlpSpectrum);
	imshow(lpFilterspectrum, FlpSpectrum);
	imwrite("FlpSpectrum.jpg", FlpSpectrum);
	/* -- ���ߡ��˲����Ե�ͨ����Ҷ�任ִ�и���Ҷ��任����ֻȡʵ�� -- */
	dft(F_lpFilter, result, DFT_SCALE + DFT_INVERSE + DFT_REAL_OUTPUT);
	/* -- �ھŲ���ͬ����(-1)^(x+y) -- */
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			if ((r + c) % 2)
				result.at<float>(r, c) *= -1;
		}
	}
	//ע�⽫���ת�� CV_8U ����
	result.convertTo(result, CV_8UC1, 1.0, 0);
	/* -- ��ʮ������ȡ���ϲ���,��С��������ͼ��Ĵ�С --*/
	result = result(Rect(0, 0, I.cols, I.rows)).clone();
	imshow("������ͨ�˲����ͼƬ", result);
	imwrite("lF.jpg", result);
}
//�����ͨ�˲���
Mat createLPFilter(Size size, Point center, float radius, int type, int n=2)
{
	Mat lpFilter = Mat::zeros(size, CV_32FC1);
	int rows = size.height;
	int cols = size.width;
	if (radius <= 0)
		return lpFilter;
	//���������ͨ�˲���
	if (type == ILP_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				float norm2 = pow(abs(float(r - center.y)), 2) + pow(abs(float(c - center.x)), 2);
				if (sqrt(norm2) < radius)
					lpFilter.at<float>(r, c) = 1;
				else
					lpFilter.at<float>(r, c) = 0;
			}
		}
	}
	//���������˹��ͨ�˲���
	if (type == BLP_FILTER)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c<cols; c++)
			{
				lpFilter.at<float>(r, c) = float(1.0 / (1.0 + pow(sqrt(pow(r - center.y, 2.0) + pow(c - center.x, 2.0)) /radius, 2.0*n)));
			}
		}
	}
	//�����˹��ͨ�˲�
	if (type == GLP_FILTER)
	{
		for (int r = 0; r< rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				lpFilter.at<float>(r, c) = float(exp(-(pow(c - center.x, 2.0) + pow(r - center.y, 2.0)) / (2 * pow(radius, 2.0))));
			}
		}
	}
	return lpFilter;
}
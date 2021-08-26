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
int main(int argc, char*argv[])
{
	//����ͼ�����
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
		return -1;
	//��������ת����ת��Ϊ������
	Mat fImg;
	img.convertTo(fImg, CV_64FC1);
	//���ٸ���Ҷ�任
	Mat fft2;
	fft2Image(fImg, fft2);
	//����Ҷ��任
	Mat image;
	cv::dft(fft2, image, DFT_INVERSE + DFT_REAL_OUTPUT + DFT_SCALE);
	//�ü�����Ҷ��任
	image = image(Rect(0, 0, img.cols, img.rows));
	return 0;
}

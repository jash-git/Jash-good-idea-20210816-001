#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//快速傅里叶变换
void fft2Image(InputArray _src, OutputArray _dst)
{
	//得到Mat类型
	Mat src = _src.getMat();
	//判断位深
	CV_Assert(src.type() == CV_32FC1 || src.type() == CV_64FC1);
	CV_Assert(src.channels() == 1 || src.channels() == 2);
	int rows = src.rows;
	int cols = src.cols;
	//为了进行快速的傅里叶变换，我们经行和列的扩充,找到最合适扩充值
	Mat padded;
	int rPadded = getOptimalDFTSize(rows);
	int cPadded = getOptimalDFTSize(cols);
	//进行边缘扩充,扩充值为零
	copyMakeBorder(src, padded, 0, rPadded - rows, 0, cPadded - cols, BORDER_CONSTANT, Scalar::all(0));
	//快速的傅里叶变换（双通道：用于存储实部 和 虚部）
	dft(padded, _dst, DFT_COMPLEX_OUTPUT);
}
int main(int argc, char*argv[])
{
	//输入图像矩阵
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
		return -1;
	//数据类型转换：转换为浮点型
	Mat fImg;
	img.convertTo(fImg, CV_64FC1);
	//快速傅里叶变换
	Mat fft2;
	fft2Image(fImg, fft2);
	//傅里叶逆变换
	Mat image;
	cv::dft(fft2, image, DFT_INVERSE + DFT_REAL_OUTPUT + DFT_SCALE);
	//裁剪傅里叶逆变换
	image = image(Rect(0, 0, img.cols, img.rows));
	return 0;
}

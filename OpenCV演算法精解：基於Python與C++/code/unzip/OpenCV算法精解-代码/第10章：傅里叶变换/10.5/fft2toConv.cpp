#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//利用快速傅里叶变换计算卷积，I 为浮点型矩阵
Mat fft2Conv(Mat I, Mat kernel, int borderType = BORDER_DEFAULT,Scalar value = Scalar())
{
	// I 的宽高
	int R = I.rows;
	int C = I.cols;
	// 卷积核 kernel 的宽高,均为奇数
	int r = kernel.rows;
	int c = kernel.cols;
	// 卷积核的半径 
	int tb = (r - 1) / 2;
	int lr = (c - 1) / 2;
	/* 第一步：边界扩充 */
	Mat I_padded;
	copyMakeBorder(I, I_padded, tb, tb, lr, lr, borderType, value);
	/* 第二步：对 I_padded 和 kernel 右侧和下侧补零，以满足快速傅里叶变换的行数和列数 */
	//满足二维快速傅里叶变换的行数、列数
	int rows = getOptimalDFTSize(I_padded.rows + r -1);
	int cols = getOptimalDFTSize(I_padded.cols + c - 1);
	//补零
	Mat I_padded_zeros, kernel_zeros;
	copyMakeBorder(I_padded, I_padded_zeros, 0, rows - I_padded.rows, 0, cols - I_padded.cols,BORDER_CONSTANT, Scalar(0,0,0,0));
	copyMakeBorder(kernel, kernel_zeros, 0, rows - kernel.rows, 0, cols - kernel.cols, BORDER_CONSTANT, Scalar(0,0,0,0));
	/* 第三步：快速傅里叶变换 */
	Mat fft2_Ipz,fft2_kz;
	dft(I_padded_zeros, fft2_Ipz, DFT_COMPLEX_OUTPUT);
	dft(kernel_zeros, fft2_kz, DFT_COMPLEX_OUTPUT);
	/* 第四步 ：两个傅里叶变换点乘 */
	Mat Ipz_kz;
	mulSpectrums(fft2_Ipz, fft2_kz, Ipz_kz, DFT_ROWS);
	/* 第五步：傅里叶逆变换，并只取实部 */
	Mat ifft2;
	dft(Ipz_kz, ifft2, DFT_INVERSE + DFT_SCALE + DFT_REAL_OUTPUT);
	/* 第六步：裁剪，同输入矩阵同样的尺寸 */
	Mat sameConv = ifft2(Rect(c - 1, r - 1, C + c - 1, R + r - 1));
	return sameConv;
}

int main(int argc, char*argv[])
{
	//输入矩阵
	Mat I = (Mat_<float>(7, 7)
			<< 34, 56, 1, 0, 255, 230, 45,
				0, 201, 101, 125, 52, 12, 124,
		        3, 41, 42, 40, 12, 90, 123, 
				5, 245, 98, 32, 34, 234, 90,
			   12, 12, 10, 41, 56, 89, 189,
			  112, 87, 12, 45, 78, 45, 10,
			   42, 123, 234, 12, 12, 21, 56);
	//卷积核
	Mat kernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	//通过傅里叶变换计算卷积
	Mat sameConv = fft2Conv(I, kernel, BORDER_DEFAULT);
	return 0;
}
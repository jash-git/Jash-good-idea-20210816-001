#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//���ÿ��ٸ���Ҷ�任��������I Ϊ�����;���
Mat fft2Conv(Mat I, Mat kernel, int borderType = BORDER_DEFAULT,Scalar value = Scalar())
{
	// I �Ŀ��
	int R = I.rows;
	int C = I.cols;
	// ����� kernel �Ŀ��,��Ϊ����
	int r = kernel.rows;
	int c = kernel.cols;
	// ����˵İ뾶 
	int tb = (r - 1) / 2;
	int lr = (c - 1) / 2;
	/* ��һ�����߽����� */
	Mat I_padded;
	copyMakeBorder(I, I_padded, tb, tb, lr, lr, borderType, value);
	/* �ڶ������� I_padded �� kernel �Ҳ���²ಹ�㣬��������ٸ���Ҷ�任������������ */
	//�����ά���ٸ���Ҷ�任������������
	int rows = getOptimalDFTSize(I_padded.rows + r -1);
	int cols = getOptimalDFTSize(I_padded.cols + c - 1);
	//����
	Mat I_padded_zeros, kernel_zeros;
	copyMakeBorder(I_padded, I_padded_zeros, 0, rows - I_padded.rows, 0, cols - I_padded.cols,BORDER_CONSTANT, Scalar(0,0,0,0));
	copyMakeBorder(kernel, kernel_zeros, 0, rows - kernel.rows, 0, cols - kernel.cols, BORDER_CONSTANT, Scalar(0,0,0,0));
	/* �����������ٸ���Ҷ�任 */
	Mat fft2_Ipz,fft2_kz;
	dft(I_padded_zeros, fft2_Ipz, DFT_COMPLEX_OUTPUT);
	dft(kernel_zeros, fft2_kz, DFT_COMPLEX_OUTPUT);
	/* ���Ĳ� ����������Ҷ�任��� */
	Mat Ipz_kz;
	mulSpectrums(fft2_Ipz, fft2_kz, Ipz_kz, DFT_ROWS);
	/* ���岽������Ҷ��任����ֻȡʵ�� */
	Mat ifft2;
	dft(Ipz_kz, ifft2, DFT_INVERSE + DFT_SCALE + DFT_REAL_OUTPUT);
	/* ���������ü���ͬ�������ͬ���ĳߴ� */
	Mat sameConv = ifft2(Rect(c - 1, r - 1, C + c - 1, R + r - 1));
	return sameConv;
}

int main(int argc, char*argv[])
{
	//�������
	Mat I = (Mat_<float>(7, 7)
			<< 34, 56, 1, 0, 255, 230, 45,
				0, 201, 101, 125, 52, 12, 124,
		        3, 41, 42, 40, 12, 90, 123, 
				5, 245, 98, 32, 34, 234, 90,
			   12, 12, 10, 41, 56, 89, 189,
			  112, 87, 12, 45, 78, 45, 10,
			   42, 123, 234, 12, 12, 21, 56);
	//�����
	Mat kernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	//ͨ������Ҷ�任������
	Mat sameConv = fft2Conv(I, kernel, BORDER_DEFAULT);
	return 0;
}
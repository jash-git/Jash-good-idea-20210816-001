#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	//�Ծ�����д���չʾ����任�Ĺ�ϵ
	Mat a = (Mat_<float>(5, 5) << 1, 2, 3, 4, 5,
		2, 3, 4, 5, 6,
		3, 4, 5, 6, 7,
		4, 5, 6, 7, 8,
		5, 6, 7, 8, 9);
	Mat b, c, d;
	dft(a, b, DFT_COMPLEX_OUTPUT);  //���任
	dft(b, c, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);  //��任ֻ���ʵ��
	idft(b, d, DFT_SCALE);  //��任

	//��ͼ����д���
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	resize(gray, gray, Size(502, 502));
	imshow("ԭͼ��", gray);

	//������ʵ���ɢ����Ҷ�任�ߴ�
	int rows = getOptimalDFTSize(gray.rows);
	int cols = getOptimalDFTSize(gray.cols);

	//��չͼ��
	Mat appropriate;
	int T = (rows - gray.rows) / 2;  //�Ϸ���չ����
	int B = rows - gray.rows - T;  //�·���չ����
	int L = (cols - gray.cols) / 2;  //�����չ����
	int R = cols - gray.cols - L;  //�Ҳ���չ����
	copyMakeBorder(gray, appropriate, T, B, L, R, BORDER_CONSTANT);
	imshow("��չ���ͼ��", appropriate);

	//������ɢ����Ҷ�任������
	Mat flo[2], complex;
	flo[0] = Mat_<float>(appropriate);  //ʵ������
	flo[1] = Mat::zeros(appropriate.size(), CV_32F);  //��������
	merge(flo, 2, complex);  //�ϳ�һ����ͨ������

	//������ɢ����Ҷ�任
	Mat result;
	dft(complex, result);

	//������ת��Ϊ��ֵ
	Mat resultC[2];
	split(result, resultC);  //�ֳ�ʵ��������
	Mat amplitude;
	magnitude(resultC[0], resultC[1], amplitude);

	//���ж���������ʽΪ�� M1 = log��1+M������֤������������0
	amplitude = amplitude + 1;
	log(amplitude, amplitude);//����Ȼ����

	//��ԭͼ��ߴ��Ӧ������								
	amplitude = amplitude(Rect(T, L, gray.cols, gray.rows));
	normalize(amplitude, amplitude, 0, 1, NORM_MINMAX);  //��һ��
	imshow("����Ҷ�任�����ֵͼ��", amplitude);  //��ʾ���

	//�������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
	int centerX = amplitude.cols / 2;
	int centerY = amplitude.rows / 2;
	//�ֽ���ĸ�С����
	Mat Qlt(amplitude, Rect(0, 0, centerX, centerY));//ROI���������
	Mat Qrt(amplitude, Rect(centerX, 0, centerX, centerY));//ROI���������
	Mat Qlb(amplitude, Rect(0, centerY, centerX, centerY));//ROI���������
	Mat Qrb(amplitude, Rect(centerX, centerY, centerX, centerY));//ROI���������

	//�������ޣ����Ϻ����½��н���
	Mat med;
	Qlt.copyTo(med);
	Qrb.copyTo(Qlt);
	med.copyTo(Qrb);
	//�������ޣ����º����Ͻ��н���
	Qrt.copyTo(med);
	Qlb.copyTo(Qrt);
	med.copyTo(Qlb);

	imshow("���Ļ���ķ�ֵͼ��", amplitude);
	waitKey(0);
	return 0;
}
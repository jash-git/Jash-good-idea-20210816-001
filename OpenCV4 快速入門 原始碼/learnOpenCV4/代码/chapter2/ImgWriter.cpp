#include <iostream>
#include <opencv2\opencv.hpp>

using	namespace std;
using	namespace cv;

void AlphaMat(Mat &mat)
{
	CV_Assert(mat.channels() == 4);
	for (int i = 0; i < mat.rows; ++i)
		{
			for (int j = 0; j < mat.cols; ++j)
			{
				Vec4b& bgra = mat.at<Vec4b>(i, j);
				bgra[0] = UCHAR_MAX;  // ��ɫͨ��
				bgra[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);  // ��ɫͨ��
				bgra[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);  // ��ɫͨ��
				bgra[3] = saturate_cast<uchar>(0.5 * (bgra[1] + bgra[2]));  // Alphaͨ��
			}
		}
}
int main(int agrc, char** agrv)
{
	// Create mat with alpha channel
	Mat mat(480, 640, CV_8UC4);
	AlphaMat(mat);
	vector<int> compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);  //PNG��ʽͼ��ѹ����־
	compression_params.push_back(9);  //�������ѹ������		
	bool result = imwrite("alpha.png", mat, compression_params);
	if (!result)
	{
		cout << "�����PNG��ʽͼ��ʧ��" << endl;
		return -1;
	}
	cout << "����ɹ�" << endl;
	return 0;
}

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<map>
#include<iostream>
using namespace std;
map<vector<int>, vector<Point>> HTLine(Mat I,Mat & accumulator,float stepTheta=1, float stepRho=1)
{
	//ͼ��Ŀ��
	int rows = I.rows;
	int cols = I.cols;
	//���ܳ��ֵ�����ߵĳ���
	int L = round(sqrt(pow(rows-1,2.0)+pow(cols-1,2.0)))+1;
	//��ʼ��ͶƱ��
	int numtheta = int(180.0 / stepTheta);
	int numRho = int(2 * L / stepRho + 1);
	accumulator=Mat::zeros(Size(numtheta, numRho), CV_32SC1);

	//��ʼ�� map �࣬���ڴ洢���ߵĵ�
	map<vector<int> , vector<Point>> lines;
	for (int i = 0; i < numRho; i++)
	{
		for (int j = 0; j < numtheta; j++)
		{
			lines.insert(make_pair(vector<int>(j,i),vector<Point>()));
		}
	}
	//ͶƱ����
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			if (I.at<uchar>(Point(x, y)) == 255)
			{
				for (int m = 0; m < numtheta; m++)
				{
					//��ÿһ���Ƕȣ������Ӧ�� rho ֵ
					float rho1 = x*cos(stepTheta*m / 180.0*CV_PI);
					float rho2 = y*sin(stepTheta*m / 180.0*CV_PI);
					float rho = rho1 + rho2;
					//����ͶƱ����һ������
					int n = int(round(rho + L) / stepRho);
					//�ۼ� 1
					accumulator.at<int>(n, m) += 1;
					//��¼�õ�
					lines.at(vector<int>(m,n)).push_back(Point(x,y));
				}
			}
		}
	}
	return lines;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	//ͼ���Ե���
	Mat edge;
	Canny(img, edge, 50, 200);
	//����ֱ�߼��
	Mat accu;//ͶƱ��
	map<vector<int>, vector<Point>> lines;
	lines = HTLine(edge, accu);
	//ͶƱ���ĻҶȼ����ӻ�
	double maxValue;//�ҵ�ͶƱ���е����ֵ
	minMaxLoc(accu, NULL, &maxValue, NULL, NULL);
	//��������ת������ͶƱ�����лҶȻ�
	Mat grayAccu;
	accu.convertTo(grayAccu, CV_8UC1,1.0 / maxValue*255);
	grayAccu = grayAccu.t();
	imshow("ͶƱ���ĻҶȼ���ʾ", grayAccu);
	imwrite("grayAccu.jpg", grayAccu);
	//����ͶƱ������ĳһ��ֵ��ֱ��
	int vote = 150;
	for (int r = 1; r < accu.rows-1; r++)
	{
		for (int c = 1; c < accu.cols-1; c++)
		{	
			int current = accu.at<int>(r, c);
			//��ֱ�ߣ�line ����ĩԪ��Ϊ��ʼ��
			if (current> vote)
			{
				
				int lt = accu.at<int>(r - 1, c - 1);//����
				int t = accu.at<int>(r - 1, c );//����
				int rt = accu.at<int>(r - 1, c+1);//����
				int l = accu.at<int>(r, c - 1);//��
				int right = accu.at<int>(r, c + 1);//��
				int lb = accu.at<int>(r+1, c - 1);//����
				int b = accu.at<int>(r - 1, c );//��
				int rb = accu.at<int>(r + 1, c+1);//��
				 //�жϸ�λ���ǲ��Ǿֲ����ֵ
				if (current > lt&& current > t && current > rt
					&&current > l && current > right&&
					current > lb && current > b&& current > rb)
				{
					vector<Point> line = lines.at(vector<int>(c, r));
					int s = line.size();
					//����
					cv::line(img, line.at(0), line.at(s - 1), Scalar(255), 2);
				}	
			}
		}
	}
	imshow("img", img);
	waitKey(0);
}
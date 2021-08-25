#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main() 
{
	Mat img = imread("faces.jpg");
	if (img.empty())
	{
		cout << "��ȷ���Ƿ�������ȷ��ͼ���ļ�" << endl;
		return -1;
	}

	//��ȡ����ʶ��ģ��
	String model_bin = "ch12_face_age/opencv_face_detector_uint8.pb";
	String config_text = "ch12_face_age/opencv_face_detector.pbtxt";
	Net faceNet = readNet(model_bin, config_text);

	//��ȡ�Ա���ģ��
	String genderProto = "ch12_face_age/gender_deploy.prototxt";
	String genderModel = "ch12_face_age/gender_net.caffemodel";
	String genderList[] = { "Male", "Female" };
	Net genderNet = readNet(genderModel, genderProto);
	if(faceNet.empty()&&genderNet.empty())
	{
		cout << "��ȷ���Ƿ�������ȷ��ģ���ļ�" << endl;
		return -1;
	}
	
	//������ͼ������������
	Mat blobImage = blobFromImage(img, 1.0, Size(300, 300), Scalar(), false, false);
	faceNet.setInput(blobImage, "data");
	Mat detect = faceNet.forward("detection_out");
	//�������ʡ��������������λ��
	Mat detectionMat(detect.size[2], detect.size[3], CV_32F, detect.ptr<float>());
	
	//��ÿ��������������Ա���
	int exBoundray = 25;  //ÿ�����������ĸ���������ĳߴ�
	float confidenceThreshold = 0.5;  //�ж�Ϊ�����ĸ�����ֵ����ֵԽ��׼ȷ��Խ��
	for (int i = 0; i < detectionMat.rows; i++) 
	{
		float confidence = detectionMat.at<float>(i, 2);  //���Ϊ�����ĸ���
		//ֻ�����ʴ�����ֵ������Ա�
		if (confidence > confidenceThreshold)
		{
			//���������������С
			int topLx = detectionMat.at<float>(i, 3) * img.cols;
			int topLy = detectionMat.at<float>(i, 4) * img.rows;
			int bottomRx = detectionMat.at<float>(i, 5) * img.cols;
			int bottomRy = detectionMat.at<float>(i, 6) * img.rows;
			Rect faceRect(topLx, topLy, bottomRx - topLx, bottomRy - topLy);

			//���������������ߴ�������䣬Ҫע���ֹ�ߴ���ͼ����ʵ�ߴ�֮��
			Rect faceTextRect;
			faceTextRect.x = max(0, faceRect.x - exBoundray);
			faceTextRect.y = max(0, faceRect.y - exBoundray);
			faceTextRect.width = min(faceRect.width + exBoundray, img.cols - 1);
			faceTextRect.height = min(faceRect.height + exBoundray, img.rows - 1);
			Mat face = img(faceTextRect);  //����������ͼ��

			//�����沿ͼ��ߴ�
			Mat faceblob = blobFromImage(face, 1.0, Size(227, 227), Scalar(), false, false);
			//����������沿ͼ�����뵽�Ա�������
			genderNet.setInput(faceblob);
			//��������
			Mat genderPreds = genderNet.forward();  //�����Ա�Ŀ�����

			//�Ա�����
			float male, female;
			male = genderPreds.at<float>(0, 0);
			female = genderPreds.at<float>(0, 1);
			int classID = male > female ? 0 : 1;
			String gender = genderList[classID];

			//��ԭͼ���л����沿�������Ա�
			rectangle(img, faceRect, Scalar(0, 0, 255), 2, 8, 0);
			putText(img, gender.c_str(), faceRect.tl(), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255), 2, 8);
		}
	}
	imshow("�Ա�����", img);
	waitKey(0);
	return 0;
}
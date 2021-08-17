#include<opencv2/opencv.hpp>
using namespace cv;

class QuickDemo //创建一个QuickDemo对象
{
    public:
        void colorSpace_Demo(Mat &imge); //定义一个类，里面包含输入一个图片，对图片操作
};

#include<quickopencv.h>
void QuickDemo::colorSpace_Demo(Mat &image)
{
    Mat gray, hsv;//定义2个矩阵类的图像gray和hsv，
    cvtColor(image,hsv,COLOR_BGR2HSV);//图像转换函数，可以把image转成hsv，第三个参数是转成的类型
    cvtColor(image,gray,COLOR_BGR2GRAY);//图像转换函数，可以把image转成hsv，第三个参数是转成的类型
    imshow("HSV",hsv);
    imshow("灰度",gray);
    imwrite("D:/hsv.jpg",hsv);//保存图片，前面是保存图的地址，后面是保存图的名称
    imwrite("D:/gray.jpg",gray);
}

#include<opencv2/opencv.hpp>
#include<iostream>
#include<quickopencv.h>

using namespace std;
using namespace cv;
int main() 
{

    Mat src = imread("D:/images/1.jpg",IMREAD_ANYCOLOR);//B,G,R实际上0-255三色。3通道
    //读取进来的数据以矩阵的形势,第二个参数代表显示一张灰度图像。
    if (src.empty()) 
    {
        printf("could not load image");//如果图片不存在 将无法读取，打印到终端。
        return-1;
    }
    //超过屏幕的图像无法显示时候调用此函数。

    namedWindow("输入窗口", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
    imshow("输入窗口", src);//表示显示在新创建的输入窗口上，第一个参数表示窗口名称，src表示数据对象Mat 
//在主函数中调用之前创建的类对象    
    QuickDemo qd;
    qd.colorSpace_Demo(src);

    waitKey(0);//执行到这句，程序阻塞。参数表示延时时间。单位ms
    destroyAllWindows();//销毁前面创建的显示窗口
    return0;
}
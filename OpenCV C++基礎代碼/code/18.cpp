void QuickDemo::norm_demo(Mat &image)
{
    Mat dst;//定义一个名为dst的二值化类型的数据
    std::cout << image.type() << std::endl;//打印出来图片的类型
    image.convertTo(image,CV_32F);//将dst数据转换成浮点型float32位数据。
    std::cout << image.type() << std::endl;//再次打印转换后的数据类型
    normalize(image, dst, 1.0, 0, NORM_MINMAX);//进行归一化操作
    std::cout << dst.type() << std::endl;//打印归一化操作之后的数据
    imshow("图像的归一化", dst);//显示归一化的图像
    //CV_8UC3 ,CV_32FC3  //3通道每个通道8位的UC类型
    //转换后 3通道 每个通道32位的浮点数
}
void QuickDemo::mat_creation_demo(Mat &image) 
{
    Mat m1, m2;
    m1 = image.clone();
    image.copyTo(m2);

    //创建空白图像
    Mat m3 = Mat::ones(Size(400, 400), CV_8UC3);//创建8*8的CV8位的无符号的n通道的unsigned char
    //ones&zeros是初始化的方法
    m3 = Scalar(255, 0, 0);//给三个通道都赋值127  ,单通道赋值方法 m3 = 127;
    //m3初始为蓝色
    //数据的宽度和长度是由通道数决定的。
    //std::cout << "width:"<<m3.cols<<"height"<< m3.rows <<"channels"<<m3.channels()<< std::endl;
    //用来查看宽度，高度与通道数。
    /*std::cout << m3 << std::endl;*/
    Mat m4 = m3.clone();//赋值M4就是M3 M4改变了,M3也改变了，没有产生新的自我(M4与M3同体)
    //M4为M3的克隆，M3还是原来的颜色，不会改变。(M4与M3不同体，各自是各自的颜色)
    //m3.copyTo(m4);//把M3赋值给M4，M4就是蓝色
    m4 = Scalar(0, 255, 255);//改变m4的颜色为黄色 ,m4也改变
    imshow("图像3", m3);//标题和图像名称   显示图像m3 纯蓝色
    imshow("图像4", m4);//标题和图像名称
}
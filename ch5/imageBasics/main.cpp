#include <iostream>
#include <chrono>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main( int argc,char** argv) {
    // 读取argv[1]指定的图像
    cv::Mat image;
    image = cv::imread( argv[1] );
    // 判断图像文件是否正确读取
    if ( image.data == nullptr )
    {
        std::cerr<<"文件"<<argv[1]<<"不存在."<<std::endl;
        return 0;
    }

    // 文件顺利读取，首先输出一些基本信息
    std::cout<<"图像宽为"<<image.cols<<",高为"<<image.rows<<",通道数为"<<image.channels()<<std::endl;
    imshow("image",image);
    cv::waitKey( 0 );   //0表示延迟时间
    // 判断 image 的类型
    if ( image.type() != CV_8UC1 && image.type() != CV_8UC3 )
    {
        // 图像类型不符合要求
        std::cout<<"请输入一张彩色图或灰度图"<<std::endl;
        return 0;
    }

    // 遍历图像，以下遍历方式亦可使用于随机访问
    // 使用 std::chrono 来给算法计时
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    for (size_t y = 0; y < image.rows; ++y) {
        for (size_t x = 0; x < image.cols; ++x) {
            // 访问位于 x,y 处的像素
            // 用 cv::Mat::ptr 获得图像的行指针
            unsigned char* row_ptr = image.ptr<unsigned char> ( y ); // row_ptr 是第 y 行的头指针
            unsigned char* data_ptr = &row_ptr[ x*image.channels() ]; // data_ptr 指向待访问的像素数据
            // 输出该像素的每个通道，如果是灰度图就只有一个通道
            for (int c = 0; c != image.channels() ; ++c) {
                unsigned char data = data_ptr[c]; // data 为 I(x,y) 第 c 个通道的值
            }
        }
    }
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double > time_used = std::chrono::duration_cast<std::chrono::duration
            <double >>( t2 - t1 );
    std::cout<<"遍历图像用时: "<<time_used.count()<<"秒"<<std::endl;

    // 关于 cv::Mat 的拷贝
    // 直接赋值并不会复制数据
    cv::Mat image_another = image;
    // 修改 image_another 会导致 image 发生变化
    image_another ( cv::Rect (0,0,100,100)).setTo( 0 ); // 将左上角 100X100 的块置零
    cv::imshow("image",image);
    cv::waitKey( 0 );

    // 使用 clone 函数来复制数据
    cv::Mat image_clone = image.clone();
    image_clone ( cv::Rect (0,0,100,100) ).setTo( 255 );
    cv::imshow("image",image);
    cv::imshow("image_clone",image_clone);
    cv::waitKey( 0 );

    cv::destroyAllWindows();
    return 0;
}
#include <iostream>
#include <chrono>

#include "LineDetector.h"

#include <bitset>



void generate()
{
    vision::LineDetector lineDetector;
    for (int num = 0; num < 256; num ++)
    {
        std::array<uchar, 8> nums;
        for (int i = 0; i < 8; i++)
            nums[i] = (num >> i) & 1;
        if (!(num % 32)) std::cout << std::endl;
        std::cout << (bool)(lineDetector.checkAllCondition(0, nums) || lineDetector.checkAllCondition(1, nums)) <<  ", " ;

    }
}

int main()
{
//    generate();
//    return 0;
    vision::LineDetector lineDetector;

    cv::Mat oimg, img = cv::imread("/Users/nikitas/Projects/rrcVision/images/line.png");

    cv::cvtColor(img, img, CV_BGR2GRAY);
    cv::imshow("original", img);
    cv::threshold(img, oimg, 200, 255, cv::THRESH_BINARY);

    cv::Mat c = oimg.clone();
    clock_t t = clock();
    lineDetector.zhangSuen(oimg);
    std::cout << double(clock() - t) / CLOCKS_PER_SEC * 1000.0 << std::endl;


    cv::imshow("threshold::img1", oimg);
    cv::imshow("threshold::img2", c);
    cv::waitKey(10);


    cv::waitKey();
    return 0;
}

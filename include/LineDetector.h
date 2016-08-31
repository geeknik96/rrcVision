//
// Created by Nikita Somenkov on 10/08/16.
//

#pragma once

#include <array>

#include <opencv2/opencv.hpp>

namespace vision {

    class LineDetector {
    public:
        cv::Mat zhangSuen(cv::Mat &binImage);
        cv::Mat simpleThin(cv::Mat &binImage);
        bool checkAllCondition(char iteration, const std::array<uchar, 8> &neighbours);
    private:
        int fillNeighbours(const cv::Mat &window, bool *neighbours);


    };

}


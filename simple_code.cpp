//
// Created by Nikita Somenkov on 12/08/16.
//

#include <vector>

#include <opencv2/core.hpp>

std::vector<std::vector<uchar>> t(const cv::Mat &mat)
{
    std::vector<std::vector<uchar>> result(mat.rows);
    for (auto & row : result) row.resize(mat.cols);

    for (int r = 0; r < mat.rows; ++r) {
        for (int c = 0; c < mat.cols; ++c) {

        }
    }
    return result;
}

cv::Mat t(const std::vector<std::vector<uchar>> &mat)
{
    cv::Mat result();
}

void zhangSuen(char **)
{

}


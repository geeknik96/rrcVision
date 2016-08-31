//
// Created by Nikita Somenkov on 10/08/16.
//

#include <array>
#include <list>
#include <stack>

#include "LineDetector.h"

static const char table[] {
        0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0
};

cv::Mat vision::LineDetector::zhangSuen(cv::Mat &binImage)
{
    assert(binImage.depth() == CV_8U);
    assert(binImage.channels() == 1);

    const int rows = binImage.rows;
    const int cols = binImage.cols;

    bool neighbours[8];

    std::vector<cv::Point> points(rows * cols);

    int inter =0 ;
    int count;
    do {
        count = 0;



        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {

                if (!binImage.at<uchar>(r, c))
                    continue;

//                std::cout << r << ' ' << c << " ";

                // TODO:optimize from construct
                const cv::Rect window(c - 1, r - 1, 3, 3);

                int idx= fillNeighbours(binImage(window), neighbours);
//
//                std::stack<cv::Point> stack;
//
//                do {
//                    if ( table[ans] == )
//                } while(!stack.empty());

                if ( table[idx] )
                {
                    points[count++] = cv::Point(c, r);
                }
            }
        }

        for (int i = 0; i < count; ++i)
            binImage.at<uchar>(points[i]) = 0;
        inter++;

//        cv::imshow("tmp", binImage);
//        cv::waitKey();

//        std::cout << lst.size() << std::endl;
    } while (count != 0);

    std::cout << inter << std::endl;

    return cv::Mat();
}

int vision::LineDetector::fillNeighbours(const cv::Mat &window, bool *neighbours)
{
    static const int indexes [][2] {
            {0, 1}, {0, 2}, {1, 2}, {2, 2},
            {2, 1}, {2, 0}, {1, 0}, {0, 0}
    };

    int table_idx = 0;

    const uchar *data = window.ptr(0);
    for (int i = 0; i < sizeof(indexes) / sizeof(*indexes); ++i)
    {
        const int  * idx = indexes[i];
        neighbours[i] = window.at<uchar>(idx[0], idx[1]);
        table_idx = table_idx << 1 | neighbours[i];
    }
    return table_idx;
}


bool vision::LineDetector::checkAllCondition(char iteration, const std::array<uchar, 8> &neighbours)
{
    // TODO: uchar * uchar  = ?(type)
    if (iteration == 0) {
        if (neighbours[1] * neighbours[3] * neighbours[5] != 0 ||
            neighbours[3] * neighbours[5] * neighbours[7] != 0)
            return false;
    }
    else {
        if (neighbours[1] * neighbours[3] * neighbours[7] != 0 ||
            neighbours[1] * neighbours[5] * neighbours[7] != 0)
            return false;
    }

    int seqCount = 0;
    int sum = neighbours[0];

    for (size_t i = 1; i < neighbours.size(); ++i)
    {
        if (neighbours[i] == 1 && neighbours[i - 1] == 0)
            if (++ seqCount > 1) return false;

        sum += neighbours[i];
    }

    seqCount += (neighbours[0] == 1 && neighbours[7] == 0) ? 1 : 0;

    return 2 <= sum && sum <= 6 && seqCount == 1;
}

cv::Mat vision::LineDetector::simpleThin(cv::Mat &binImage) {
    const uchar white = 255;
    for (int r = 0; r < binImage.rows; r++) {
        for (int c = 0, e; c < binImage.cols; c++) {
            uchar px = binImage.at<uchar>(r, c);
            if (px != white) continue;
            e = c;
            while (px == white && e < binImage.cols)
                px = binImage.at<uchar>(r, e++);
            int dx = e - c;
            if (dx > 1 && dx < 30)
                binImage.at<uchar>(r, c + dx / 2) = 255;
            c = e;
        }
    }

    //scan y
    for (int c = 0; c < binImage.cols; c++) {
        for (int r = 0, e; r < binImage.rows; r++) {
            uchar px = binImage.at<uchar>(r, c);
            if (px != white) continue;
            e = r;
            while (px == white && e < binImage.rows)
                px = binImage.at<uchar>(e++, c);
            int dx = e - r;
            if (dx > 1 && dx < 30)
                binImage.at<uchar>(r + dx / 2, c) = 255;
            r = e;
        }
    }
    return cv::Mat();
}


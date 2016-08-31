//
// Created by Nikita Somenkov on 15/08/16.
//

#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

//static const uchar colors[] = {25, 75, 125, 175, 225, 0};
static const uchar colors[] = {88, 139, 124, 200, 0};
cv::Scalar ctable[] = {
        cv::Scalar { 124, 135, 88 },
        cv::Scalar { 225, 225, 225 },
        cv::Scalar { 60,  255, 255 },
        cv::Scalar { 180, 189, 123 }
};

cv::Vec3b getColor(cv::Vec3b color)
{
    double min_diff = 255.0;
    cv::Vec3b result{0, 0, 0};
    for (const uchar *r = colors; *r; ++r)
    {
        for (const uchar *g = colors; *g; ++g)
        {
            for (const uchar *b = colors; *b; ++b)
            {
                const cv::Vec3b current_color { *b, *g, *r };
                const double diff = cv::norm(color - current_color);
                if (diff < min_diff) min_diff = diff, result = current_color;
            }
        }
    }
    return result;
}

cv::Vec3b getColor2(cv::Vec3b color) {
    double min_diff = 255.0;
    cv::Vec3b result(0, 0, 0);
    cv::Scalar c(color[0], color[1], color[2]);
    for (int i = 0; i < sizeof(ctable) / sizeof(*ctable); ++i) {
        const cv::Scalar elem = ctable[i];
        if (cv::norm(c - elem) < min_diff) min_diff = cv::norm(c - elem), result = cv::Vec3b(elem[0], elem[1], elem[2]);
    }
    return result;
}

void applyColor(cv::Mat & mat)
{
    for (int r = 0; r < mat.rows; ++r)
    {
        for (int c = 0; c < mat.cols; ++c)
        {
            cv::Vec3b &color = mat.at<cv::Vec3b>(r, c);
            color = getColor2(color);
        }
    }
}


int main(int argc, char **argv)
{
    const std::string config_path = argv[1];
    const std::string save_dir = argv[2];
    int i = 0;
    while (true)
    {
        std::string path = save_dir + "/" + std::to_string(i) + ".png";
        cv::Mat image = cv::imread(path), orginal_image;

        cv::imshow("original", image);
        applyColor(image);
        cv::imshow("result", image);

        cv::Mat lines;
        cv::inRange(image, cv::Scalar::all(225), cv::Scalar::all(225), lines);
        cv::imshow("lines", lines);


        int key = cv::waitKey();

        if (key == 27) break;
        else if (key == '1') i--;
        else if (key == '2') i++;
    }
}

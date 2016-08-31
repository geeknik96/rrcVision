//
// Created by Nikita Somenkov on 10/08/16.
//

#include "BallDetector.h"

vision::BallDetector::BallDetector() : BaseDetector("BallDetector") { }

cv::Rect vision::BallDetector::detect(const cv::Mat &image)
{
    std::vector<cv::Rect> balls;
    mBallCascade.detectMultiScale(image, balls);
    return chooseBestBall(balls);
}


cv::Rect vision::BallDetector::chooseBestBall(const std::vector<cv::Rect> &balls)
{
    auto rect = std::max_element(balls.cbegin(), balls.cend(),
         [](cv::Rect &r1, cv::Rect &r2) -> bool {
             return r1.area() > r2.area();
         });
    return rect != balls.cend() ? *rect : cv::Rect();
}

void vision::BallDetector::load(const boost::property_tree::ptree &config)
{
    mConfig.cascadePath = config.get<std::string>("cascadePath");
    mConfig.minNeighbors = config.get<int>("minNeighbors");
    mConfig.scaleFactor = config.get<int>("scaleFactor");
}

void vision::BallDetector::save(boost::property_tree::ptree &config)
{
    config.put("cascadePath", mConfig.cascadePath);
    config.put("minNeighbors", mConfig.minNeighbors);
    config.put("scaleFactor", mConfig.scaleFactor);
}

vision::BallDetector::~BallDetector()
{

}

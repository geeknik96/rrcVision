//
// Created by Nikita Somenkov on 10/08/16.
//

#pragma once

#include "opencv2/objdetect.hpp"

#include "BaseDetector.h"

namespace vision {

    class BallDetector : public BaseDetector
    {
    public:
        BallDetector();

        cv::Rect detect(const cv::Mat &image);

        virtual void load(const boost::property_tree::ptree & config);
        virtual void save(boost::property_tree::ptree & config);

        ~BallDetector();

    private:
        cv::Rect chooseBestBall(const std::vector<cv::Rect> &balls);

        cv::CascadeClassifier mBallCascade;

        struct config
        {
            std::string cascadePath; //
            double scaleFactor; // > 1.0
            int minNeighbors; // > 0
        } mConfig;
    };

}




//
// Created by Nikita Somenkov on 10/08/16.
//

#pragma once

#include <opencv2/core.hpp>

#include <boost/property_tree/ptree.hpp>

namespace vision
{

    class BaseDetector
    {
    public:

        BaseDetector(const std::string & name);

        virtual void detect(boost::any& val, const cv::Mat & image) = 0;

        const std::string & name();

        virtual void load(const boost::property_tree::ptree & config) = 0;
        virtual void save(boost::property_tree::ptree & config) = 0;

    private:
        std::string mName;
    };

}

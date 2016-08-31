//
// Created by Nikita Somenkov on 10/08/16.
//

#include "BaseDetector.h"


vision::BaseDetector::BaseDetector(const std::string &name) : mName(name) { }


const std::string &vision::BaseDetector::name()
{
    return mName;
}

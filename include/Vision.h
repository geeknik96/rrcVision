//
// Created by Nikita Somenkov on 10/08/16.
//

#pragma once

#include <list>
#include <memory>

#include "BallDetector.h"
#include "LineDetector.h"

namespace vision {

    class Vision
    {
    public:
        void addDetector(std::shared_ptr<BaseDetector> detector);

    private:
        std::list<std::shared_ptr<BaseDetector>> mDetectors;

    };

}




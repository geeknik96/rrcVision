//
// Created by Nikita Somenkov on 10/08/16.
//

#include "Vision.h"

std::shared_ptr<BallDetector> vision::Vision::ballDetector()
{
    return mBallDetector;
}

std::shared_ptr<LineDetector> vision::Vision::lineDetector()
{
    return mLineDetector;
}

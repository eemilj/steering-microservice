#include "SteeringAngleCalculator.h"
#include <cmath>
#include <iostream>

double angle(const cv::Point& v1, const cv::Point& v2) {
    double cosAngle = v1.dot(v2) / (cv::norm(v1) * cv::norm(v2));
    if (cosAngle > 1.0)
        return 0.0;
    else if (cosAngle < -1.0)
        return CV_PI;
    return std::acos(cosAngle);
}

double SteeringAngleCalculator::calculateSteeringAngle(cones foundCones) {
    double steeringAngle;
    std::vector<cv::Point> hypotenuse, vector = {foundCones.blue.first, foundCones.blue.second};

    //squareroot of x² + y²
    //x / magnitude, y / magnitude

    auto cone = foundCones.blue.first;
    auto cone2 = foundCones.blue.second;

    //

    if( !(  (foundCones.blue.first.x == 0 && foundCones.blue.first.y == 0) ||
            (foundCones.blue.second.x == 0 && foundCones.blue.second.y == 0))) {
        steeringAngle = angle(foundCones.blue.first, foundCones.blue.second);
        std::cout << " Found angle: " << steeringAngle << std::endl;
    }else {
        steeringAngle = 3;
    }
    return steeringAngle;
}


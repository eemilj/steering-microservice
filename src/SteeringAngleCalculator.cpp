#include "SteeringAngleCalculator.h"
#include <cmath>
#include <iostream>
#define INVALID_ANGLE 3;

double angle(const cv::Point& v1, const cv::Point& v2) {
    double cosAngle = v1.dot(v2) / (cv::norm(v1) * cv::norm(v2));
    if (cosAngle > 1.0)
        return 0.0;
    else if (cosAngle < -1.0)
        return CV_PI;
    return std::acos(cosAngle);
}

double SteeringAngleCalculator::calculateSteeringAngle(cones foundCones, double distanceReading) {
    double steeringAngle, blueConeAngle, yellowConeAngle;

    blueConeAngle = findConeAngle(foundCones.blue);
    yellowConeAngle = findConeAngle(foundCones.yellow);


    return blueConeAngle;
}

double SteeringAngleCalculator::findConeAngle(std::pair<cv::Point, cv::Point> cone){
    double coneAngle;
    if( !(  (cone.first.x == 0 && cone.first.y == 0) ||
            (cone.second.x == 0 && cone.second.y == 0))) {
        coneAngle = angle(cone.first, cone.second);
        std::cout << " Found angle: " << coneAngle << std::endl;
    }else {
        coneAngle = INVALID_ANGLE;
    }
    return coneAngle;
}


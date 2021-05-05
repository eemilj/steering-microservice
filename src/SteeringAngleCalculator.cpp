#include "SteeringAngleCalculator.h"
#include <cmath>
#include <iostream>
#define INVALID_ANGLE 3;

double angle(const cv::Point& vector1, const cv::Point& vector2) {
    double cosAngle = vector1.dot(vector2) / (cv::norm(vector1) * cv::norm(vector2));
    if (cosAngle > 1.0)
        return 0.0;
    else if (cosAngle < -1.0)
        return CV_PI;
    return std::acos(cosAngle);
}

double SteeringAngleCalculator::calculateSteeringAngle(cones foundCones, double distanceReading) {
    double steeringAngle, blueConeAngle, yellowConeAngle;

    blueConeAngle = findConeAngle(foundCones.blue);
    //yellowConeAngle = findConeAngle(foundCones.yellow);


    return blueConeAngle;
}

double SteeringAngleCalculator::findConeAngle(std::pair<cv::Point, cv::Point> cone){
    double coneAngle;
    cv::Point vector1, vector2;
    if( !(  (cone.first.x == 0 && cone.first.y == 0) ||
            (cone.second.x == 0 && cone.second.y == 0))) {
        vector1 ={cone.second.x - cone.first.x, cone.second.y - cone.first.y};
        vector2 = {1,0};
        coneAngle = angle(vector1, vector2);
        std::cout << " Found angle: " << coneAngle / CV_PI*180 << std::endl;
    }else {
        coneAngle = INVALID_ANGLE;
    }
    return coneAngle;
}


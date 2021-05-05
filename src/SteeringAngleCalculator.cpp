#include "SteeringAngleCalculator.h"
#include <cmath>
#include <iostream>

const int INVALID_ANGLE = 361;

double angle(const cv::Point& vector1, const cv::Point& vector2) {
    double cosAngle = vector1.dot(vector2) / (cv::norm(vector1) * cv::norm(vector2));
    if (cosAngle > 1.0) {
        return 0.0;
    }
    else if (cosAngle < -1.0) {
        return CV_PI;
    }
    return std::acos(cosAngle)/CV_PI*180;
}

double SteeringAngleCalculator::outputSteeringAngle(double lastSteeringAngle, cones foundCones, double distanceReading){
    double calculatedSteeringAngle = calculateSteeringAngle(foundCones);
    double steeringAngle;

    if (distanceReading >= 0.7) {
        return 0;
    }
    if((int)calculatedSteeringAngle == INVALID_ANGLE){
        return lastSteeringAngle;
    }

    if((int)calculatedSteeringAngle < 90){
        steeringAngle = -(0.3-(calculatedSteeringAngle/90)*0.3);
    } else {
        steeringAngle = (calculatedSteeringAngle/90)*0.3-0.3;
    }

    return steeringAngle;
}

double SteeringAngleCalculator::calculateSteeringAngle(cones foundCones) {
    double blueConeAngle, yellowConeAngle;

    blueConeAngle = findConeAngle(foundCones.blue);
    yellowConeAngle = findConeAngle(foundCones.yellow);


    if((int)blueConeAngle == INVALID_ANGLE && (int)yellowConeAngle == INVALID_ANGLE){
        return INVALID_ANGLE;
    }
    if((int)blueConeAngle == INVALID_ANGLE) {
        return yellowConeAngle;
    }
    if((int)yellowConeAngle == INVALID_ANGLE) {
        return blueConeAngle;
    }

    if ((foundCones.yellow.second.x-320) < (320 - foundCones.blue.second.x)){
        return yellowConeAngle;
    }
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
    }else {
        coneAngle = INVALID_ANGLE;
    }
    return coneAngle;
}


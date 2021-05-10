#include "SteeringAngleCalculator.h"
#include <cmath>
#include <iostream>

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

double SteeringAngleCalculator::outputSteeringAngle(double lastSteeringAngle, const cones& foundCones, double distanceReading){
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

double SteeringAngleCalculator::calculateSteeringAngle(const cones& foundCones) {
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

    if (abs(foundCones.yellow.second.position.x-320) < abs(320 - foundCones.blue.second.position.x)){
        return yellowConeAngle;
    }
    return blueConeAngle;
}

double SteeringAngleCalculator::findConeAngle(const std::pair<cone, cone>& cones){
    double coneAngle;
    cv::Point vector1, vector2;
    if( !(  (cones.first.position.x == 0 && cones.first.position.y == 0) ||
            (cones.second.position.x == 0 && cones.second.position.y == 0))) {
        vector1 ={cones.second.position.x - cones.first.position.x, cones.second.position.y - cones.first.position.y};
        vector2 = {1,0};
        coneAngle = angle(vector1, vector2);
    }else {
        coneAngle = INVALID_ANGLE;
    }
    return coneAngle;
}


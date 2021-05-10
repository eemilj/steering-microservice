#ifndef STEERINGANGLECALCULATOR_H
#define STEERINGANGLECALCULATOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageRecognitionController.h"

class SteeringAngleCalculator {
public:
    static double calculateSteeringAngle(const cones& foundCones);
    static double findConeAngle(const std::pair<cv::Point, cv::Point>& cones);
    static double outputSteeringAngle(double lastSteeringAngle, const cones& foundCones, double distanceReading);
};

static const int INVALID_ANGLE = 361;


#endif //STEERINGANGLECALCULATOR_H

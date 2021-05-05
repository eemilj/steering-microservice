#ifndef STEERINGANGLECALCULATOR_H
#define STEERINGANGLECALCULATOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageRecognitionController.h"
class SteeringAngleCalculator {
public:
    static double calculateSteeringAngle(cones foundCones);
    static double findConeAngle(std::pair<cv::Point, cv::Point> cone);
    static double outputSteeringAngle(double lastSteeringAngle, cones foundCones, double distanceReading);
};


#endif //STEERINGANGLECALCULATOR_H

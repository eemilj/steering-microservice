#ifndef STEERINGANGLECALCULATOR_H
#define STEERINGANGLECALCULATOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageRecognitionController.hpp"

class SteeringAngleCalculator {
public:
    static double calculateSteeringAngle(const cones& foundCones);
    static double findConeAngle(const std::pair<cone, cone>& cones);
    static double outputSteeringAngle(const double &lastSteeringAngle, const cones& foundCones, const double &distanceReading);
};

static const int INVALID_ANGLE = 361;
static const double MAX_STEERING_ANGLE = 0.29;
static const double DISTANCE_READING_THRESHOLD = 0.7;
static const int QUARTER_CIRCLE_DEGREE = 90;
static const int HALF_CIRCLE_DEGREE = 180;


#endif //STEERINGANGLECALCULATOR_H

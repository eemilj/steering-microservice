#ifndef STEERINGANGLECALCULATOR_H
#define STEERINGANGLECALCULATOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageRecognitionController.h"
class SteeringAngleCalculator {
public:
    static double calculateSteeringAngle(cones foundCones);
};


#endif //STEERINGANGLECALCULATOR_H

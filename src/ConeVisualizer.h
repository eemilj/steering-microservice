#ifndef CONEVISUALIZER_H
#define CONEVISUALIZER_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageRecognitionController.h"

class ConeVisualizer {
public:
    static cv::Mat createDebugImage(cv::Mat &image, const cones &foundCones, cluon::data::TimeStamp timeStamp, double steeringAngle);
};


#endif
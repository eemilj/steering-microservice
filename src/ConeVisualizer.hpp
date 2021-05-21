#ifndef CONEVISUALIZER_H
#define CONEVISUALIZER_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ImageRecognitionController.hpp"

class ConeVisualizer {
public:
    static cv::Mat createDebugImage(const cv::Mat &image, const cones &foundCones, const cluon::data::TimeStamp &timeStamp, const double &steeringAngle);
};


#endif
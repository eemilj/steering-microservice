#ifndef IMAGERECOGNITIONCONTROLLER_H
#define IMAGERECOGNITIONCONTROLLER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ConeDetector.hpp"

struct cones {
    std::pair<cone, cone> blue = {};
    std::pair<cone, cone> yellow = {};
};

class ImageRecognitionController {
public:
    static cones findConeCoordinates(const cv::Mat& image);
};


#endif
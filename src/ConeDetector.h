#ifndef CONEDETECTOR_H
#define CONEDETECTOR_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct cone {
    cv::Point position = {};
    cv::Rect boundingRectangle = {};
};

class ConeDetector {
public:
    static std::pair<cone, cone>  findCenterCoordinate(const cv::Mat& image);
    static std::vector<std::vector<cv::Point>> detectContours(const cv::Mat& image);
};


#endif //CONEDETECTOR_H

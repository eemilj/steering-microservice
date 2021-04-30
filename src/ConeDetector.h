#ifndef CONEDETECTOR_H
#define CONEDETECTOR_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ConeDetector {
public:
    static std::pair<cv::Point, cv::Point> findCenterCoordinate(const cv::Mat& image);
    static std::vector<std::vector<cv::Point>> detectContours(const cv::Mat& image);

};


#endif //CONEDETECTOR_H

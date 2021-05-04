#ifndef CONEVISUALIZER_H
#define CONEVISUALIZER_H


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//This can be deleted when the testing is done.
struct contours {
    std::vector<std::vector<cv::Point>> blue = {};
    std::vector<std::vector<cv::Point>> yellow = {};
};

class ConeVisualizer {
public:
    static contours testingContourDrawing(const cv::Mat &image);
    static cv::Mat drawContoursImage(cv::Mat &image);
};


#endif
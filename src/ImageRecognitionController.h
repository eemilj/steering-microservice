#ifndef IMAGERECOGNITIONCONTROLLER_H
#define IMAGERECOGNITIONCONTROLLER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct cones {
    std::pair<cv::Point, cv::Point> blue = {};
    std::pair<cv::Point, cv::Point> yellow = {};
};
//This can be deleted when the testing is done.
struct contours {
    std::vector<std::vector<cv::Point>> blue = {};
    std::vector<std::vector<cv::Point>> yellow = {};
};

class ImageRecognitionController {
public:
    static cones findConeCoordinates(const cv::Mat& image, cv::Scalar lo, cv::Scalar hi);
    static contours testingContourDrawing(const cv::Mat& image);

};


#endif //IMAGERECOGNITIONCONTROLLER_H
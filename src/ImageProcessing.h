#ifndef IMAGEPROCESSING
#define IMAGEPROCESSING

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcessing {

public:
    cv::Mat processImage(cv::Mat image);
};


#endif

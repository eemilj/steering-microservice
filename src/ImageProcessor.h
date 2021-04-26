#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcessor {

public:
    cv::Mat processImage(const cv::Mat& image, int width, int height);
};


#endif

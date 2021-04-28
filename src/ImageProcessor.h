#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcessor {

public:
    static cv::Mat processImage(const cv::Mat& image, cv::Scalar lowRange, cv::Scalar highRange);
    static cv::Mat cropImage(const cv::Mat& image, int width, int height);
    static cv::Mat filterImage(const cv::Mat& image, const cv::Scalar& hi, const cv::Scalar& lo);
    static cv::Mat denoiseImage(const cv::Mat& image);
};


#endif

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcessor {

public:
    cv::Mat processImage(const cv::Mat& image, int width, int height);
    cv::Mat cropImage(const cv::Mat& image, int width, int height);
    cv::Mat filterImage(const cv::Mat& image, const cv::Scalar& hi, const cv::Scalar& lo);
    cv::Mat denoiseImage(const cv::Mat& image);
};


#endif

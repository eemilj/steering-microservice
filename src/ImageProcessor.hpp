#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcessor {

public:
    static cv::Mat processImage(const cv::Mat& image, const cv::Scalar &lowRange, const cv::Scalar &highRange);
    static cv::Mat cropImage(const cv::Mat& image, const int &width, const int &height);
    static cv::Mat filterImage(const cv::Mat& image, const cv::Scalar& lowRange, const cv::Scalar& highRange);
    static cv::Mat denoiseImage(const cv::Mat& image);
    static cv::Mat bilateralFiltering(const cv::Mat& image);
};


#endif

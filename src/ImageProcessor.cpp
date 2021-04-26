#include "ImageProcessor.h"


cv::Mat ImageProcessor::processImage(const cv::Mat& image, int width, int height) {
    cv::Mat maskBlue, maskYellow, croppedImage, processedImage;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(100, 100, 45);
    blueHigh = cv::Scalar(150,255,255);

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    croppedImage = cropImage(image, width, height);
    maskBlue = filterImage(croppedImage, blueHigh, blueLow);
    maskYellow = filterImage(croppedImage, yellowHigh, yellowLow);
    processedImage = maskYellow + maskBlue;
    return processedImage;
}

cv::Mat ImageProcessor::cropImage(const cv::Mat& image, int width, int height) {
    cv::Mat output;
    cv::Rect crop;
    int halfImgHeight;

    halfImgHeight = height/2;
    crop = cv::Rect(0, halfImgHeight, width, halfImgHeight);
    output = image(crop);
    return output;
}

cv::Mat ImageProcessor::filterImage(const cv::Mat& image, const cv::Scalar& hi, const cv::Scalar& lo) {
    cv::Mat output;
    cv::cvtColor(image, output, cv::COLOR_BGR2HSV);
    cv::inRange(output, lo, hi, output);
    return output;
}

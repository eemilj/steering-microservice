#include "ImageProcessor.h"


cv::Mat ImageProcessor::processImage(const cv::Mat& image, int width, int height) {
    int halfImgHeight;
    cv::Rect crop;
    cv::Mat maskBlue, maskYellow, input, output;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(100, 100, 45);
    blueHigh = cv::Scalar(150,255,255);

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    halfImgHeight = height/2;
    crop = cv::Rect(0, halfImgHeight, width, halfImgHeight);

    input = image(crop);
    cv::cvtColor(input, input, cv::COLOR_BGR2HSV);

    cv::inRange(input, blueLow, blueHigh, maskBlue);
    cv::inRange(input, yellowLow, yellowHigh, maskYellow);
    output = maskYellow + maskBlue;

    return output;
}

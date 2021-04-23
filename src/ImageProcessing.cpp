#include "ImageProcessing.h"


cv::Mat ImageProcessing::processImage(cv::Mat image) {

    cv::Scalar blueLow = cv::Scalar(100, 100, 45);
    cv::Scalar blueHigh = cv::Scalar(150,255,255);

    cv::Scalar yellowLow = cv::Scalar(14, 100, 120);
    cv::Scalar yellowHigh = cv::Scalar(30,255,255);

    cv::cvtColor(image, image, cv::COLOR_BGR2HSV);
    cv::Mat maskBlue;
    cv::Mat mask;
    cv::Rect crop = cv::Rect(0,240,640,240);
    cv::inRange(image, blueLow, blueHigh, maskBlue);
    cv::inRange(image, yellowLow, yellowHigh, mask);
    mask += maskBlue;
    mask = mask(crop);
    return mask;
}

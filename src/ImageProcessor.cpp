#include "ImageProcessor.h"

cv::Mat ImageProcessor::processImage(const cv::Mat& image, int width, int height) {
    cv::Mat maskBlue, maskYellow, croppedImage, processedImage;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(100, 100, 45); //100, 100, 45
    blueHigh = cv::Scalar(150,255,255);

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    croppedImage = cropImage(image, width, height);
    maskBlue = filterImage(croppedImage, blueHigh, blueLow);
    //maskYellow = filterImage(croppedImage, yellowHigh, yellowLow);
    //processedImage = maskYellow + maskBlue;
    processedImage = maskBlue;
    processedImage = denoiseImage(processedImage);

    return processedImage;
}

cv::Mat ImageProcessor::cropImage(const cv::Mat& image, int width, int height) {
    cv::Mat output;
    cv::Rect crop;
    int halfImgHeight;

    halfImgHeight = height/2;
    //Top half of image is cropped away.
    crop = cv::Rect(0, halfImgHeight, width, halfImgHeight);
    output = image(crop);
    //Bottom part of image is cropped away
    crop = cv::Rect(0, halfImgHeight, width, int(halfImgHeight/1.8));
    output = image(crop);
    return output;
}

cv::Mat ImageProcessor::filterImage(const cv::Mat& image, const cv::Scalar& hi, const cv::Scalar& lo) {
    cv::Mat output;
    cv::cvtColor(image, output, cv::COLOR_BGR2HSV);
    cv::inRange(output, lo, hi, output);
    return output;
}

cv::Mat ImageProcessor::denoiseImage(const cv::Mat &image) {
    cv::Mat outputImage;

    cv::erode(image, outputImage, cv::Mat(), cv::Point(-1,-1), 3);
    cv::dilate(outputImage, outputImage,cv::Mat(),cv::Point(-1,-1), 4); //4 was found

    return outputImage;
}

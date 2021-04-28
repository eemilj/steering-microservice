#include "ImageProcessor.h"

cv::Mat ImageProcessor::processImage(const cv::Mat& image, cv::Scalar lowRange, cv::Scalar highRange) {
    cv::Mat maskColor, croppedImage, processedImage;
    int width, height;
    height = image.rows;
    width = image.cols;

    croppedImage = cropImage(image, width, height);
    maskColor = filterImage(croppedImage, highRange, lowRange);
    processedImage = denoiseImage(maskColor);

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

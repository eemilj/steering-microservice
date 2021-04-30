#include "ImageProcessor.h"

cv::Mat ImageProcessor::processImage(const cv::Mat& image, cv::Scalar lowRange, cv::Scalar highRange) {
    cv::Mat maskColor, croppedImage, processedImage, bilateralFilteredImage;
    int width, height;
    height = image.rows;
    width = image.cols;

    croppedImage = cropImage(image, width, height);
    bilateralFilteredImage = bilateralFiltering(croppedImage);
    maskColor = filterImage(bilateralFilteredImage, highRange, lowRange);
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

cv::Mat ImageProcessor::bilateralFiltering(const cv::Mat& image){
    cv::Mat output, hsvImg, processedImage, channels[3];
    cv::cvtColor(image, hsvImg, cv::COLOR_BGR2HSV);
    cv::split(hsvImg, channels);
    channels[1] = channels[1]*1.6;
    channels[2] = channels[2]*1.3;
    cv::merge(channels,3, hsvImg);
    cv::cvtColor(hsvImg, output, cv::COLOR_HSV2BGR);
    cv::bilateralFilter(output, processedImage, 4, 60, 20);
    return processedImage;
}

cv::Mat ImageProcessor::denoiseImage(const cv::Mat &image) {
    cv::Mat outputImage;
    //196 hits with old, 477 hits in close followed by open, 707 in open followed by close

    //remove noise
    cv::morphologyEx(image, outputImage, cv::MORPH_OPEN,
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));

    //fill objects
    cv::morphologyEx(outputImage, outputImage, cv::MORPH_CLOSE,
                     cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
    //smooth the image
    cv::medianBlur(outputImage, outputImage, 5);

    return outputImage;
}

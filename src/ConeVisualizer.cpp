#include "ConeVisualizer.h"
#include "ImageProcessor.h"
#include "ConeDetector.h"

// This is just for testing purposes, it can be deleted in the future.
contours ConeVisualizer::testingContourDrawing(const cv::Mat &image) {
    contours found;
    cv::Mat processedImage;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(110, 140, 50); //100, 100, 45
    blueHigh = cv::Scalar(130,255,100);

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    processedImage = ImageProcessor::processImage(image, yellowLow, yellowHigh);
    found.yellow = ConeDetector::detectContours(processedImage);
    processedImage = ImageProcessor::processImage(image, blueLow, blueHigh);
    found.blue = ConeDetector::detectContours(processedImage);
    return found;
}

cv::Mat ConeVisualizer::drawContoursImage(cv::Mat &image) {
    cv::Mat contourImage;
    contourImage = cv::Mat(image.rows, image.cols, CV_8UC3, cv::Scalar(0,0,0));
    contourImage = ImageProcessor::cropImage(contourImage, contourImage.cols, contourImage.rows);
    contours contours;
    contours = testingContourDrawing(image);
    cv::drawContours(contourImage, contours.blue, -1, cv::Scalar(255,255,255), 1);
    cv::drawContours(contourImage, contours.yellow, -1, cv::Scalar(255,255,255), 1);
    return contourImage;
}




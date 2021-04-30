#include "ImageRecognitionController.h"
#include "ImageProcessor.h"
#include "ConeDetector.h"

cones ImageRecognitionController::findConeCoordinates(const cv::Mat& image) {
    cones foundCones;
    cv::Mat processedImage;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(90, 145, 55); //90, 145, 55
    blueHigh = cv::Scalar(125,255,100); // 125, 255, 125

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    processedImage = ImageProcessor::processImage(image, yellowLow, yellowHigh);
    foundCones.yellow = ConeDetector::findCenterCoordinate(processedImage);

    processedImage = ImageProcessor::processImage(image, blueLow, blueHigh);
    foundCones.blue = ConeDetector::findCenterCoordinate(processedImage);

    return foundCones;
}
// This is just for testing purposes, it can be deleted in the future.
contours ImageRecognitionController::testingContourDrawing(const cv::Mat &image) {
    contours found;
    cv::Mat processedImage;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(90, 145, 55); //100, 100, 45
    blueHigh = cv::Scalar(125,255,125);

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    processedImage = ImageProcessor::processImage(image, yellowLow, yellowHigh);
    found.yellow = ConeDetector::detectContours(processedImage);
    processedImage = ImageProcessor::processImage(image, blueLow, blueHigh);
    found.blue = ConeDetector::detectContours(processedImage);
    return found;
}
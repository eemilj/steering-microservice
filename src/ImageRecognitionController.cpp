#include "ImageRecognitionController.h"
#include "ImageProcessor.h"
#include "ConeDetector.h"

cones ImageRecognitionController::findConeCoordinates(const cv::Mat& image) {
    cones foundCones;
    cv::Mat processedImage;
    cv::Scalar blueLow, blueHigh, yellowLow, yellowHigh;

    blueLow = cv::Scalar(100, 100, 45); //100, 100, 45
    blueHigh = cv::Scalar(150,255,255);

    yellowLow = cv::Scalar(14, 100, 120);
    yellowHigh = cv::Scalar(30,255,255);

    processedImage = ImageProcessor::processImage(image, yellowLow, yellowHigh);
    foundCones.yellow = ConeDetector::findCenterCoordinate(processedImage);

    processedImage = ImageProcessor::processImage(image, blueLow, blueHigh);
    foundCones.blue = ConeDetector::findCenterCoordinate(processedImage);

    return foundCones;
}

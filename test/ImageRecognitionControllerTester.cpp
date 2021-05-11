#include "catch.hpp"
#include "ImageRecognitionController.h"

TEST_CASE("Test find cone coordinates") {
    const int OFFSET = 20, CROP_VALUE = 240;
    cones actualCones;
    cv::Mat testImage;
    cv::Point topLeftBlue, bottomRightBlue, topLeftYellow, bottomRightYellow, expectedMiddlePointBlue, expectedMiddlePointYellow;
    cv::Scalar white, blue, yellow;
    white = cv::Scalar(255, 255, 255);
    blue = cv::Scalar(62, 32, 41);
    yellow = cv::Scalar(0, 255, 255);
    topLeftBlue = cv::Point(50, 300);
    bottomRightBlue = cv::Point(50 + OFFSET, 300 + OFFSET);
    topLeftYellow = cv::Point(100,300);
    bottomRightYellow = cv::Point(100 + OFFSET, 300 + OFFSET);
    testImage = cv::Mat(480, 640, CV_8UC3, white);
    expectedMiddlePointBlue = cv::Point(50 + OFFSET/2 + 1, 300 + OFFSET/2 + 1 - CROP_VALUE);
    expectedMiddlePointYellow = cv::Point(100 + OFFSET/2 + 1, 300 + OFFSET/2 + 1 - CROP_VALUE);
    cv::rectangle(testImage, topLeftBlue, bottomRightBlue  , blue, -1);
    cv::rectangle(testImage, topLeftYellow, bottomRightYellow ,yellow, -1);

    actualCones = ImageRecognitionController::findConeCoordinates(testImage);

    REQUIRE(expectedMiddlePointBlue == actualCones.blue.first.position);
    REQUIRE(expectedMiddlePointYellow == actualCones.yellow.first.position);
}
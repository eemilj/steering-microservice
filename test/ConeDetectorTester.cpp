#include "catch.hpp"
#include "ConeDetector.h"
#include <iostream>

TEST_CASE("Test object position") {
    //Calculated center points of the two generated squares
    const cv::Point EXPECTED_RESULT_ONE = {35,45}, EXPECTED_RESULT_TWO = {90, 100};
    cv::Point rectangleOneTopLeft, rectangleOneBottomRight, rectangleTwoTopLeft, rectangleTwoBottomRight;
    cv::Scalar hi, lo, white, black;
    cv::Mat testImage, resultImage;
    std::pair<cv::Point, cv::Point> foundPoints;

    //drawing first rectangle in the top left corner of the image
    rectangleOneTopLeft = cv::Point(10, 20); //20, 20
    rectangleOneBottomRight = cv::Point(60, 70);

    //drawing second rectangle lower than the first rectangle
    rectangleTwoTopLeft = cv::Point(70, 80);
    rectangleTwoBottomRight = cv::Point(110, 120);

    //Generate test picture with two rectangles
    white = cv::Scalar(255, 255, 255);
    black = cv::Scalar(0, 0, 0);
    testImage = cv::Mat(480, 640, CV_8UC3, black);
    cv::rectangle(testImage, rectangleOneTopLeft, rectangleOneBottomRight, white, 1);
    cv::rectangle(testImage, rectangleTwoTopLeft, rectangleTwoBottomRight, white, 1);

    foundPoints = ConeDetector::findCenterCoordinate(testImage);

    REQUIRE(foundPoints.first.x == EXPECTED_RESULT_ONE.x);
    REQUIRE(foundPoints.first.y == EXPECTED_RESULT_ONE.y);
    REQUIRE(foundPoints.second.x == EXPECTED_RESULT_TWO.x);
    REQUIRE(foundPoints.second.y == EXPECTED_RESULT_TWO.y);
}

TEST_CASE("Test contours") {
    const int RADIUS = 40;
    cv::Point circleCenterPoint;
    cv::Scalar white, black;
    cv::Mat testImage;
    std::vector<std::vector<cv::Point>> results;
    double sumOfMagnitudes = 0;
    int numberOfPoints = 0;

    //Generate black test picture with white circle
    circleCenterPoint = cv::Point(50, 60);
    white = cv::Scalar(255, 255, 255);
    black = cv::Scalar(0, 0, 0);
    testImage = cv::Mat(480, 640, CV_8UC3, black);
    cv::circle(testImage, circleCenterPoint, RADIUS, white, 1);

    results = ConeDetector::detectContours(testImage);

    for(auto &result : results) {
        for(auto &point : result) {
            numberOfPoints++;
            sumOfMagnitudes += cv::norm(point-circleCenterPoint);
        }
    }
    REQUIRE(RADIUS == int(sumOfMagnitudes/numberOfPoints));
}
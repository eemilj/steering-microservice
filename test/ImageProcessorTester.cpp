#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ImageProcessor.h"
// Best test
TEST_CASE("Sanity check") {
    REQUIRE(true);
}
// THIS WORKS!
TEST_CASE("Test crop function") {
    int width, height;
    cv::Mat image, output;
    height = 480;
    width = 640;

    image = cv::Mat(height, width, CV_64FC1);
    output = ImageProcessor::cropImage(image, image.cols, image.rows);
    REQUIRE(output.cols == width);
    REQUIRE(output.rows == int((height/2)/1.8));
}

TEST_CASE("Test HSV shifting") {
    // Drawn square is 20x20 so circumference is 80px.
    const int EXPECTED_RESULT = 80;
    int testResult;
    cv::Point topLeft, bottomRight;
    cv::Scalar hi, lo, white, blue;
    cv::Mat testImage, resultImage;

    topLeft = cv::Point(0,40);
    bottomRight = cv::Point(20, 20);

    white = cv::Scalar(255, 255, 255);
    blue = cv::Scalar(255, 0, 0);
    lo = cv::Scalar(100, 100, 45);
    hi = cv::Scalar(150,255,255);

    testImage = cv::Mat(480, 640, CV_8UC3, white);
    cv::rectangle(testImage, topLeft, bottomRight, blue, 1);

    resultImage = ImageProcessor::filterImage(testImage, hi, lo);
    testResult = cv::countNonZero(resultImage);
    REQUIRE(testResult == EXPECTED_RESULT);
}
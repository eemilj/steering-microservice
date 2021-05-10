#include "catch.hpp"
#include "SteeringAngleCalculator.h"
#include "ImageRecognitionController.h"


TEST_CASE("Test calculation for steering angle") {
    cones testCones;
    const int EXPECTED_STEERING_ANGLE = 90;

    double steeringAngle;
    testCones.blue.first = cv::Point(0,1);
    testCones.blue.second = cv::Point(0,0);
    testCones.yellow.first = cv::Point(640,1);
    testCones.yellow.second = cv::Point(640,0);
    SECTION("Test valid for valid angle") {
        steeringAngle = SteeringAngleCalculator::calculateSteeringAngle(testCones);
        REQUIRE((int)steeringAngle==EXPECTED_STEERING_ANGLE);
    }
    SECTION("Test valid for invalid angle") {
        testCones.blue.first = cv::Point(0,0);
        testCones.blue.second = cv::Point(0,0);
        testCones.yellow.first = cv::Point(0,0);
        testCones.yellow.second = cv::Point(0,0);
        steeringAngle = SteeringAngleCalculator::calculateSteeringAngle(testCones);
        REQUIRE((int)steeringAngle== INVALID_ANGLE);
    }

}

TEST_CASE("Test find angles for cones") {
    std::pair<cv::Point, cv::Point> cones;
    const int EXPECTED_ANGLE = 90;
    double angle;
    cones.first = cv::Point(1,1);
    cones.second = cv::Point(1,0);
    angle = SteeringAngleCalculator::findConeAngle(cones);
    REQUIRE((int)angle==EXPECTED_ANGLE);
}

TEST_CASE("Test steering angle") {
    const int LAST_STEERING_ANGLE = 25;
    double distanceReading, steeringAngle;
    cones testCones;
    distanceReading = 0.3;
    testCones.blue.first = cv::Point(0,0);
    testCones.blue.second = cv::Point(0,0);
    testCones.yellow.first = cv::Point(0,0);
    testCones.yellow.second = cv::Point(0,0);

    SECTION("Test steering angle with high distance reading"){
        distanceReading = 1;
        steeringAngle = SteeringAngleCalculator::outputSteeringAngle(LAST_STEERING_ANGLE,testCones,distanceReading);
        REQUIRE((int)steeringAngle==0);
    }
    SECTION("Test steeringAngle with invalid calculated angle") {
        steeringAngle = SteeringAngleCalculator::outputSteeringAngle(LAST_STEERING_ANGLE,testCones,distanceReading);
        REQUIRE((int)(steeringAngle)==LAST_STEERING_ANGLE);
    }
    SECTION("Test steeringAngle with angle less than 90 degrees") {
        testCones.blue.first = cv::Point(0,2);
        testCones.blue.second = cv::Point(1,1);
        steeringAngle = SteeringAngleCalculator::outputSteeringAngle(LAST_STEERING_ANGLE,testCones,distanceReading);
        REQUIRE(steeringAngle < 0);
    }
    SECTION("Test steeringAngle with angle more than 90 degrees") {
        testCones.blue.first = cv::Point(1,2);
        testCones.blue.second = cv::Point(0,1);
        steeringAngle = SteeringAngleCalculator::outputSteeringAngle(LAST_STEERING_ANGLE,testCones,distanceReading);
        REQUIRE(steeringAngle > 0);
    }
}

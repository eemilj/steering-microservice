#include "ConeDetector.h"
#include <iostream>


bool compareContourAreas (const std::vector<cv::Point>& contour1, const std::vector<cv::Point>& contour2) {
    double i = fabs( contourArea(cv::Mat(contour1)) );
    double j = fabs( contourArea(cv::Mat(contour2)) );
    return ( i > j );
}

std::pair<cone, cone> ConeDetector::findCenterCoordinate(const cv::Mat& image) {

    std::vector<std::vector<cv::Point>> contours;
    std::pair<cone, cone> foundCones;
    foundCones.first.position = cv::Point(0,0);
    foundCones.second.position = cv::Point(0,0);

    contours = detectContours(image);
    if(!contours.empty()) {
        std::sort(contours.begin(), contours.end(), compareContourAreas);
        foundCones.first.boundingRectangle = cv::boundingRect(contours[0]);
        foundCones.first.position.x = foundCones.first.boundingRectangle.x + foundCones.first.boundingRectangle.width/2;
        foundCones.first.position.y = foundCones.first.boundingRectangle.y + foundCones.first.boundingRectangle.width/2;
        if(contours.size() > 1) {
            foundCones.second.boundingRectangle = cv::boundingRect(contours[1]);
            foundCones.second.position.x = foundCones.second.boundingRectangle.x + foundCones.second.boundingRectangle.width/2;
            foundCones.second.position.y = foundCones.second.boundingRectangle.y + foundCones.second.boundingRectangle.width/2;
        }
    }
    return foundCones;
}

std::vector<std::vector<cv::Point>> ConeDetector::detectContours(const cv::Mat &image) {
    cv::Mat output;
    std::vector<std::vector<cv::Point>> contours, convexHulls;
    std::vector<cv::Point> convexHull;
    cv::Canny(image, output, 80, 160);
    cv::findContours(output, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for(auto &contour : contours) {
        cv::convexHull(contour, convexHull);
        convexHulls.push_back(convexHull);
    }

    return convexHulls;
}
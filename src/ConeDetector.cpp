#include "ConeDetector.h"
#include <iostream>


bool compareContourAreas (std::vector<cv::Point> contour1, std::vector<cv::Point> contour2) {
    double i = fabs( contourArea(cv::Mat(contour1)) );
    double j = fabs( contourArea(cv::Mat(contour2)) );
    return ( i > j );
}

cv::Point pointFinder(cv::Moments moment) {
    int centerX, centerY;
    centerX = int(moment.m10 / moment.m00);
    centerY = int(moment.m01 / moment.m00);
    cv::Point foundPoint;
    foundPoint.x = centerX;
    foundPoint.y = centerY;
    return foundPoint;
}

std::pair<cv::Point, cv::Point> ConeDetector::findCenterCoordinate(const cv::Mat& image) {
    //cv::Rect boundingRectangle;
    //std::vector<cv::Vec4i> elementsHierarchy;
    std::vector<std::vector<cv::Point>> contours;
    std::pair<cv::Point, cv::Point> foundPoints;
    foundPoints.first = cv::Point(0,0);
    foundPoints.second = cv::Point(0,0);

    contours = detectContours(image);
    if(!contours.empty()) {
        //sort the thing for reasons unknown
        std::sort(contours.begin(), contours.end(), compareContourAreas);
        cv::Moments largest = cv::moments(contours[0]);
        if(contours.size() > 1) {
            cv::Moments secondLargest = cv::moments(contours[1]);
            foundPoints.second = pointFinder(secondLargest);
        }
        foundPoints.first = pointFinder(largest);
    }
    return foundPoints;
}

std::vector<std::vector<cv::Point>> ConeDetector::detectContours(const cv::Mat &image) {
    cv::Mat output;
    std::vector<std::vector<cv::Point>> contours, approximatedContours, convexHulls, convexHulls3_10;
    std::vector<cv::Point> approximatedContour, convexHull, convexHull3_10;
    cv::Canny(image, output, 80, 160);
    cv::findContours(output, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for(auto &contour : contours) {
        cv::approxPolyDP(contour, approximatedContour, 10, true);
        approximatedContours.push_back(approximatedContour);
    }

    for(auto &contour : contours) {
        cv::convexHull(contour, convexHull);
        convexHulls.push_back(convexHull);
    }

    for(auto & i : convexHulls) {
        if(i.size() >= 3 && i.size() <= 10) {
            cv::convexHull(i, convexHull3_10);
            convexHulls3_10.push_back(convexHull3_10);
        }
    }

    return convexHulls3_10;
}
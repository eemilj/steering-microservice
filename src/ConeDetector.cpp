#include "ConeDetector.h"

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
    std::vector<cv::Vec4i> elementsHierarchy;
    std::vector<std::vector<cv::Point>> contours;
    std::pair<cv::Point, cv::Point> foundPoints;
    foundPoints.first = cv::Point(0,0);
    foundPoints.second = cv::Point(0,0);

    cv::Canny(image, image, 50, 200);

    cv::findContours(image, contours, elementsHierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    //sort the thing for reasons unknown
    if(!contours.empty()) {
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
#include "ConeVisualizer.h"
#include "ImageProcessor.h"
#include "ConeDetector.h"

cv::Point adjustPosition(const cv::Point& position) {
    cv::Point adjustedPoint;
    adjustedPoint.x = position.x;
    adjustedPoint.y = position.y + 240;
    return adjustedPoint;
}

cv::Mat ConeVisualizer::drawContoursImage(cv::Mat &image, const cones& foundCones) {

    cv::Mat contourImage;
    contourImage = image.clone();
    cv::Scalar blue = cv::Scalar(255, 0, 0);
    cv::Scalar yellow = cv::Scalar(0, 255, 255);

    cv::rectangle(contourImage, adjustPosition(foundCones.blue.first.boundingRectangle.tl()),
                  adjustPosition(foundCones.blue.first.boundingRectangle.br()),blue,2);
    cv::rectangle(contourImage, adjustPosition(foundCones.blue.second.boundingRectangle.tl()),
                  adjustPosition(foundCones.blue.second.boundingRectangle.br()),blue,2);
    cv::rectangle(contourImage, adjustPosition(foundCones.yellow.first.boundingRectangle.tl()),
                  adjustPosition(foundCones.yellow.first.boundingRectangle.br()),yellow,2);
    cv::rectangle(contourImage, adjustPosition(foundCones.yellow.second.boundingRectangle.tl()),
                  adjustPosition(foundCones.yellow.second.boundingRectangle.br()),yellow,2);
    return contourImage;
}




#include <cluon-complete.hpp>
#include "ConeVisualizer.h"
#include "ConeDetector.h"

cv::Point adjustPosition(const cv::Point& position) {
    cv::Point adjustedPoint;
    adjustedPoint.x = position.x;
    adjustedPoint.y = position.y + 240;
    return adjustedPoint;
}

cv::Mat ConeVisualizer::createDebugImage(cv::Mat &image, const cones &foundCones, cluon::data::TimeStamp timeStamp, double steeringAngle) {

    cv::Mat debugImage;
    debugImage = image.clone();
    cv::Scalar blue = cv::Scalar(255, 0, 0);
    cv::Scalar yellow = cv::Scalar(0, 255, 255);

    cv::rectangle(debugImage, adjustPosition(foundCones.blue.first.boundingRectangle.tl()),
                  adjustPosition(foundCones.blue.first.boundingRectangle.br()), blue, 2);
    cv::rectangle(debugImage, adjustPosition(foundCones.blue.second.boundingRectangle.tl()),
                  adjustPosition(foundCones.blue.second.boundingRectangle.br()), blue, 2);
    cv::rectangle(debugImage, adjustPosition(foundCones.yellow.first.boundingRectangle.tl()),
                  adjustPosition(foundCones.yellow.first.boundingRectangle.br()), yellow, 2);
    cv::rectangle(debugImage, adjustPosition(foundCones.yellow.second.boundingRectangle.tl()),
                  adjustPosition(foundCones.yellow.second.boundingRectangle.br()), yellow, 2);

    cv::String outputText = "group_04;" + std::to_string(cluon::time::toMicroseconds(timeStamp)) + ";" + std::to_string(steeringAngle);

    cv::putText(debugImage,outputText,cv::Point(10,image.rows - 10),cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(255,255,255));

    return debugImage;
}




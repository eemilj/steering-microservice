/*
 * Copyright (C) 2020  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Include the single-file, header-only middleware libcluon to create high-performance microservices
#include "cluon-complete.hpp"
// Include the OpenDLV Standard Message Set that contains messages that are usually exchanged for automotive or robotic applications 
#include "opendlv-standard-message-set.hpp"

// Include the GUI and image processing header files from OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageRecognitionController.h"
#include "SteeringAngleCalculator.h"
#include "ImageProcessor.h"
#include <chrono>

int32_t main(int32_t argc, char **argv) {
    int32_t retCode{1};
    // Parse the command line parameters as we require the user to specify some mandatory information on startup.
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if ( (0 == commandlineArguments.count("cid")) ||
         (0 == commandlineArguments.count("name")) ||
         (0 == commandlineArguments.count("width")) ||
         (0 == commandlineArguments.count("height")) ) {
        std::cerr << argv[0] << " attaches to a shared memory area containing an ARGB image." << std::endl;
        std::cerr << "Usage:   " << argv[0]
        << " --cid=<OD4 session> --name=<name of shared memory area> [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --name:   name of the shared memory area to attach" << std::endl;
        std::cerr << "         --width:  width of the frame" << std::endl;
        std::cerr << "         --height: height of the frame" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=253 --name=img --width=640 --height=480 --verbose" << std::endl;
    }
    else {
        // Extract the values from the command line parameters
        const std::string NAME{commandlineArguments["name"]};
        const uint32_t WIDTH{static_cast<uint32_t>(std::stoi(commandlineArguments["width"]))};
        const uint32_t HEIGHT{static_cast<uint32_t>(std::stoi(commandlineArguments["height"]))};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};

        // Attach to the shared memory.
        std::unique_ptr<cluon::SharedMemory> sharedMemory{new cluon::SharedMemory{NAME}};
        if (sharedMemory && sharedMemory->valid()) {
            std::clog << argv[0] << ": Attached to shared memory '"
            << sharedMemory->name() << " (" << sharedMemory->size() << " bytes)." << std::endl;

            // Interface to a running OpenDaVINCI session where network messages are exchanged.
            // The instance od4 allows you to send and receive messages.
            cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

            opendlv::proxy::GroundSteeringRequest gsr;
            std::mutex gsrMutex;
            auto onGroundSteeringRequest = [&gsr, &gsrMutex](cluon::data::Envelope &&env){
                // The envelope data structure provide further details, such as sampleTimePoint as shown in this test case:
                // https://github.com/chrberger/libcluon/blob/master/libcluon/testsuites/TestEnvelopeConverter.cpp#L31-L40
                std::lock_guard<std::mutex> lck(gsrMutex);
                gsr = cluon::extractMessage<opendlv::proxy::GroundSteeringRequest>(std::move(env));
                //std::cout << "lambda: groundSteering = " << gsr.groundSteering() << std::endl;
            };

            od4.dataTrigger(opendlv::proxy::GroundSteeringRequest::ID(), onGroundSteeringRequest);

            // Endless loop; end the program by pressing Ctrl-C.
            int frameCounter = 0;
            int realFrameCounter = 0;

            cv::namedWindow("Inspector", cv::WINDOW_AUTOSIZE);
            int minH{110};
            int maxH{130};
            cv::createTrackbar("Hue (min)", "Inspector", &minH, 255);
            cv::createTrackbar("Hue (max)", "Inspector", &maxH, 255);

            int minS{140};
            int maxS{255};
            cv::createTrackbar("Sat (min)", "Inspector", &minS, 255);
            cv::createTrackbar("Sat (max)", "Inspector", &maxS, 255);

            int minV{50};
            int maxV{100};
            cv::createTrackbar("Val (min)", "Inspector", &minV, 255);
            cv::createTrackbar("Val (max)", "Inspector", &maxV, 255);

            while (od4.isRunning()) {
                auto start = std::chrono::system_clock::now();
                // OpenCV data structure to hold an image.
                cv::Mat img, processedImg;

                // Wait for a notification of a new frame.
                sharedMemory->wait();

                // Lock the shared memory.
                sharedMemory->lock();
                {
                    // Copy the pixels from the shared memory into our own data structure.
                    cv::Mat wrapped(HEIGHT, WIDTH, CV_8UC4, sharedMemory->data());
                    img = wrapped.clone();
                }
                // TODO: Here, you can add some code to check the sampleTimePoint when the current frame was captured.
                sharedMemory->unlock();

                // TODO: Do something with the frame.
                cones foundCones = ImageRecognitionController::findConeCoordinates(img, cv::Scalar(minH, minS, minV), cv::Scalar(maxH, maxS, maxV));

                double steeringAngle = SteeringAngleCalculator::calculateSteeringAngle(foundCones);

                if(steeringAngle < 2){
                    frameCounter++;
                    std::cout << "Valid frames: " << frameCounter << std::endl;
                }
                realFrameCounter++;
                std::cout << "Valid frame percentage: " << double(frameCounter)/double(realFrameCounter)*100 << "%" << std::endl;

                cv::Mat counterTest;
                counterTest = img.clone();

                foundCones.yellow.first.y = foundCones.yellow.first.y+240;
                foundCones.yellow.second.y = foundCones.yellow.second.y+240;
                cv::circle(img, foundCones.yellow.first, 3, cv::Scalar(0,0,255), 2);
                cv::circle(img, foundCones.yellow.second, 3, cv::Scalar(0,0,255), 2);
                cv::line(img, foundCones.yellow.first, foundCones.yellow.second, cv::Scalar(0,0,255), 2);

                foundCones.blue.first.y = foundCones.blue.first.y+240;
                foundCones.blue.second.y = foundCones.blue.second.y+240;
                cv::circle(img, foundCones.blue.first, 3, cv::Scalar(0,0,255), 2);
                cv::circle(img, foundCones.blue.second, 3, cv::Scalar(0,0,255), 2);
                cv::line(img, foundCones.blue.first, foundCones.blue.second, cv::Scalar(0,0,255), 2);

                cv::putText(img, std::to_string(gsr.groundSteering()), cv::Point(0,50),
                            cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255,255,255), 1, false);
                // If you want to access the latest received ground steering, don't forget to lock the mutex:



                cv::Scalar blueLow = cv::Scalar(100, 100, 35); //100, 100, 45
                cv::Scalar blueHigh = cv::Scalar(150,255,255); //150, 255, 255
                cv::Scalar yellowLow = cv::Scalar(14, 100, 120);
                cv::Scalar yellowHigh = cv::Scalar(30,255,255);
                cv::Mat testDenoiseImage = ImageProcessor::processImage(img, cv::Scalar(minH, minS, minV), cv::Scalar(maxH, maxS, maxV));

                contours contours;
                contours = ImageRecognitionController::testingContourDrawing(counterTest);
                counterTest = testDenoiseImage.clone();
                cv::drawContours(counterTest, contours.blue, -1, cv::Scalar(255,255,255), 1);
                cv::drawContours(counterTest, contours.yellow, -1, cv::Scalar(255,255,255), 1);
                {
                    std::lock_guard<std::mutex> lck(gsrMutex);
                    //std::cout << "main: groundSteering = " << gsr.groundSteering() << std::endl;

                }

                // Display image on your screen.
                if (VERBOSE) {
                    cv::imshow("denoise", testDenoiseImage);
                    cv::imshow("img", img);
                    cv::imshow("contoursDraw", contourTest);
                    cv::waitKey(1);
                }
                auto stop = std::chrono::system_clock::now();
                auto end = stop - start;
                std::cout  << " Process time: "
                           << std::chrono::duration_cast<std::chrono::milliseconds>(end).count()
                           << " ms. " << std::endl;
            }
        }
        retCode = 0;
    }
    return retCode;
}


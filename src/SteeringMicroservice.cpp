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
#include "IOCSVProducer.h"

// Include the GUI and image processing header files from OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageRecognitionController.h"
#include "SteeringAngleCalculator.h"
#include <chrono>
#include "ConeVisualizer.h"

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

            opendlv::proxy::DistanceReading dsr;
            std::mutex dsrMutex;
            auto onDistanceReadingRequest = [&dsr, &dsrMutex](cluon::data::Envelope &&env){
                // The envelope data structure provide further details, such as sampleTimePoint as shown in this test case:
                // https://github.com/chrberger/libcluon/blob/master/libcluon/testsuites/TestEnvelopeConverter.cpp#L31-L40
                std::lock_guard<std::mutex> lck(dsrMutex);
                if(env.senderStamp() == 0) {
                    dsr = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(env));
                }
            };

            od4.dataTrigger(opendlv::proxy::GroundSteeringRequest::ID(), onGroundSteeringRequest);
            od4.dataTrigger(opendlv::proxy::DistanceReading::ID(), onDistanceReadingRequest);


            // Endless loop; end the program by pressing Ctrl-C.
            int frameCounter = 0;
            int realFrameCounter = 0;
            cluon::data::TimeStamp timeStamp;
            cv::Mat img, processedImg;
            double distanceReading, lastSteeringAngle = 0, upperBound = 0, lowerBound = 0;
            std::ofstream csvFile = IOCSVProducer::openCsvFile("csvOutput.csv");

            while (od4.isRunning()) {
                auto start = std::chrono::system_clock::now();
                // OpenCV data structure to hold an image.

                // Wait for a notification of a new frame.
                sharedMemory->wait();

                // Lock the shared memory.
                sharedMemory->lock();
                {
                    timeStamp = sharedMemory->getTimeStamp().second;
                    // Copy the pixels from the shared memory into our own data structure.
                    cv::Mat wrapped(HEIGHT, WIDTH, CV_8UC4, sharedMemory->data());
                    img = wrapped.clone();
                    std::lock_guard<std::mutex> lck(dsrMutex);
                    distanceReading = dsr.distance();
                }
                sharedMemory->unlock();
                cones foundCones = ImageRecognitionController::findConeCoordinates(img);

                double steeringAngle = SteeringAngleCalculator::outputSteeringAngle(lastSteeringAngle, foundCones, distanceReading);
                lastSteeringAngle = steeringAngle;
                std::cout << "Our gsr: " << steeringAngle << std::endl;

//                if(steeringAngle != 0 && steeringAngle < 361){
//                    frameCounter++;
//                    //std::cout << "Valid frames: " << frameCounter << std::endl;
//                }
                realFrameCounter++;
                //std::cout << "Valid frame percentage: " << double(frameCounter)/double(realFrameCounter)*100 << "%" << std::endl;
                cv::Mat contoursImage;
                contoursImage = ConeVisualizer::drawContoursImage(img);
                {
                    std::lock_guard<std::mutex> lck(gsrMutex);
                    std::cout << "main: groundSteering = " << gsr.groundSteering() << std::endl;
                    upperBound = gsr.groundSteering() + 0.5*gsr.groundSteering();
                    lowerBound = gsr.groundSteering() - 0.5*gsr.groundSteering();

                    if(gsr.groundSteering() > 0 && (steeringAngle >= lowerBound) && (steeringAngle <= upperBound)){
                        frameCounter++;
                    } else if (gsr.groundSteering() < 0 && (steeringAngle <= lowerBound) && (steeringAngle >= upperBound)){
                        frameCounter++;
                    } else if (fabs(gsr.groundSteering()) == 0.0){
                        if (steeringAngle <= 0.05 && steeringAngle >= -0.05) {
                            frameCounter++;
                        }
                    }

                    IOCSVProducer::exportDataToCsv(timeStamp, gsr.groundSteering(), steeringAngle, csvFile);
                }
                std::cout << "Valid frame percentage: " << double(frameCounter)/double(realFrameCounter)*100 << "%" << std::endl;

                // Display image on your screen.
                if (VERBOSE) {
                    cv::imshow("img", img);
                    cv::imshow("contours", contoursImage);
                    cv::waitKey(1);
                }
                auto stop = std::chrono::system_clock::now();
                auto end = stop - start;
                /*std::cout  << " Process time: "
                           << std::chrono::duration_cast<std::chrono::milliseconds>(end).count()
                           << " ms. " << std::endl;*/
            }
            IOCSVProducer::closeCsvFile(csvFile);
        }
        retCode = 0;
    }
    return retCode;
}


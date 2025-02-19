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
#include "IOHandler.hpp"

// Include the GUI and image processing header files from OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageRecognitionController.hpp"
#include "SteeringAngleCalculator.hpp"
#include "ConeVisualizer.hpp"

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
            cluon::data::TimeStamp timeStamp;
            cv::Mat img, processedImg;
            double distanceReading, lastSteeringAngle = 0;
            std::fstream csvFile = IOHandler::openCsvFile("/csv_files/csvOutput.csv");

            while (od4.isRunning()) {
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

                {
                    IOHandler::writeToCsv(timeStamp, gsr.groundSteering(), steeringAngle, csvFile);
                    IOHandler::printToTerminal(timeStamp, steeringAngle);
                }

                // Display image on your screen.
                if (VERBOSE) {
                    cv::Mat rectangleImage;
                    rectangleImage = ConeVisualizer::createDebugImage(img, foundCones, timeStamp, steeringAngle);
                    cv::imshow("debug", rectangleImage);
                    cv::waitKey(1);
                }
            }
            IOHandler::closeCsvFile(csvFile);
        }
        retCode = 0;
    }
    return retCode;
}


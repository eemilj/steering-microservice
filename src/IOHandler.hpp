#ifndef IOCSVPRODUCER_H
#define IOCSVPRODUCER_H

#include <fstream>
#include <iostream>
#include "cluon-complete.hpp"
#include <cstdio>

class IOHandler {
public:
    static void writeToCsv(const cluon::data::TimeStamp &timeStamp, const double &actualGroundSteering, const double &calculatedSteeringAngle, std::fstream &csvFile);
    static std::fstream openCsvFile(const char* fileName);
    static bool closeCsvFile(std::fstream &csvFile);
    static bool fileExists(const std::string& filename);
    static void printToTerminal(const cluon::data::TimeStamp &timeStamp, const double &calculatedSteeringAngle);
};


#endif

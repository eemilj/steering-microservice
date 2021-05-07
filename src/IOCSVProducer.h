#ifndef IOCSVPRODUCER_H
#define IOCSVPRODUCER_H

#include <fstream>
#include <iostream>
#include "cluon-complete.hpp"
#include <cstdio>

class IOCSVProducer {
public:
    static void exportDataToCsv(cluon::data::TimeStamp timeStamp, double actualGroundSteering, double calculatedSteeringAngle, std::ofstream &csvFile);
    static std::ofstream openCsvFile(const char* fileName);
    static void closeCsvFile(std::ofstream &csvFile);

private:
    static bool fileExists(const std::string& filename);
};


#endif

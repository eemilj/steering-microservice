#ifndef IOCSVPRODUCER_H
#define IOCSVPRODUCER_H

#include <fstream>
#include <iostream>
#include "cluon-complete.hpp"

class IOCSVProducer {
public:
    static void exportDataToCsv(cluon::data::TimeStamp timeStamp, double actualGroundSteering, double calculatedSteeringAngle, std::ofstream &csvFile);
    static std::ofstream openCsvFile();
    static void closeCsvFile(std::ofstream &csvFile);
};


#endif

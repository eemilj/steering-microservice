#include "IOCSVProducer.h"

void IOCSVProducer::exportDataToCsv(cluon::data::TimeStamp timeStamp, double actualGroundSteering, double calculatedSteeringAngle, std::ofstream &csvFile){
    const char columnSeparator = ',';
    uint64_t time;
    if(csvFile.is_open() && !csvFile.fail()) {
        time = (uint64_t) timeStamp.seconds() * 1000000 + timeStamp.microseconds();
        csvFile << time << columnSeparator
                << actualGroundSteering << columnSeparator
                << calculatedSteeringAngle << std::endl;
    }else{
        std::cerr << "Oops, error printing to file" << std::endl;
    }
}

std::ofstream IOCSVProducer::openCsvFile(){
    const char columnSeparator = ',';
    std::ofstream csvFile;
    csvFile.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
    try {
        csvFile.open ("csvOutput.csv", std::ios::app);
        csvFile << "Timestamp" << columnSeparator << "ActualGroundSteering" << columnSeparator << "CalculatedSteeringAngle" << std::endl;
    }catch (std::ofstream::failure& e) {
        std::cerr << "Exception opening file" << e.code() << " & " << e.what() << std::endl;
    }
    return csvFile;
}

void IOCSVProducer::closeCsvFile(std::ofstream &csvFile){
    try {
        csvFile.close();
    }catch (std::ofstream::failure& e) {
        std::cerr << "Exception closing file: " << e.code() << " & " << e.what() << std::endl;
    }
}
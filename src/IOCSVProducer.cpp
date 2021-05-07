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

std::ofstream IOCSVProducer::openCsvFile(const char* fileName){
    const char columnSeparator = ',';
    std::ofstream csvFile;
    csvFile.exceptions ( std::ofstream::failbit | std::ofstream::badbit );
    try {
        if (fileExists(fileName)) {
            remove(fileName);
        }
        csvFile.open (fileName, std::ios::app);
        csvFile << "Timestamp" << columnSeparator << "ActualGroundSteering" << columnSeparator << "CalculatedSteeringAngle" << std::endl;
    }catch (std::ofstream::failure& e) {
        std::cerr << "Exception opening file: " << e.code() << " & " << e.what() << std::endl;
    }
    return csvFile;
}

// https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
bool IOCSVProducer::fileExists(const std::string& filename) {
    struct stat buf = {};
    if (stat(filename.c_str(), &buf) != -1) {
        return true;
    }
    return false;
}

void IOCSVProducer::closeCsvFile(std::ofstream &csvFile){
    try {
        csvFile.close();
    }catch (std::ofstream::failure& e) {
        std::cerr << "Exception closing file: " << e.code() << " & " << e.what() << std::endl;
    }
}
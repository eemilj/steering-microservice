#include "IOHandler.h"

void IOHandler::writeToCsv(cluon::data::TimeStamp timeStamp, double actualGroundSteering, double calculatedSteeringAngle, std::fstream &csvFile){
    const char columnSeparator = ',';
    uint64_t time;
    if(csvFile.is_open() && !csvFile.fail()) {
        time = cluon::time::toMicroseconds(timeStamp);
        csvFile << time << columnSeparator
                << actualGroundSteering << columnSeparator
                << calculatedSteeringAngle << std::endl;
    }else{
        std::cerr << "Oops, error printing to file" << std::endl;
    }
}

std::fstream IOHandler::openCsvFile(const char* fileName){
    const char columnSeparator = ',';
    std::fstream csvFile;
    csvFile.exceptions ( std::fstream::failbit | std::fstream::badbit );
    try {
        if (fileExists(fileName)) {
            remove(fileName);
        }
        csvFile.open (fileName, std::ios::app);
        csvFile << "Timestamp" << columnSeparator << "ActualGroundSteering" << columnSeparator << "CalculatedSteeringAngle" << std::endl;
    }catch (std::fstream::failure& e) {
        std::cerr << "Exception opening file: " << e.code() << " & " << e.what() << std::endl;
    }
    return csvFile;
}

// https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
bool IOHandler::fileExists(const std::string& filename) {
    struct stat buf = {};
    if (stat(filename.c_str(), &buf) != -1) {
        return true;
    }
    return false;
}

bool IOHandler::closeCsvFile(std::fstream &csvFile){
    try {
        csvFile.close();
    }catch (std::fstream::failure& e) {
        std::cerr << "Exception closing file: " << e.code() << " & " << e.what() << std::endl;
        return false;
    }
    return true;
}

void IOHandler::printToTerminal(cluon::data::TimeStamp timeStamp, double calculatedSteeringAngle) {
    uint64_t time;
    time = cluon::time::toMicroseconds(timeStamp);
    std::cout << "group_04;" << time << ";" << calculatedSteeringAngle << std::endl;
}


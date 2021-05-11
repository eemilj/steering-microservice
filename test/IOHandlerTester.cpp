#include "catch.hpp"
#include "IOHandler.h"

TEST_CASE("Test to create a file") {
    std::fstream OStream = IOHandler::openCsvFile("testFile");
    IOHandler::closeCsvFile(OStream);
    std::fstream stream = std::fstream("testFile");
    std::string line, expectedLine;
    expectedLine = "Timestamp,ActualGroundSteering,CalculatedSteeringAngle";
    std::getline(stream,line);
    REQUIRE(IOHandler::fileExists("testFile"));
    REQUIRE(line == expectedLine);
    IOHandler::closeCsvFile(stream);
}

TEST_CASE("Test close stream") {
    std::fstream stream = std::fstream("testFile");
    REQUIRE(IOHandler::closeCsvFile(stream));
    REQUIRE_FALSE(stream.is_open());
}

TEST_CASE("Test to write to a file") {
    std::fstream OStream = IOHandler::openCsvFile("testFile");
    cluon::data::TimeStamp timeStamp = cluon::data::TimeStamp();
    IOHandler::writeToCsv(timeStamp,13.0, 10.1,OStream );
    IOHandler::closeCsvFile(OStream);
    std::fstream stream = std::fstream("testFile");
    std::string line, expectedLine;
    expectedLine = "0,13,10.1";
    std::getline(stream,line); // read title line
    std::getline(stream,line); // read second line added by writeToCsv function
    REQUIRE(line == expectedLine);
    REQUIRE(IOHandler::fileExists("testFile"));
    IOHandler::closeCsvFile(stream);
}

TEST_CASE("Test to verify that a file exist/does not exist") {
    REQUIRE(IOHandler::fileExists("testFile"));
    REQUIRE_FALSE(IOHandler::fileExists("notAFile"));
}
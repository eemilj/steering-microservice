#include "catch.hpp"
#include "IOCSVProducer.h"

TEST_CASE("Test to create a file") {
    std::fstream OStream = IOCSVProducer::openCsvFile("testFile");
    IOCSVProducer::closeCsvFile(OStream);
    std::fstream stream = std::fstream("testFile");
    std::string line, expectedLine;
    expectedLine = "Timestamp,ActualGroundSteering,CalculatedSteeringAngle";
    std::getline(stream,line);
    REQUIRE(IOCSVProducer::fileExists("testFile"));
    REQUIRE(line == expectedLine);
    IOCSVProducer::closeCsvFile(stream);
}

TEST_CASE("Test close stream") {
    std::fstream stream = std::fstream("testFile");
    REQUIRE(IOCSVProducer::closeCsvFile(stream));
    REQUIRE_FALSE(stream.is_open());
}

TEST_CASE("Test to write to a file") {
    std::fstream OStream = IOCSVProducer::openCsvFile("testFile");
    cluon::data::TimeStamp timeStamp = cluon::data::TimeStamp();
    IOCSVProducer::writeToCsv(timeStamp,13.0, 10.1,OStream );
    IOCSVProducer::closeCsvFile(OStream);
    std::fstream stream = std::fstream("testFile");
    std::string line, expectedLine;
    expectedLine = "0,13,10.1";
    std::getline(stream,line); // read title line
    std::getline(stream,line); // read second line added by writeToCsv function
    REQUIRE(line == expectedLine);
    REQUIRE(IOCSVProducer::fileExists("testFile"));
    IOCSVProducer::closeCsvFile(stream);
}

TEST_CASE("Test to verify that a file exist/does not exist") {
    REQUIRE(IOCSVProducer::fileExists("testFile"));
    REQUIRE_FALSE(IOCSVProducer::fileExists("notAFile"));
}
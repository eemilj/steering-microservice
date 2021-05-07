#include "catch.hpp"
#include "IOCSVProducer.h"

TEST_CASE("Test to create a file") {
    IOCSVProducer::openCsvFile("testFile");
    REQUIRE(IOCSVProducer::fileExists("testFile"));
}
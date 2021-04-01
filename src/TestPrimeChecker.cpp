#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PrimeChecker.hpp"

TEST_CASE("Test PrimeChecker 1.") {
    PrimeChecker primeChecker;
    REQUIRE(primeChecker.isPrime(5));
}

TEST_CASE("Test PrimeChecker 2.") {
    PrimeChecker primeChecker;
    REQUIRE(!primeChecker.isPrime(2));
}

TEST_CASE("Test PrimeChecker 3.") {
    PrimeChecker primeChecker;
    REQUIRE(primeChecker.isPrime(3));
}

TEST_CASE("Test PrimeChecker 4.") {
    PrimeChecker primeChecker;
    REQUIRE_FALSE(primeChecker.isPrime(9));
}

TEST_CASE("Test PrimeChecker 5.") {
    PrimeChecker primeChecker;
    REQUIRE_FALSE(primeChecker.isPrime(7));
}
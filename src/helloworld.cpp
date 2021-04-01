//Eemil Was here
#include <iostream>
#include "PrimeChecker.hpp"
//Alexander Hultén
//Chrysostomos Tsagkidis
int main(int argc, char** argv) {
    if (argc == 2) {
        int number = std::stoi(argv[1]);
        PrimeChecker primeChecker;
        std::cout << "Group 4;" << number << " is a prime? " << primeChecker.isPrime(number) << std:: endl;
    }
    return 0;
}

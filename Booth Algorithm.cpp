#include <iostream>
#include <vector> 

void obtainData(int &a, int &b) {
    std::cout << "Multiplicand value: ";
    std::cin >> a;
    std::cout << "Multiplier value: ";
    std::cin >> b;
}

int nLength(int multiplicand, int multiplier, int& nBits) {
    int nMultiplicand, nMultiplier;
    if (multiplicand >= -8 && multiplicand <= 7) {
        nMultiplicand = 4;
    }
    else if (multiplicand >= -128 && multiplicand <= 127) {
        nMultiplicand = 8;
    }
    else {
        nMultiplicand = 16;
    }
    if (multiplier >= -8 && multiplier <= 7) {
        nMultiplier = 4;
    }
    else if (multiplier >= -128 && multiplier <= 127) {
        nMultiplier = 8;
    }
    else {
        nMultiplier = 16;
    }
    if (nMultiplier > nMultiplicand) {
        nBits = nMultiplier;
    }
    else {
        nBits = nMultiplicand;
    }
    return nBits;
}

std::vector<bool> binaryNumber(int number, int nBits) {
    std::vector<bool> binaryNumber;
    while (number != 0) {
        binaryNumber.push_back(number % 2);
        number /= 2;
    }
    return binaryNumber;
}

int main() {
    int multiplicand = 0, multiplier = 0, nBits;
    obtainData(multiplicand, multiplier);
    nLength(multiplicand, multiplier, nBits);
    std::vector<bool> binaryMultiplicand = binaryNumber(multiplicand, nBits);
    
    for (int i = 0; i < nBits; i++) {
        std::cout << binaryMultiplicand[i];
    }

}
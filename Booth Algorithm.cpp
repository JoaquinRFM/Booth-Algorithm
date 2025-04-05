#include <iostream>
#include <vector> 

void obtainData(int& a, int& b) {
    do {
        std::cout << "Multiplicand value: ";
        std::cin >> a;
        std::cout << "Multiplier value: ";
        std::cin >> b;
        if (a > 32767 || a < -32768 || b > 32767 || b < -32768) {
            std::cout << "Out of limits, select another number" << std::endl;
        }
    } while (a > 32767 || a < -32768 || b > 32767 || b < -32768);
}

int nLength(int multiplicand, int multiplier, int& nBits) {
    int nMultiplicand = 16, nMultiplier = 16;
    if (multiplicand >= -8 && multiplicand <= 7) {
        nMultiplicand = 4;
    }
    else if (multiplicand >= -128 && multiplicand <= 127) {
        nMultiplicand = 8;
    }
    else if (multiplicand >= -32768 && multiplicand <= 32767) {
        nMultiplicand = 16;
    }
    if (multiplier >= -8 && multiplier <= 7) {
        nMultiplier = 4;
    }
    else if (multiplier >= -128 && multiplier <= 127) {
        nMultiplier = 8;
    }
    else if (multiplier >= -32768 && multiplier <= 32767) {
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
    if (number == 0) {
        for (int i = 0; i < nBits; i++) {
            binaryNumber.push_back(0);
        }
        return binaryNumber;
    }
    int absoluteValue;
    if (number < 0) {
        absoluteValue = -number;
    }
    else {
        absoluteValue = number;
    }
    while (absoluteValue > 0) {
        binaryNumber.insert(binaryNumber.begin(), (absoluteValue % 2) != 0);
        absoluteValue /= 2;
    }
    while (binaryNumber.size() < nBits) {
        binaryNumber.insert(binaryNumber.begin(), 0);
    }
    if (number < 0) {
        for (int i = 0; i < binaryNumber.size(); i++) {
            if (binaryNumber[i]) {
                binaryNumber[i] = 0;
            }
            else {
                binaryNumber[i] = 1;
            }
        }
        bool carry = 1;
        for (int i = binaryNumber.size() - 1; carry && i >= 0; i--) {
            if (binaryNumber[i] == 0) {
                binaryNumber[i] = 1;
                carry = 0;
            }
            else {
                binaryNumber[i] = 0;
            }
        }
    }
    return binaryNumber;
}

void printBinary(std::vector<bool>& binaryNumber) {
    for (int i = 0; i < binaryNumber.size(); i++) {
        if (binaryNumber[i] == 1) {
            std::cout << '1';
        }
        else {
            std::cout << '0';
        }
    }
}

int main() {
    int multiplicand = 0, multiplier = 0, nBits;
    obtainData(multiplicand, multiplier);
    nLength(multiplicand, multiplier, nBits);
    std::vector<bool> binaryMultiplicand = binaryNumber(multiplicand, nBits);
    std::vector<bool> binaryMultiplier = binaryNumber(multiplier, nBits);

    printBinary(binaryMultiplicand);
    std::cout << std::endl;
    printBinary(binaryMultiplier);
}
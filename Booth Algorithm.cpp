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

std::vector<bool> twoComplement(std::vector<bool> binaryNumber) {
    for (int i = 0; i < binaryNumber.size(); i++) {
        if (binaryNumber[i] == 1) {
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
    return binaryNumber;
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
        binaryNumber = twoComplement(binaryNumber);
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

std::vector<bool> binarySum(std::vector<bool> A, std::vector<bool> M) {
    std::vector<bool> tempA = A;
    bool C = 0;
    for (int i = A.size() - 1; i >= 0; i--) {
        bool S = (A[i] ^ M[i]) ^ C;
        C = (A[i] && M[i]) || (M[i] && C) || (A[i] && C);
        tempA[i] = S;
    }
    return tempA;
}

void aritmeticShiftRight(std::vector<bool>& A, std::vector<bool>& Q, bool& Q1) {
    Q1 = Q[Q.size() - 1];
    for (int i = Q.size() - 1; i > 0; i--) {
        Q[i] = Q[i - 1];
    }
    Q[0] = A[A.size() - 1];
    bool MSB_A = A[0];
    for (int i = A.size() - 1; i > 0; i--) {
        A[i] = A[i - 1];
    }
    A[0] = MSB_A;
}

void boothAlgorith(std::vector<bool>& A, bool& Q1, std::vector<bool> M, std::vector<bool>& Q, int n) {
    while (n != 0) {
        if (Q[Q.size() - 1] == 1 && Q1 == 0) {
            std::vector<bool> negativeM = M;
            negativeM = twoComplement(negativeM);
            A = binarySum(A, negativeM);
        }
        else if (Q[Q.size() - 1] == 0 && Q1 == 1) {
            A = binarySum(A, M);
        }
        aritmeticShiftRight(A, Q, Q1);
        n--;
    }
}

void binaryMerge(std::vector<bool> A, std::vector<bool> Q, std::vector<bool>& resultBinary) {
    for (int i = 0; i < A.size(); i++) {
        resultBinary[i] = A[i];
    }
    for (int i = 0; i < Q.size(); i++) {
        resultBinary[i + A.size()] = Q[i];
    }
}

int binaryToInt(const std::vector<bool>& binary) {
    int result = 0;
    int n = binary.size();
    if (binary[0]) {
        result = -1;
        for (int i = 1; i < n; ++i) {
            result *= 2;
            if (binary[i]) {
                result += 1;
            }
        }
        result -= 1;
    }
    else {
        for (int i = 1; i < n; ++i) {
            result *= 2;
            if (binary[i]) {
                result += 1;
            }
        }
    }

    return result;
}

int main() {
    int multiplicand = 0, multiplier = 0, A = 0, nBits, R = 0, resultInt;
    bool Q1 = 0;
    std::cout << "-------------------------------------------------------------" << std::endl;
    obtainData(multiplicand, multiplier);
    nLength(multiplicand, multiplier, nBits);
    std::vector<bool> binaryMultiplicand = binaryNumber(multiplicand, nBits);
    std::vector<bool> binaryMultiplier = binaryNumber(multiplier, nBits);
    std::vector<bool> binaryA = binaryNumber(A, nBits);
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Multiplicand: " << multiplicand << "  Binary value: ";
    printBinary(binaryMultiplicand);
    std::cout << std::endl;
    std::cout << "Multiplier: " << multiplier << "  Binary value: ";
    printBinary(binaryMultiplier);
    std::cout << std::endl << "-------------------------------------------------------------" << std::endl;
    boothAlgorith(binaryA, Q1, binaryMultiplicand, binaryMultiplier, nBits);
    std::vector<bool> resultBinary = binaryNumber(0, (nBits * 2));
    binaryMerge(binaryA, binaryMultiplier, resultBinary);
    resultInt = binaryToInt(resultBinary);
    std::cout << "Result: " << resultInt << "  Binary value: ";
    printBinary(resultBinary);
    std::cout << std::endl << "-------------------------------------------------------------" << std::endl;
}
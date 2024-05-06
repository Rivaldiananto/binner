#include <iostream>
#include <bitset>
#include <sstream>
#include <string>
#include <random>
#include <ctime>

// Fungsi untuk mengonversi string biner ke hexadecimal
std::string binToHex(const std::string &binStr) {
    std::stringstream ss;
    unsigned long long num = std::bitset<66>(binStr).to_ullong();
    ss << std::hex << std::uppercase << num;
    return ss.str();
}

// Fungsi untuk menghasilkan string biner acak 6-bit
std::string generateRandomBinaryPattern() {
    static std::mt19937 rng(time(nullptr)); // generator nomor acak berdasarkan waktu
    std::uniform_int_distribution<int> dist(0, 63); // distribusi untuk angka 0-63
    int number = dist(rng);
    std::bitset<6> bset(number);
    return bset.to_string();
}

int main() {
    std::string combinedBinPattern;

    // Menghasilkan dan menggabungkan 11 pola biner 6-bit
    for (int i = 0; i < 11; ++i) {
        combinedBinPattern += generateRandomBinaryPattern();
    }

    // Mengonversi ke hexadecimal
    std::string hexOutput = binToHex(combinedBinPattern);
    std::cout << "String biner yang dihasilkan: " << combinedBinPattern << std::endl;
    std::cout << "Hasil konversi ke hexadecimal: " << hexOutput << std::endl;

    return 0;
}

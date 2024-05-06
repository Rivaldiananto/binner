#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <iomanip>

// Fungsi untuk mengonversi string biner ke hexadecimal
std::string binToHex(const std::string& binStr) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < binStr.size(); i += 4) {
        int nibble = std::stoi(binStr.substr(i, 4), nullptr, 2);
        ss << nibble;
    }
    return ss.str();
}

// Fungsi untuk menghasilkan semua pola biner 6-bit dari 0 hingga 63
std::vector<std::string> generateAllBinaryPatterns() {
    std::vector<std::string> patterns;
    for (int i = 0; i < 64; ++i) {
        std::bitset<6> bset(i);
        patterns.push_back(bset.to_string());
    }
    return patterns;
}

int main() {
    auto patterns = generateAllBinaryPatterns();
    std::string combinedBinPattern;

    // Membuat generator nomor acak
    std::mt19937 rng(time(nullptr));
    std::shuffle(patterns.begin(), patterns.end(), rng);

    // Memilih 11 pola acak
    for (int i = 0; i < 11; ++i) {
        combinedBinPattern += patterns[i];
    }

    // Mengonversi ke hexadecimal
    std::string hexOutput = binToHex(combinedBinPattern);
    std::cout << "String biner yang dihasilkan: " << combinedBinPattern << std::endl;
    std::cout << "Hasil konversi ke hexadecimal: " << hexOutput << std::endl;

    return 0;
}

#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <cstdlib>  // Untuk std::atoi

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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number of patterns>" << std::endl;
        return 1;
    }

    int numPatterns = std::atoi(argv[1]);
    if (numPatterns <= 0 || numPatterns > 64) {
        std::cerr << "Invalid number of patterns. Please specify a number between 1 and 64." << std::endl;
        return 1;
    }

    auto patterns = generateAllBinaryPatterns();
    std::string combinedBinPattern;

    // Membuat generator nomor acak
    std::mt19937 rng(time(nullptr));
    std::shuffle(patterns.begin(), patterns.end(), rng);

    // Memilih n pola acak, sesuai dengan input pengguna
    for (int i = 0; i < numPatterns; ++i) {
        combinedBinPattern += patterns[i];
    }

    // Mengonversi ke hexadecimal
    std::string hexOutput = binToHex(combinedBinPattern);
    std::cout << "String biner yang dihasilkan: " << combinedBinPattern << std::endl;
    std::cout << "Hasil konversi ke hexadecimal: " << hexOutput << std::endl;

    return 0;
}

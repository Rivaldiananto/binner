#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <chrono>  // For measuring time
#include <cstdlib>

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
    std::vector<bool> v(64, false);
    std::fill(v.begin(), v.begin() + numPatterns, true);
    std::sort(patterns.begin(), patterns.end());

    // Menggunakan chrono untuk menghitung waktu
    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;

    do {
        std::string combinedBinPattern;
        for (int i = 0; i < 64; ++i) {
            if (v[i]) {
                combinedBinPattern += patterns[i];
            }
        }
        std::string hexOutput = binToHex(combinedBinPattern);
        count++;
    } while (std::prev_permutation(v.begin(), v.end()));

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Binner completed. Processed " << count << " combinations.\n";
    std::cout << "Hex Output: " << binToHex(patterns.back()) << "\n";
    std::cout << "Time elapsed (seconds): " << elapsed.count() << " s\n";
    std::cout << "Combinations per second: " << count / elapsed.count() << "\n";

    return 0;
}

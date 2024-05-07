#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <chrono>
#include <gmpxx.h>
#include <omp.h>
#include <fstream>

std::string binToHex(const std::string& binStr) {
    mpz_class mpz_bin(binStr, 2);  // Setiap thread memiliki instance mpz_class-nya sendiri
    std::stringstream ss;
    ss << std::hex << mpz_bin;
    return ss.str();
}

std::vector<std::string> generateAllBinaryPatterns() {
    std::vector<std::string> patterns;
    for (int i = 0; i < 64; ++i) {
        std::bitset<6> bset(i);
        patterns.push_back(bset.to_string());
    }
    return patterns;
}

int main(int argc, char* argv[]) {
    auto patterns = generateAllBinaryPatterns();
    std::vector<std::string> hexResults(patterns.size());

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (size_t idx = 0; idx < patterns.size(); ++idx) {
        hexResults[idx] = binToHex(patterns[idx]);  // Memaralelkan konversi setiap pola
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::ofstream outFile("output_hex_results.txt");
    for (const auto& hex : hexResults) {
        outFile << hex << std::endl;
    }
    outFile.close();

    std::cout << "[+] Total patterns converted: " << hexResults.size() << " in " << elapsed.count() << " seconds." << std::endl;
    std::cout << "[+] Results saved to 'output_hex_results.txt'." << std::endl;

    return 0;
}

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
#include <fstream> // Include untuk output file

std::string binToHex(const std::string& binStr) {
    mpz_class mpz_bin(binStr, 2);
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

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::string> hexResults;

    #pragma omp parallel
    {
        std::vector<std::string> localHexResults;

        #pragma omp for nowait
        for (size_t idx = 0; idx < patterns.size(); ++idx) {
            if (v[idx]) {
                localHexResults.push_back(binToHex(patterns[idx]));
            }
        }

        #pragma omp critical
        {
            hexResults.insert(hexResults.end(), localHexResults.begin(), localHexResults.end());
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Menyimpan hasil ke dalam file
    std::ofstream outFile("output_hex_results.txt");
    for (const auto& hex : hexResults) {
        outFile << hex << std::endl;
    }
    outFile.close(); // Menutup file

    std::cout << "[+] Total patterns converted: " << hexResults.size() << " in " << elapsed.count() << " seconds." << std::endl;
    std::cout << "[+] Results saved to 'output_hex_results.txt'." << std::endl;

    return 0;
}

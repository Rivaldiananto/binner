#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <chrono>
#include <gmpxx.h>
#include <fstream>
#include <omp.h>

std::string binToHex(const std::string& binStr) {
    mpz_class mpz_bin(binStr, 2);
    std::stringstream ss;
    ss << std::hex << mpz_bin;
    return ss.str();
}

std::vector<std::string> generateAllBinaryPatterns() {
    std::vector<std::string> patterns(64);
    #pragma omp parallel for
    for (int i = 0; i < 64; ++i) {
        std::bitset<6> bset(i);
        patterns[i] = bset.to_string();
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

    std::ofstream outfile("output.txt");

    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;
    std::cout << "[+] Binner:\n[+] Hex:\n";

    #pragma omp parallel
    {
        std::vector<std::string> local_outputs;
        #pragma omp for nowait
        do {
            std::string combinedBinPattern;
            for (int i = 0; i < 64; ++i) {
                if (v[i]) {
                    combinedBinPattern += patterns[i];
                }
            }
            local_outputs.push_back(binToHex(combinedBinPattern));
        } while (std::prev_permutation(v.begin(), v.end()));

        #pragma omp critical
        {
            for (const auto& hexOutput : local_outputs) {
                outfile << hexOutput << std::endl;
                count++;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "[+] Finished in: " << elapsed.count() << " seconds" << std::endl;

    outfile.close();
    return 0;
}

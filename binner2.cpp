#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <chrono>
#include <gmpxx.h>
#include <omp.h> // Include untuk OpenMP

// Fungsi untuk mengonversi string biner ke hexadecimal
std::string binToHex(const std::string& binStr) {
    mpz_class mpz_bin(binStr, 2);  // Inisialisasi mpz_class dengan string biner
    std::stringstream ss;
    ss << std::hex << mpz_bin;  // Mengonversi bilangan biner ke heksadesimal
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

    auto start = std::chrono::high_resolution_clock::now();
    auto last_update = start;
    int count = 0;

    std::cout << "[+] Binner:\n[+] Hex:\n";  // Print header only once

    // Paralelisasi proses generasi dan konversi pattern
    #pragma omp parallel
    {
        std::vector<std::string> localPatterns;  // Vektor lokal untuk setiap thread

        #pragma omp for schedule(dynamic) nowait  // Distribusi beban kerja secara dinamis
        for (size_t idx = 0; idx < patterns.size(); ++idx) {
            if (v[idx]) {
                localPatterns.push_back(patterns[idx]);
            }
        }

        #pragma omp critical
        {
            for (const auto& pattern : localPatterns) {
                std::string hexOutput = binToHex(pattern);
                count++;
            }
        }
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - last_update;
    std::printf("[+] Total patterns converted: %d in %.2f seconds.\n", count, elapsed.count());

    return 0;
}

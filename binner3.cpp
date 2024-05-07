#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <chrono>
#include <gmpxx.h>
#include <fstream> // Include library untuk file handling

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

    std::ofstream outfile("output.txt"); // Membuka file untuk menulis hasil

    auto start = std::chrono::high_resolution_clock::now();
    auto last_update = start;
    int count = 0;

    std::cout << "[+] Binner:\n[+] Hex:\n";  // Print header only once

    do {
        std::string combinedBinPattern;
        for (int i = 0; i < 64; ++i) {
            if (v[i]) {
                combinedBinPattern += patterns[i];
            }
        }
        std::string hexOutput = binToHex(combinedBinPattern);
        outfile << hexOutput << std::endl; // Menulis ke file
        count++;

        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - last_update;

        if (elapsed.count() >= 1.0) { // Update the output every second
            std::printf("\r[+] Jumlah output/detik: %d kombinasi/detik", count);  // Update on the same line
            std::fflush(stdout);  // Flush the output buffer
            last_update = now;
            count = 0;  // Reset count after updating
        }
    } while (std::prev_permutation(v.begin(), v.end()));

    std::cout << std::endl;  // Print a newline at the end of the program
    outfile.close(); // Tutup file setelah semua operasi selesai

    return 0;
}

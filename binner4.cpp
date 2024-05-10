#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <gmp.h>
#include <chrono>

// Fungsi untuk mengonversi integer ke string biner 6-bit
std::string intToBinary6(int num) {
    std::bitset<6> bin(num);
    return bin.to_string();
}

// Fungsi untuk menghasilkan semua kombinasi biner 6-bit
std::vector<std::string> generateAllCombinations() {
    std::vector<std::string> allCombinations;
    for (int i = 0; i < 64; ++i) {
        allCombinations.push_back(intToBinary6(i));
    }
    return allCombinations;
}

int main() {
    const int numPatterns = 11; // Jumlah pola yang ingin digunakan
    std::vector<std::string> allCombinations = generateAllCombinations();

    mpz_t totalCombinations;
    mpz_init(totalCombinations);
    mpz_ui_pow_ui(totalCombinations, 64, numPatterns);  // 64^numPatterns

    gmp_printf("Total kombinasi yang mungkin: %Zd\n", totalCombinations);

    // Start time measurement
    auto start = std::chrono::steady_clock::now();

    mpz_t i;
    mpz_init_set_ui(i, 0);
    unsigned long count = 0;
    while(mpz_cmp(i, totalCombinations) < 0) {  // Iterate through all combinations
        unsigned long long combination = mpz_get_ui(i);
        std::string result;
        for (int j = 0; j < numPatterns; ++j) {
            int index = combination % 64;
            result += allCombinations[index];
            combination /= 64;
        }
        // Optionally process the result here
        mpz_add_ui(i, i, 1);
        count++;
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    double seconds = elapsed_seconds.count();
    double rate = count / seconds;

    std::cout << "Total waktu eksekusi: " << seconds << " detik\n";
    std::cout << "Operasi per detik: " << rate << std::endl;

    mpz_clear(totalCombinations);
    mpz_clear(i);
    return 0;
}

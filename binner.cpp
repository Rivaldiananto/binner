#include <iostream>
#include <bitset>
#include <sstream>
#include <string>

// Fungsi untuk mengonversi string biner ke hexadecimal
std::string binToHex(const std::string &binStr) {
    std::stringstream ss;
    unsigned long long num = std::bitset<66>(binStr).to_ullong();
    ss << std::hex << std::uppercase << num;
    return ss.str();
}

// Fungsi utama
int main() {
    std::string binInput;

    // Membaca input biner 66-bit (11 pola x 6-bit)
    std::cout << "Masukkan string biner 66-bit (11 pola x 6-bit): ";
    std::cin >> binInput;

    if (binInput.length() != 66) {
        std::cerr << "Input harus tepat 66 bit." << std::endl;
        return 1;
    }

    // Mengonversi ke hexadecimal
    std::string hexOutput = binToHex(binInput);
    std::cout << "Hasil konversi ke hexadecimal: " << hexOutput << std::endl;

    return 0;
}

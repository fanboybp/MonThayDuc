#include <iostream>
#include <bitset>

// Hàm chuyển đổi chuỗi ký tự sang bitset
std::bitset<64> stringToBitset(const std::string& input) {
    std::bitset<64> bits;
    for (size_t i = 0; i < 64; ++i) {
        bits[i] = (input[i / 8] >> (i % 8)) & 1;
    }
    return bits;
}

// Hàm chuyển đổi bitset sang chuỗi ký tự
std::string bitsetToString(const std::bitset<64>& bits) {
    std::string str(8, '\0');
    for (size_t i = 0; i < 64; ++i) {
        str[i / 8] |= (bits[i] << (i % 8));
    }
    return str;
}

int main() {
    // Nhập khóa DES từ người dùng
    std::string userKey;
    std::cout << "Nhập khóa DES (chuỗi ký tự): ";
    std::getline(std::cin, userKey);

    // Chuyển đổi khóa từ chuỗi ký tự sang dạng bitset
    std::bitset<64> keyBits = stringToBitset(userKey);

    // Hiển thị khóa DES dưới dạng chuỗi ký tự hex
    std::cout << "DES Key: ";
    std::string keyString = bitsetToString(keyBits);
    for (char c : keyString) {
        std::cout << std::hex << (int)c;
    }
    std::cout << std::endl;

    return 0;
}
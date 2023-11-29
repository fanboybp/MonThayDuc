#include <iostream>
#include <bitset>

// Hàm chuyển đổi chuỗi ký tự sang bitset
using namespace std;
bitset<64> stringToBitset(const string& input) {
    std::bitset<64> bits;
    for (size_t i = 0; i < 64; ++i) {
        bits[i] = (input[i / 8] >> (i % 8)) & 1;
    }
    return bits;
}

// Hàm chuyển đổi bitset sang chuỗi ký tự
string bitsetToString(const bitset<64>& bits) {
    string str(8, '\0');
    for (size_t i = 0; i < 64; ++i) {
        str[i / 8] |= (bits[i] << (i % 8));
    }
    return str;
}

int main() {
    // Khóa DES có độ dài 64-bit
    string userKey = "nguyenluan"; // Thay thế bằng khóa thực tế của bạn

    // Chuyển đổi khóa từ chuỗi ký tự sang dạng bitset
    bitset<64> keyBits = stringToBitset(userKey);

    // Hiển thị khóa DES dưới dạng chuỗi ký tự hex
    cout << "DES Key: ";
    string keyString = bitsetToString(keyBits);
    for (char c : keyString) {
        cout << hex << (int)c;
    }
    cout << endl;

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// Lớp Vigenere để thực hiện mã hóa và giải mã dữ liệu sử dụng phương pháp Vigenere Cipher
class Vigenere
{
    public:
        string key;  // Khóa để thực hiện mã hóa và giải mã

        // Hàm khởi tạo khóa Vigenere từ một chuỗi nhập vào
        Vigenere(string key)
        {
            // Chuyển đổi chuỗi khóa thành chuỗi chỉ chứa các ký tự chữ cái in hoa
            for (int i = 0; i < key.size(); ++i)
            {
                if (key[i] >= 'A' && key[i] <= 'Z')
                    this->key += key[i];
                else if (key[i] >= 'a' && key[i] <= 'z')
                    this->key += key[i] + 'A' - 'a';
            }
        }

        // Hàm thực hiện mã hóa Vigenere
        string encrypt(string text)
        {
            string out;

            // Duyệt qua từng ký tự trong chuỗi cần mã hóa
            for (int i = 0, j = 0; i < text.length(); ++i)
            {
                char c = text[i];

                // Chuyển đổi ký tự thành chữ cái in hoa nếu là chữ cái thường
                if (c >= 'a' && c <= 'z')
                    c += 'A' - 'a';
                else if (c < 'A' || c > 'Z')
                    continue;  // Bỏ qua các ký tự không phải chữ cái

                // Thực hiện mã hóa Vigenere
                out += (c + key[j] - 2 * 'A') % 26 + 'A';
                j = (j + 1) % key.length();
            }

            return out;
        }

        // Hàm thực hiện giải mã Vigenere
        string decrypt(string text)
        {
            string out;

            // Duyệt qua từng ký tự trong chuỗi cần giải mã
            for (int i = 0, j = 0; i < text.length(); ++i)
            {
                char c = text[i];

                // Chuyển đổi ký tự thành chữ cái in hoa nếu là chữ cái thường
                if (c >= 'a' && c <= 'z')
                    c += 'A' - 'a';
                else if (c < 'A' || c > 'Z')
                    continue;  // Bỏ qua các ký tự không phải chữ cái

                // Thực hiện giải mã Vigenere
                out += (c - key[j] + 26) % 26 + 'A';
                j = (j + 1) % key.length();
            }

            return out;
        }
};

// Hàm main để kiểm tra mã hóa và giải mã Vigenere
int main()
{
    string s, k;
    cout << "Nhap chuoi: ";
    getline(cin, s);
    cout << "Nhap khoa: ";
    getline(cin, k);

    Vigenere key(k);

    string mahoa = key.encrypt(s);
    string giaima = key.decrypt(mahoa);

    cout << "Ma hoa: " << mahoa << endl;
    cout << "Giai ma: " << giaima;

    return 0;
}

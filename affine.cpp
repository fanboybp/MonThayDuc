#include <iostream>
#include <string>
using namespace std;

// Hàm tìm nghịch đảo modular của một số nguyên k trong modulo 26
int modInverse(int k)
{
    for (int i = 0; i < 26; i++)
    {
        int flag = (i * k) % 26;
        if (flag == 1)
        {
            return i;  // Nếu tìm thấy, trả về giá trị nghịch đảo
        }
    }
    return -1;  // Nếu không tìm thấy, trả về -1
}

// Hàm mã hóa chuỗi s bằng phương pháp Affine với khóa a và b
string encrypt(string s, int a, int b)
{
    string out = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s[i]))  // Chỉ xử lý ký tự là chữ cái
        {
            if (isupper(s[i]))
            {
                // Mã hóa ký tự chữ cái in hoa theo công thức Affine
                out += (a * int(s[i] - 65) + b) % 26 + 65;
            }
            else
            {
                // Mã hóa ký tự chữ cái thường theo công thức Affine
                out += (a * int(s[i] - 97) + b) % 26 + 97;
            }
        }
    }
    return out;  // Trả về chuỗi đã mã hóa
}

// Hàm giải mã chuỗi s đã được mã hóa bằng phương pháp Affine với khóa a và b
string decrypt(string s, int a, int b)
{
    string out = "";
    int key_inverse = modInverse(a);  // Tìm giá trị nghịch đảo của khóa a
    if (key_inverse == -1)
    {
        return "Khóa " + to_string(a) + " không phải là số nguyên tố, không tìm thấy nghịch đảo.";
    }

    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s[i]))  // Chỉ xử lý ký tự là chữ cái
        {
            if (isupper(s[i]))
            {
                // Giải mã ký tự chữ cái in hoa theo công thức Affine
                out += ((((s[i] - 65 - b) % 26 + 26) % 26) * key_inverse) % 26 + 65;
            }
            else
            {
                // Giải mã ký tự chữ cái thường theo công thức Affine
                out += ((((s[i] - 97 - b) % 26 + 26) % 26) * key_inverse) % 26 + 97;
            }
        }
    }
    return out;  // Trả về chuỗi đã giải mã
}

// Hàm main, nơi bắt đầu thực thi chương trình
int main()
{
    string s;
    int a, b;

    // Nhập chuỗi từ người dùng
    cout << "Nhập chuỗi: ";
    getline(cin, s);

    // Nhập khóa a và b từ người dùng
    cout << "Nhập khóa a: ";
    cin >> a;
    cout << "Nhập khóa b: ";
    cin >> b;

    // Mã hóa và giải mã chuỗi, sau đó in kết quả ra màn hình
    string mh = encrypt(s, a, b);
    cout << "Mã khoá: " << mh << endl;
    cout << "Giải mã: " << decrypt(mh, a, b) << endl;

    return 0;  // Kết thúc chương trình
}
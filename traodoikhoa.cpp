#include <iostream>
#include <cmath>
using namespace std;
// Tính modulo của a^b mod p
long long modPow(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % p;
        }
        b = b / 2;
        a = (a * a) % p;
    }
    return result;
}

int main() {
    // Tham số công khai p và g
    long long p; // Số nguyên tố lớn
    cout<<"nhap vao so nguyen to lon p : "<<endl;cin>>p;
    long long g;  // Số gốc, thường là một số nguyên tố nhỏ hơn p
    cout<<"nhap vao so nguyen to nho g : "<<endl;cin>>g;
    // Số ngẫu nhiên của mỗi bên
    long long a; // Alice chọn số ngẫu nhiên
    cout<<"nhap vao so ngau nhien a : "<<endl;cin>>a;
    long long b = 15; // Bob chọn số ngẫu nhiên
    cout<<"nhap vao so ngau nhien b : "<<endl;cin>>b;
    // Tính giá trị công khai g^a mod p và g^b mod p
    long long A = modPow(g, a, p);
    long long B = modPow(g, b, p);

    // In ra giá trị A và B
    cout << "Alice gui gia tri  A cho Bob: " << A << std::endl;
    cout << "Bob gui gia tri  B cho Alice: " << B << std::endl;

    // Tính khóa chia sẻ s
    long long secretKeyAlice = modPow(B, a, p);
    long long secretKeyBob = modPow(A, b, p);

    // In ra khóa chia sẻ
    cout << "Khoa chia se cua Alice: " << secretKeyAlice << std::endl;
    cout << "Khoa chia se cua Bob: " << secretKeyBob << std::endl;

    return 0;
}

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

//hàm tìm ước số chung lớn nhất của hai số
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

//hàm tính nghịch đảo modulo
int multiplicative_inverse(int e, int phi) {
    int d = 0;
    int x1 = 0;
    int x2 = 1;
    int y1 = 1;
    int temp_phi = phi;
    while (e > 0) {
        int temp1 = temp_phi / e;
        int temp2 = temp_phi - temp1 * e;
        temp_phi = e;
        e = temp2;
        int x = x2 - temp1 * x1;
        int y = d - temp1 * y1;
        x2 = x1;
        x1 = x;
        d = y1;
        y1 = y;
    }
    if (temp_phi == 1) {
        return d + phi;
    }
    return 0;
}

//hàm tính lũy thừa modulo a^b mod m
int mod_pow(int a, int b, int m) {
    if (b == 0)
        return 1;
    long long temp = mod_pow(a, b / 2, m);
    temp = (temp * temp) % m;
    if (b % 2 == 1)
        temp = (temp * a) % m;
    return temp;
}

//hàm tạo khóa
void generate_key(int p, int q, int &n, int &e, int &d) {
    n = p * q;
    int phi = (p - 1) * (q - 1);
    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }
    d = multiplicative_inverse(e, phi);
}

//hàm mã hóa
string encrypt(string message, int e, int n) {
    string encrypted_message = "";
    for (char c : message) {
        int m = c;
        int encrypted_char = mod_pow(m, e, n);
        encrypted_message += to_string(encrypted_char) + " ";
    }
    return encrypted_message;
}

//hàm giải mã
string decrypt(string encrypted_message, int d, int n) {
    string decrypted_message = "";
    int encrypted_char = 0;
    for (char c : encrypted_message) {
        if (c == ' ') {
            int decrypted_char = mod_pow(encrypted_char, d, n);
            decrypted_message += static_cast<char>(decrypted_char);
            encrypted_char = 0;
        } else {
            encrypted_char = encrypted_char * 10 + (c - '0');
        }
    }
    return decrypted_message;
}


int main() {
    int p, q;
    cout << "nhap p: ";
    cin >> p;
    cout << "nhap q: ";
    cin >> q;

    int e, d, n;
    cout <<"nhap e: ";
    cin >> e;
    generate_key(p, q, n, e, d);

    cout << "khoa cong khai: (" << e << ", " << n << ")" << endl;
    cout << "khoa bi mat: (" << d << ", " << n << ")" << endl;
    cin.ignore();
    cout<<"nhap vao lua chon cua ban: "<<endl;
    cout<<"1: ma hoa "<<endl<<"2: giai ma"<<endl;
    int luachon;
    cin>>luachon;
    if(luachon==1)
    {
        FILE *inputFile = fopen("C:\\Users\\sieua\\OneDrive\\Documents\\input.txt", "r");
        FILE *outputFile = fopen("C:\\Users\\sieua\\OneDrive\\Documents\\output.txt", "w");
        char input[256];
        cout << "chuoi can ma hoa: "<<endl;
        while (fgets(input, sizeof(input), inputFile) != NULL) {
        printf("%s\n",input);
            }
        string m(input);
        string mh = encrypt(m, e, n);
        cout << "chuoi sau khi ma hoa: " << mh << "\n";
        fprintf(outputFile,"%s",mh.c_str());
    }
    if(luachon==2)
    {
        FILE *outputFile = fopen("C:\\Users\\sieua\\OneDrive\\Documents\\output.txt", "r");
        char input[256];
        cout << "chuoi can giai ma: "<<endl;
        while (fgets(input, sizeof(input), outputFile) != NULL) {
        printf("%s\n",input);
            }
        string m(input);
        string gm = decrypt(m, d, n);
        cout << "chuoi sau khi giai ma: " << gm << "\n";
    }
    return 0;
}

#include<iostream>
#include<math.h>
using namespace std;

int key[3][3]; // Ma trận khóa

// Hàm này trả về giá trị của x modulo 26. Nó được sử dụng để đảm bảo rằng các giá trị nằm trong khoảng từ 0 đến 25.
int mod26(int x) {
    return x >= 0 ? (x % 26) : 26 - (abs(x) % 26);
}

// Hàm này nhân hai ma trận a và b, sau đó lưu kết quả vào ma trận res. Nó cũng sử dụng hàm mod26 để đảm bảo giữ cho giá trị thu được trong khoảng 0 đến 25.
void multiplymatrices(int a[1000][3], int a_rows, int a_cols,
                      int b[1000][3], int b_rows, int b_cols,
                      int res[1000][3]) {
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            for (int k = 0; k < b_rows; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
            res[i][j] = mod26(res[i][j]);
        }
    }
}

// Hàm mã hóa chuỗi pt bằng mật mã Hill sử dụng ma trận khóa key có kích thước nxn.
string encrypt(string pt, int n) {
    int P[1000][3] = {0};
    int C[1000][3] = {0};
    int pt_iter = 0;

    // Bổ sung 'x' vào cuối chuỗi pt nếu kích thước không chia hết cho n
    while (pt.length() % n != 0) {
        pt += "x";
    }
    int row = (pt.length()) / n;

    // Đổ giá trị của các ký tự trong chuỗi pt vào ma trận P
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < n; j++) {
            P[i][j] = pt[pt_iter++] - 'a';
        }
    }

    // Nhân ma trận P với ma trận khóa key, lưu kết quả vào ma trận C
    multiplymatrices(P, row, n, key, n, n, C);

    string ct = "";
    // Đổ giá trị của ma trận C thành chuỗi kết quả
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < n; j++) {
            ct += (C[i][j] + 'a');
        }
    }
    return ct;
}

int main() {
    int n;
    FILE *inputFile = fopen("C:\\Users\\sieua\\OneDrive\\Documents\\input.txt", "r");
    FILE *outputFile = fopen("C:\\Users\\sieua\\OneDrive\\Documents\\output.txt", "w");
    char input[256];
    cout << "chuoi can ma hoa: " << endl;
    while (fgets(input, sizeof(input), inputFile) != NULL) {
        printf("%s\n", input);
    }
    string pt(input);
    cout << "nhap chuoi kich thuoc ma tran: ";
    cin >> n;

    cout << "nhap ma tran: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> key[i][j];
        }
    }

    string ct = encrypt(pt, n);
    cout << "chuoi sau khi ma hoa: " << ct << endl;
    fprintf(outputFile, "%s", ct.c_str());
    return 0;
}

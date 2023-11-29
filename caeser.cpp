#include <iostream>
#include <string>
using namespace std;

string caeser_encrypt(string s, int k) {
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            if (isupper(s[i])) {
                s[i] = (s[i] - 65 + k) % 26 + 65;
            } else {
                s[i] = (s[i] - 97 + k) % 26 + 97;
            }
        }
    }
    return s;
}

string caesar_decrypt(string s, int k) {
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            if (isupper(s[i])) {
                s[i] = (s[i] - 65 - k + 26) % 26 + 65;
            } else {
                s[i] = (s[i] - 97 - k + 26) % 26 + 97;
            }
        }
    }
    return s;
}

int main() {
    FILE *inputFile = fopen("C:\\Users\\sieua\\OneDrive\\Documents\\index.txt", "r");
     char input[256];
     cout << "chuoi can ma hoa: "<<endl;
    while (fgets(input, sizeof(input), inputFile) != NULL) {
        printf("%s",input);
    }
    cout << "\nnhap k: ";
    int k;
    cin >> k;

    string mh = caeser_encrypt(input, k);
    cout << "chuoi da ma hoa: " << mh <<endl;
    cout << "chuoi da giai ma: " << caesar_decrypt(mh,k);
    return 0;
}
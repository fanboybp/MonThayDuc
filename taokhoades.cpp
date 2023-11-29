#include <iostream>
#include<bitset>
using namespace std;

int pc_1[] = {
   57, 49, 41, 33, 25, 17, 9 ,
   1 , 58, 50, 42, 34, 26, 18,
   10, 2 , 59, 51, 43, 35, 27,
   19, 11, 3 , 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
   7 , 62, 54, 46, 38, 30, 22,
   14, 6 , 61, 53, 45, 37, 29,
   21, 13, 5 , 28, 20, 12, 4 };
//Mảng pc_1 chứa thông tin về hoán vị (permutation) đầu tiên cho khóa gốc (64 bit) để tạo thành một khóa 56 bit.

int pc_2[] = {
   14, 17, 11, 24, 1 , 5 , 3 , 28,
   15, 6 , 21, 10, 23, 19, 12, 4 ,
   26, 8 , 16, 7 , 27, 20, 13, 2 ,
   41, 52, 31, 37, 47, 55, 30, 40,
   51, 45, 33, 48, 44, 49, 39, 56,
   34, 53, 46, 42, 50, 36, 29, 32 };
//Mảng pc_2 chứa thông tin về hoán vị thứ hai từ khóa 56 bit đã được chia thành hai nửa 28 bit để tạo ra 16 khóa con 48 bit mỗi khóa.
int leftShift[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
//Mảng leftShift xác định số lần dịch bit trái đối với mỗi vòng lặp trong việc tạo 16 khóa con.
string rotateSubKey(string s , int rot)
{
    return s.substr(rot, s.length()-rot) + s.substr(0, rot) ;
}
// Dịch chuyển bit trong chuỗi s theo số lượng rot bit và kết hợp các phần tử đầu và cuối chuỗi để tạo chuỗi mới sau khi dịch.
string firstPermute(string input)
{
    string res = "" ;
    for(int i=0 ; i<56 ; i++)
    {
        res += input[pc_1[i]-1];
    }
    return res ;
}
//Áp dụng hoán vị theo mảng pc_1 để thu được khóa 56 bit từ khóa ban đầu 64 bit.
string secondPermute(string input)
{
    string res = "" ;
    for(int i=0 ; i<48 ; i++)
    {
        res += input[pc_2[i]-1];
    }
    return res ;
}
// Áp dụng hoán vị theo mảng pc_2 để thu được khóa con 48 bit từ khóa 56 bit.
void generate_key(string left, string right)
{
    for (int i=0; i<16; i++)
    {
        left  = rotateSubKey(left , leftShift[i]);
        right = rotateSubKey(right, leftShift[i]);

        string key = secondPermute(left+right);

        cout << "key " << i+1 << ": " << key << endl;
    }
}
//Trong hàm generate_key, các chuỗi con 28 bit được tạo ra từ khóa 56 bit và dịch chuyển bit theo số lần quy định trong mảng leftShift. Sau đó, các chuỗi này được kết hợp để tạo thành khóa con 48 bit thông qua hoán vị pc_2. Kết quả khóa con được in ra màn hình.

int main()
{
    unsigned long long hexkey;
    cout << "nhap key: " ;
    cin >> hex >> hexkey;

    string key = bitset<64>(hexkey).to_string();
    cout << "key nhi phan: " << key <<"\n\n";

    key = firstPermute(key);
    //cout <<"key pc-1: " << key<<"\n\n";
    generate_key(key.substr(0,28) , key.substr(28,28));

    return 0;
}

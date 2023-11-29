#include<iostream>
#include<math.h>
using namespace std ;

int key[3][3] ;

int mod26(int x)
{
	return x >= 0 ? (x%26) : 26-(abs(x)%26) ;
}
//Hàm này trả về giá trị của x modulo 26. Nó được sử dụng để đảm bảo rằng các giá trị nằm trong khoảng từ 0 đến 25.
int findDet(int m[3][3] , int n)
{
	int det;
	if(n == 2)
	{
		det = m[0][0] * m[1][1] - m[0][1]*m[1][0] ;
	}
	else if (n == 3)
	{
		det = m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])  - m[0][1]*(m[1][0]*m[2][2] - m[2][0]*m[1][2] ) + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
	}
	else det = 0 ;
	return mod26(det);
}
//Hàm này tính định thức của một ma trận vuông m có kích thước nx n. Định thức được sử dụng trong việc tìm ma trận nghịch đảo.
int findDetInverse(int R , int D = 26)
{
	int i = 0 ;
	int p[100] = {0,1};
	int q[100] = {0} ;

	while(R!=0)
	{
		q[i] = D/R ;
		int oldD = D ;
		D = R ;
		R = oldD%R ;
		if(i>1)
		{
			p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
		}
		i++ ;
	}
	if (i == 1) return 1;
	else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
}
//Hàm này tính giá trị nghịch đảo modular của một số R modulo D. Nó sử dụng thuật toán Euclid mở rộng để tính giá trị nghịch đảo.
void multiplymatrices(int a[1000][3] , int a_rows , int a_cols ,  int b[1000][3] , int b_rows , int b_cols , int res[1000][3])
{
	for(int i=0 ; i < a_rows ; i++)
	{
		for(int j=0 ; j < b_cols ; j++)
		{
			for(int k=0 ; k < b_rows ; k++)
			{
				res[i][j] += a[i][k]*b[k][j] ;
			}
			res[i][j] = mod26(res[i][j]) ;
		}
	}
}
//Hàm này nhân hai ma trận a và b, sau đó lưu kết quả vào ma trận res. Nó cũng sử dụng hàm mod26 để đảm bảo giữ cho giá trị thu được trong khoảng 0 đến 25.
void findInverse(int m[3][3] , int n , int m_inverse[3][3] )
{
	int adj[3][3] = {0};

	int det = findDet(m , n);
	int detInverse = findDetInverse(det);

	if(n==2)
	{
		adj[0][0] = m[1][1];
		adj[1][1] = m[0][0];
		adj[0][1] = -m[0][1];
		adj[1][0] = -m[1][0];
	}
	else if(n==3)
	{
		int temp[5][5] = {0} ;
		for(int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++)
			{
				temp[i][j] = m[i%3][j%3] ;
			}
		}
		for(int i=1; i<=3 ; i++)
		{
			for(int j=1; j<=3 ; j++)
			{
				adj[j-1][i-1] = temp[i][j]*temp[i+1][j+1] - temp[i][j+1]*temp[i+1][j];
			}
		}
	}

	for(int i=0; i<n ; i++)
	{
		for(int j=0; j<n ; j++)
		{
			m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;
		}
	}
}
//Hàm này tìm ma trận nghịch đảo của ma trận vuông m có kích thước nx n bằng cách sử dụng định thức và giá trị nghịch đảo modular.
string decrypt(string ct, int n)
{
	int P[1000][3] = {0} ;
	int C[1000][3] = {0} ;
	int ctIter = 0 ;

	int row = ct.length()/n;

	for(int i=0; i<row ; i++)
	{
		for(int j=0; j<n; j++)
		{
			C[i][j] = ct[ctIter++]-'a' ;
		}
	}

	int k_inverse[3][3] = {0};
	findInverse(key, n , k_inverse);
	multiplymatrices(C, row , n , k_inverse , n , n , P) ;

	string pt = "" ;
	for(int i = 0 ; i<row ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			pt += (P[i][j] + 'a');
		}
	}
	return pt ;
}
// Hàm này sử dụng ma trận nghịch đảo để giải mã chuỗi đã mã hóa ct theo mật mã Hill.
int main()
{

	int n ;
	FILE *outputFile = fopen("D:\\ontapmatma\\output.txt", "r");
        char input[256];
        cout << "chuoi can giai ma: "<<endl;
        while (fgets(input, sizeof(input), outputFile) != NULL) {
        printf("%s\n",input);
            }
        string ct(input);
    cout << "nhap chuoi kich thuoc ma tran: " ;
	cin >> n;

	cout<<"nhap ma tran: " <<endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cin >> key[i][j];
		}
	}

	string dt = decrypt(ct, n);
	cout << "chuoi sau khi giai ma: " << dt << endl;
	return 0;
}


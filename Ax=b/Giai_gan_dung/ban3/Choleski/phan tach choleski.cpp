#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;
double u[50][50], b[50][50], l[50][50], d[50];
	int m, n, k;

// Dữ liệu đầu vào
void input()
{
    cin >> m;
	n >> m + 1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m+1; j++)
            cin >> u[i][j];
	cout << "Ma tran A" << endl;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++)
			cout << setw(15) << right << setprecision(10) << fixed << u[i][j];
		cout << endl;}
}

void chuyenvi(double a[][50], double b[][50], int m){
	int i, j, t;
	for (i = 0; i < m; i++) {
		for (j = 0; j <= i; j++) {
        	b[j][i] = a[i][j];
        	b[i][j] = a[j][i];
    	}
	}
}
void nhan(double a[][50], double b[][50], int m){
	int i, j, k;
	double sum, c[50][50];
	for (i = 0; i < m; i++) {
    	for (j = 0; j < m; j++) {
        	sum = 0;
        	for (k = 0; k < m; k++) {
        		sum = sum + b[i][k] * a[k][j];
         }
        c[i][j] = sum;
    	}
	}
	for (i = 0; i < m; i++)
    	for (j = 0; j < m; j++)
    		a[i][j] = c[i][j];
    cout << "Ma tran ket qua" << endl;
	for(i = 0; i < m; i++){
		for(j = 0; j < m; j++)
			cout << setw(15) << right << a[i][j] << "   ";
		cout << endl;}
	cout << "===============================" << endl;
}
void nhan2(double a[][50], double b[], int m){
	double c[50];
	for(int i = 0; i < m; i++){
		c[i] = 0;
		for(int j = 0; j < m; j++)
			c[i] += a[i][j]*b[j];
	}
	for(int i = 0; i < m; i++)
		b[i] = c[i];
}
int cholesky(double a[][50], double l[][50], int m){
	int i, j, k;
	double s, p, q;
	for(i = 0; i < m; i++){
		cout << "i = " << i << endl;
		for(j = 0; j <= i; j++){
			s = 0;
			for(k = 0; k < j; k++)
				s += l[i][k]*l[j][k];
			if(i == j){
				p = (a[i][i] - s);
				if(roundf(p*1e+6)/1e+6 == 0){
					cout << "A[" << i << "," << i << "] - sigma(l[i,k]*l[j,k]) = " << p << ", khong thuc hien duoc theo phan tach Cholesky tren truong so thuc" << endl;
					return -1;}
				else if(roundf(p*1e+6)/1e+6 < 0) {
					cout << "A[" << i << "," << i << "] - sigma(l[i,k]*l[j,k]) = " << p << ", thuc hien nhan moi ma tran A chuyen vi va thuc hien lai" << endl;
					cout << "=====================" << endl;
					return 1;}
				else l[i][i] = sqrt(p);
			}
			else{
				q = l[j][j];
				if(q == 0) {
					cout << "l" << j << j << " = " << l[j][j] << ", khong thuc hien duoc theo phan tach Cholesky tren truong so thuc" << endl;
					return -1;}
				else l[i][j] = (a[i][j] - s)/q;
				}
		}
		cout << "Ma tran L" << endl;
			for(int b = 0; b < m; b++){
				for(int c = 0; c < m; c++)
					cout << setw(15) << right << l[b][c];
				cout << endl;}
		cout << "___________________________________________" << endl;
	}
	return 0;
}


int main()
{
	freopen("CholeskyInput.txt", "r", stdin);
    freopen("CholeskyOutput.txt", "w", stdout);
    input();

	for(int i = 0; i < m; i++)
		d[i] = u[i][n-1];
	n--;
//Tao ma tran L
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++) l[i][j] = 0;
		
//Kiem tra ma tran doi xung va thuc hien phan tach ma tran
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++)
			if(u[i][j] != u[j][i]) {
				chuyenvi(u, b, m);
				cout << "A khong doi xung, nhan voi ma tran chuyen vi" << endl;
				nhan(u, b, m);
				nhan2(b, d, m);
			} 
	int check = cholesky(u, l, m);
	if(check == -1) return 0;
	if(check == 1){
		chuyenvi(u, b, m);
		nhan(u, b, m);
		nhan2(b, d, m);
		if(cholesky(u, l, m) == -1) return 0;
	}
	
//Giai pt Ly = d

//Tao ma tran bo sung sung L|d
	for(int i = 0; i < m; i++)
		l[i][n] = d[i];
	++n;
	cout << endl << "Ma tran L bo sung" << endl;
	for(k = 0; k < m; k++) {
		for(int j = 0; j < n; j++)
			cout << setw(15) << right << l[k][j] << "    ";
		cout << endl;
	}
//Giai pt
	double y[50];
	cout << endl << "Giai phuong trinh Ly = b" << endl;
	for(int i = 0; i < m; i++){
		y[i] = l[i][n-1];
		for(int j = 0; j < i; j++)
			y[i] -= l[i][j]*y[j];
		y[i] = y[i]/l[i][i];
		double tmp = roundf(y[i]*1e+6)/1e+6;
		if(tmp == 0) y[i] = tmp;
	}
	cout << "Nghiem y duy nhat" << endl;
		for(int i = 0; i < m; i++)
			cout << "y" << i << " = " << y[i] << endl;
			
//Giai pt Ux = y
//Tao ma tran bo sung U|y
	chuyenvi(l, u, m);
	for(int i = 0; i < m; i++)
		u[i][n-1] = y[i];
	cout << endl << "Ma tran U bo sung" << endl;
	for(k = 0; k < m; k++) {
		for(int j = 0; j < n; j++)
			cout << setw(15) << right << u[k][j] << "    ";
		cout << endl;
	}
	
	cout << endl << "Giai phuong trinh Ux = y" << endl;
	double x[50];
	for(int i = m-1; i >= 0; i--){
		x[i] = u[i][n-1];
		for(int j = 0; j < m; j++)
			if(i != j) x[i] -= u[i][j]*x[j];
		x[i] = x[i]/u[i][i];
	}
	cout << "He co nghiem duy nhat" << endl;
	for(int i = 0; i < m; i++)
		cout << "x" << i << " = " << x[i] << endl;
 	return 0;
}
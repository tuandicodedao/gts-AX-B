#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
#define M 50
#define ep 1e-3

// in ma trận 
void print (double matrix[][M], int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(20) << matrix[i][j];
        cout << endl;
    }
    cout << endl;
}
// in mảng X
void PrintX (double x[], int n) {
    for (int i = 0; i<n; i++)
        cout << setprecision(12) << x[i] << endl;
    cout << "-----------------------" << endl;
}
// gán x0 = x1
void Assign (double x0[], double x1[], int n) {
    for (int i = 0; i<n; i++ )
        x0[i] = x1[i];
}
// kiểm tra chéo trội hàng
int troihang (double a[][M], int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) 
                sum += abs(a[i][j]);
        }
        if (abs(a[i][i]) <= sum) 
            return 0;
    }
    return 1;
}
// kiểm tra chéo trội cột
int troicot (double a[][M], int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j)
                sum += abs(a[j][i]);
        }
        if (abs(a[i][i]) <= sum)
            return 0;
    }
    return 1;
}
//chuẩn 1 (max theo cột)
double chuan1 (double b[][M], int n) {
    // tính tổng theo cột
    double max1[n]  = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            max1[i] += abs(b[j][i]);
        }
    }
    // tìm chuẩn là max của dãy max1
    double max = max1[0];
    for (int i = 1; i<n; i++) {
        if (max1[i] > max) 
            max = max1[i];
    }
    //cout << "Chuan mot: " << max << endl;
    return max;
}
//chuẩn vô cùng (max theo hàng)
double chuanVocung (double b[][M], int n) {
    // tính tổng theo hàng
    double max8[n] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            max8[i] += abs(b[i][j]);
        }
    }
    // tìm chuẩn là max của max8
    double max = max8[0];
    for (int i = 1; i < n; i++)
        if (max8[i] > max)
            max = max8[i];
    //cout << "Chuan vo cung: " << max << endl;
    return max;
}
// chuẩn 1 của x (max theo cột)
double chuan1x (double x[], int n) {
    double chuan = 0;
    for (int i = 0; i < n; i++)
        chuan += abs(x[i]);
    cout << "x co chuan 1: " << chuan << endl;
    return chuan;
}
// chuẩn vô cùng của x (max theo hàng)
double chuanVocungx (double x[], int n) {
    double chuan = abs(x[0]);
    for (int i = 1; i < n; i++)
        if (abs(x[i]) > chuan)
            chuan = abs(x[i]);
    cout << "x co chuan vo cung: " << chuan << endl;
    return chuan;
}

// lặp khi chéo trội hàng
void hang (double a[][M], double x0[], int n) {
    
    // gán ma trận d
    cout << "Bien doi Ax = b thanh dang x = Bx + d" << endl;
    double d[n];
    for (int i = 0; i < n; i++) {
        d[i] = a[i][n]/a[i][i];
    }
    
    // gán ma trận b
    double b[n][M];
    for (int i = 0; i < n; i++) {
        b[i][i] = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                b[i][j] = -a[i][j]/a[i][i];
            }
        }
    }
    cout << "\nMa tran B:\n";
    print(b,n);
    cout << "Ma tran D:\n";
    for (int i = 0; i < n; i++)
        cout << setw(10) << d[i]; 

    double q8 = chuanVocung (b, n);
    cout << "\n\nHe so co: " << q8 << endl;
    double x1[n];
    // tính x1 = Bx + d
    for (int i = 0; i < n; i++) {
        x1[i] = 0;
        for (int j = 0; j < n; j++) {
            x1[i] += b[i][j]*x0[j]; 
        }
        x1[i] += d[i];
    }
    cout << "\ni = 1" << endl;
    PrintX (x1,n);

    // tính ||x1-x0||
    double chuanx[n];
    for (int i = 0; i < n; i++)
        chuanx[i] = x1[i] - x0[i];
    
    // theo chuẩn vô cùng
    double a8 = chuanVocungx (chuanx, n);
    double ep0 = ep*(1-q8)/q8;
    cout << "Sai so: " << ep0 << endl;
    //int n2 = ceil(log(ep*(1-q8)/a8)/log(q8));

    // vòng lặp tìm x1 
    int i = 2;
    while (a8 > ep0) {   //lặp với chuẩn 1
        cout << "\ni = " << i << endl;
            //gán x0 = x1
            Assign (x0, x1, n);
            // tính x1 = B*x0 + d
            for (int i = 0; i < n; i++) {
                x1[i] = 0;
                for (int j = 0; j < n; j++) {
                    x1[i] += b[i][j]*x0[j]; 
                }
            x1[i] += d[i];
            }
            // tính chuẩn || x1 - x0 ||
            for (int i = 0; i < n; i++)
            chuanx[i] = x1[i] - x0[i];
            // theo chuẩn vô cùng
            a8 = chuanVocungx (chuanx, n);
            cout << "Sai so: " << q8 * a8 / (1-q8) << endl;
        PrintX(x1, n);
        i++;
    }
}

// lặp khi chéo trội cột
void cot (double a[][M], double x0[], int n) {
    cout << "Bien doi Ax = b thanh dang x = Bx + d" << endl;
    // gán ma trận d
    double d[n];
    for (int i = 0; i < n; i++) {
        d[i] = a[i][n];
    }
    // gán ma trận b
    double b[n][M];
    for (int i = 0; i < n; i++) {
        b[i][i] = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                b[j][i] = -a[j][i]/a[i][i];
            }
        }
    }
    cout << "\nMa tran B:\n";
    print(b,n);
    cout << "Ma tran D: \n";
    for (int i = 0; i < n; i++)
        cout << setw(10) << d[i];

    double q1 = chuan1 (b, n);
    cout << "\n\nHe so co: " << q1 << endl;
    
    double x1[n];
    // tính x1 = Bx + d
    for (int i = 0; i < n; i++) {
        x1[i] = 0;
        for (int j = 0; j < n; j++) {
            x1[i] += b[i][j]*x0[j]; 
        }
        x1[i] += d[i];
    }
    cout << "\ni = 1" << endl;
    PrintX (x1,n);

    // tính ||x1-x0||
    double chuanx[n];
    for (int i = 0; i < n; i++)
        chuanx[i] = x1[i] - x0[i];
    
    // theo chuẩn 1
    double a1 = chuan1x (chuanx, n);
    double ep0 = ep*(1-q1)/q1;
    cout << "Sai so: " << ep0 << endl;
    int n1 = ceil(log(ep*(1-q1)/a1)/log(q1));

    // vòng lặp tìm x1 
    int i = 2;
    while (a1 > ep0) {   //lặp với chuẩn 1
        cout << "\ni = " << i << endl;
            //gán x0 = x1
            Assign (x0, x1, n);
            // tính x1 = B*x0 + d
            for (int i = 0; i < n; i++) {
                x1[i] = 0;
                for (int j = 0; j < n; j++) {
                    x1[i] += b[i][j]*x0[j]; 
                }
            x1[i] += d[i];
            }
            // tính chuẩn || x1 - x0 ||
            for (int i = 0; i < n; i++)
            chuanx[i] = x1[i] - x0[i];
            // theo chuẩn 1
            a1 = chuan1x (chuanx, n);
            cout << "Sai so: " << q1 * a1 / (1-q1) << endl;
        PrintX(x1, n);
        i++;
    }
    cout << "Nghiem:" << endl;
    for (int i = 0; i < n; i++)
        x1[i] = x1[i]/a[i][i];
    PrintX(x1, n);
}

int main () {
    ifstream read ("Nhap.txt");
    int n = 0;
    string s;
    //đếm số ẩn
    while (getline(read, s))
        n++;
    cout << "So an: " << n << endl;
    read.close();
    // lấy ma trận A ngã
    double a[n][M];
    read.open ("Nhap.txt");
    for (int i = 0; i<n; i++)
        for (int j = 0; j<=n; j++)
            read >> a[i][j];
    read.close();   

    double x0[n] = {0.0};   // giá trị ban đầu x0

    // kiểm tra trội hàng
    int h = troihang(a, n);
    int c = troicot(a, n);

    if (h == 1 && c == 1) {
        cout << "Cheo troi ca hang & cot" << endl;
        cout << "Tinh theo cheo troi hang" << endl;
        hang (a, x0, n);
    }
    if (h == 1 && c == 0) {
        cout << "Cheo troi Hang" << endl;
        hang (a, x0, n);
    }
    if (h == 0 && c == 1) {
        cout << "Cheo troi Cot" << endl;
        cot (a, x0, n);
    }
    if (h == 0 && c == 0) {
        cout << "Khong cheo troi \n=> Khong dung dc Jacobi";
        return 0;
    }
    return 0;
}
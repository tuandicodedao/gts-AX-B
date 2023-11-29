// Phương pháp lặp Gauss Seidel để giải hệ pt Ax=b
#include <bits/stdc++.h>
#define N 105

using namespace std;

long int n, k;
double a[N][N], b[N], c[N][N], x[N], y[N];
double epsi, lamda, s, zeta;

// Dữ liệu đầu vào
void input()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < n; i++)
        x[i] = 0;
    cin >> epsi;
}

// Kiểm tra tính chéo trội hàng
bool row_diagonal()
{
    double temp;
    for (int i = 0; i < n; i++)
    {
        temp = 0;
        for (int j = 0; j < n; j++)
            if (j != i)
                temp = temp + fabs(a[i][j]);
        if (abs(a[i][i]) <= temp)
            return false;
    }
    return true;
}

// Kiểm tra tính chéo trội cột
bool col_diagonal()
{
    double temp;
    for (int i = 0; i < n; i++)
    {
        temp = 0;
        for (int j = 0; j < n; j++)
            if (j != i)
                temp = temp + fabs(a[j][i]);
        if (abs(a[i][i]) <= temp)
            return false;
    }
    return true;
}

// Biến đổi Ax=b về dạng x=Cx+d
// Tìm ma trận C khi chéo trội hàng
void C_row_matrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                c[i][j] = 0;
            else
                c[i][j] = -a[i][j] / a[i][i];
        }
    }
}

// Tính hệ số lamda của điều kiện dừng khi chéo trội hàng
double lamda_cal()
{
    double lamdaa = 0;
    double gamma, beta, temp;
    C_row_matrix();
    for (int i = 0; i < n; i++)
    {
        gamma = 0;
        beta = 0;
        for (int j = 0; j < i; j++)
            beta += fabs(c[i][j]);
        for (int j = i; j < n; j++)
            gamma += fabs(c[i][j]);
        temp = gamma / (1 - beta);
        if (temp > lamdaa)
            lamdaa = temp;
    }
    return lamdaa;
}

// Tìm ma trận C khi chéo trội cột
void C_col_matrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != i)
                c[i][j] = -a[i][j] / a[j][j];
            else
                c[i][j] = 0;
        }
    }
}

// Tính hệ số s khi chéo trội cột
double s_cal()
{
    double s, temp;
    C_col_matrix();
    for (int j = 0; j < n; j++)
    {
        temp = 0;
        for (int i = j + 1; i < n; i++)
            temp += fabs(c[i][j]);
        if (temp > s)
            s = temp;
    }
    return s;
}

// Tính hệ số zeta của điều kiện dừng khi chéo trội cột
double zeta_cal()
{
    double zeta = 0;
    double gamma, beta, temp;
    C_col_matrix();
    for (int j = 0; j < n; j++)
    {
        gamma = 0;
        beta = 0;
        for (int i = 0; i < j; i++)
            beta += fabs(c[i][j]);
        for (int i = j + 1; i < n; i++)
            gamma += fabs(c[i][j]);
        temp = beta / (1 - gamma);
        if (temp > zeta)
            zeta = temp;
    }
    return zeta;
}

// Tìm nghiệm khi chéo trội hàng
void row_solve()
{
    double z[N];
    double temp, norm;
    lamda = lamda_cal();
    k = 0; // khoi tao de tinh so lan lap
    cout << "\nMa tran da cho cheo troi hang\n";
    cout << "Ta dua ve ma tran dang sau x = Cx + D: \n";
    C_row_matrix();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << fixed << setw(10) << setprecision(4) << c[i][j];
        }
        cout << "   |" << fixed << setw(10) << setprecision(4) << b[i] / a[i][i] << endl;
    }
    while (true)
    {
        k = k + 1;
        for (int i = 0; i < n; i++)
            z[i] = x[i];
        for (int i = 0; i < n; i++)
        {
            temp = 0;
            for (int j = 0; j < n; j++)
                if (j != i)
                    temp += c[i][j] * x[j];
            x[i] = b[i] / a[i][i] + temp;
        }
        norm = 0;
        // tính chuẩn || z - x ||
        for (int i = 0; i < n; i++)
        {
            if (fabs(z[i] - x[i]) > norm)
                norm = fabs(z[i] - x[i]);
        }

        cout << "\nLan lap thu " << k << ": \n";
        for (int i = 0; i < n; i++)
        {
            cout << "x" << i + 1 << "= " << setprecision(10) << x[i] << endl;
        }

        cout << "Sai so = " << setprecision(10) << lamda * norm / (1 - lamda) << "\n";
        if (norm < epsi * (1 - lamda) / lamda)
            break; // kiem tra dieu kien dung
    }
    cout << fixed;
    cout << "\n\nNghiem cua phuong trinh la: \n";
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << "= " << setprecision(10) << x[i] << endl;
    cout << "\nSo lan lap: " << k;
    cout << "\nHe so co: lamda = " << lamda;
    cout << "\nSai so cuoi cung la: " << lamda * norm / (1 - lamda);
}

// Tìm nghiệm khi chéo trội cột
void col_solve()
{
    double z[N];
    double norm, temp;
    k = 0;
    s = s_cal();
    zeta = zeta_cal();
    cout << "\nMa tran da cho cheo troi cot\n";
    cout << "Ta dua ve ma tran dang sau y = Cy + D: \n";
    C_col_matrix();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << fixed << setw(10) << setprecision(4) << c[i][j];
        }
        cout << "   |" << fixed << setw(10) << setprecision(4) << b[i] << endl;
    }
    for (int i = 0; i < n; i++)
        y[i] = x[i] * a[i][i];

    while (true)
    {
        k = k + 1;
        for (int i = 0; i < n; i++)
            z[i] = y[i];

        for (int i = 0; i < n; i++)
        {
            temp = 0;
            for (int j = 0; j < n; j++)
                if (j != i)
                    temp += c[i][j] * y[j];

            y[i] = b[i] + temp;
            x[i] = y[i] / a[i][i]; // dua tu y ve lai x
        }

        cout << "\nLan lap thu " << k << ": \n";
        for (int i = 0; i < n; i++)
        {
            cout << "x" << i + 1 << "= " << setprecision(10) << x[i] << endl;
        }
        norm = 0;
        // Tính chuẩn || z - y ||
        for (int i = 0; i < n; i++)
        {
            norm += fabs(y[i] - z[i]);
        }
        cout << "Sai so = " << setprecision(10) << zeta * norm / ((1 - s) * (1 - zeta)) << "\n";

        if (norm < epsi * (1 - s) * (1 - zeta) / zeta)
            break;
    }
    cout << fixed;
    cout << "\n\nNghiem cua phuong trinh la: \n";
    for (int i = 0; i < n; i++)
        cout << "x" << i + 1 << "= " << setprecision(10) << x[i] << endl;
    cout << "\nSo lan lap: " << k;
    cout << "\nHe so co: zeta = " << zeta;
    cout << "\nSai so cuoi cung la: " << zeta * norm / ((1 - s) * (1 - zeta));
}

int main()
{
    freopen("GaussSeidelInput.txt", "r", stdin);
    freopen("GaussSeidelOutput.txt", "w", stdout);
    input();
    // in ra ma trân Ax = b ban đầu
    cout << "\nMa tran Ax = b ban dau: \n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << fixed << setw(10) << setprecision(4) << a[i][j];
        }
        cout << "   |" << fixed << setw(10) << setprecision(4) << b[i] << endl;
    }

    if (row_diagonal() == 1)
        row_solve();
    else
    {
        if (col_diagonal() == 1)
            col_solve();
        else
            cout << "\nMa tran khong cheo troi, can tim phuong phap khac";
    }
}

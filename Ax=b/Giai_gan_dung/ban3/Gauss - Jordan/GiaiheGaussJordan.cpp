#include <stdio.h>
#include <math.h>

// In ma tran
void InMt(double M[100][100], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%lf\t", M[i][j]);
        }
        printf("\n\n");
    }
}

// Dua ma tran ve dang bac thang rut gon
void RutGon(double M[100][100], int m, int n)
{
    double HeSoNhan, tg;
    int i, j, k, l, kt, dong;
    int dem = 0;
    // Chuyen doi ma tran M ve dang bac thang rut gon

    for (i = 0; i < n - 1; i++)
    {
        /*
         * Bien doi theo cot
         *
         * Doi cho dong de dua ma tran ve dang co the bien ve so 1
         */
        if (M[i][i] == 0)
        {
            // Tim dong co cot i khac 0 de doi cho
            for (k = i + 1; k < m; k++)
            {
                if (M[k][i] != 0)
                {
                    // Doi cho dong k chua phan tu != 0 do voi dong i dang xet
                    for (l = 0; l < n; l++)
                    {
                        tg = M[i][l];
                        M[i][l] = M[k][l];
                        M[k][l] = tg;
                    }

                    break; // dung vong for lai khi da doi cho xong
                }
            }
            dem++;
            printf("\nMa tran bien doi lan %d", dem);
            printf("\n\n");
            InMt(M, m, n);
        } // Hoan tat doi cho

        /*
         * Tien hanh bien doi M[j][i] thanh so 1 va so 0
         * Chuyen doi lan luot tung dong theo dung loai
         */
        for (j = 0; j < m; j++)
        {
            /*
             * Xac dinh loai can chuyen ve so 0 hay so 1
             * loai = 2 la truong hop phan tu M[j][i] da o dung vi tri
             * khong can bien doi gi ca.
             */
            int loai = 2;

            // Neu M[j][i] khong nam tren duong cheo chinh va ban than no khac 0
            if ((j != i) && (M[j][i] != 0))
            {
                // M[j][i] can chuyen ve 0
                loai = 0;
            }

            // Neu M[j][i] nam tren duong cheo chinh va ban than no khac 1
            if ((j == i) && (M[j][i] != 1))
            {
                // M[j][i] can chuyen ve 1
                loai = 1;
            }

            switch (loai)
            {
            // Truong hop can chuyen M[j][i] ve so 0
            case 0:
                // Xac dinh he so nhan(HeSoNhan) va dong nhan vao thich hop
                for (k = 0; k < m; k++)
                {
                    if (k != j)
                    {
                        HeSoNhan = 0;
                        kt = 0;
                        for (l = 0; l < i; l++)
                            if (M[k][l] != 0)
                                kt = 1;
                        if ((kt == 0) && (M[k][i] != 0))
                        {
                            dong = k;
                            HeSoNhan = (-1) * M[j][i] / M[dong][i];
                            break;
                        }
                    }
                }
                // Neu co HeSoNhan thi se chuyen doi neu khong thi giu nguyen
                if (HeSoNhan != 0)
                {
                    for (k = 0; k < n; k++)
                    {
                        M[j][k] = M[j][k] + HeSoNhan * M[dong][k];
                    }
                    dem++;
                    printf("\nMa tran bien doi lan %d", dem);
                    printf("\n\n");
                    InMt(M, m, n);
                }

            // Truong hop can chuyen M[j][i] ve so 1
            case 1:
                kt = 0;
                for (l = 0; l < i; l++)
                {
                    if (M[j][l] != 0)
                    {
                        kt = 1;
                    }
                }

                HeSoNhan = M[j][i];
                if ((HeSoNhan != 0) && (kt == 0))
                {
                    for (l = 0; l < n; l++)
                    {
                        M[j][l] = M[j][l] / HeSoNhan;
                    }
                    dem++;
                    printf("\nMa tran bien doi lan %d", dem);
                    printf("\n\n");
                    InMt(M, m, n);
                    break;
                }
            }
        }
    }
}

// Bien luan nghiem tu ma tran bac thang rut gon

void BienLuan(double M[100][100], int m, int n)
{

    printf("\nBien luan nghiem tu ma tran bac thang rut gon thu duoc:");
    int i, j;

    // Tim hang cua ma tran he so A
    int rA = 0;
    int tangHangA;
    for (i = 0; i < m; i++)
    {
        // Mac dinh la khong tang hang
        tangHangA = 0;
        for (j = 0; j < n - 1; j++)
        {
            // Chi can mot phan tu trong hang khac 0 la tang hang ngay
            if (M[i][j] != 0)
            {
                tangHangA = 1;
                break;
            }
        }

        rA += tangHangA;
    }
    printf("\n - Hang cua ma tran he so A la rA = %d", rA);

    // Tim hang cua ma tran bo sung M
    int rM = 0;
    int tangHangM;
    for (i = 0; i < m; i++)
    {
        // Mac dinh la khong tang hang
        tangHangM = 0;
        for (j = 0; j < n; j++)
        {
            // Chi can mot phan tu trong hang khac 0 la tang hang ngay
            if ((int)M[i][j] != 0)
            {
                tangHangM = 1;
                break;
            }
        }

        rM += tangHangM;
    }
    printf("\n - Hang cua ma tran bo sung M la rM = %d", rM);

    printf("\n - So an (n-1) la: %d", n - 1);

    // TH1 HPTTT co nghiem duy nhat Khi rA == rM == n-1(so an):
    if (rA == rM && rA == n - 1)
    {
        printf("\n-> He phuong trinh co nghiem duy nhat la:");
        for (i = 0; i < n - 1; i++)
        {
            printf("\n X%d = %lf", i + 1, M[i][n - 1]);
        }

        printf("\n");
    }

    // TH2 HPTTT co vo so nghiem Khi rA == rM < so an:
    if (rA == rM && rA < n - 1)
    {
        printf("\n-> He phuong trinh co vo so nghiem.\n");
        for (i = n - 2; i >= 0; i--)
        {
            printf("\n X%d = ", i + 1);
            printf("%lf", M[i][n - 1]);
            for (j = i + 1; j < n - 1; j++)
                if (M[i][j] != 0)
                {
                    printf("   %lf X%d", -M[i][j], j + 1);
                }
            printf("\n");
        }

        printf("\n");
    }

    // TH2 HPTTT vo nghiem Khi rA < rM:
    if (rA < rM)
    {
        printf("\n-> He phuong trinh vo nghiem.\n");
    }
}
int main()
{
    FILE *fp;
    double M[100][100];
    int m, n, i, j;
    fp = fopen("matran.txt", "r");
    // doc so hang cua ma tran
    fscanf(fp, "%d\n", &m);
    // doc so cot cua ma tran
    fscanf(fp, "%d\n", &n);

    printf("So hang cua ma tran: %d\n", m);
    printf("So cot cua ma tran: %d\n", n);

    // doc noi dung ma tran
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            fscanf(fp, "%lf\n", &M[i][j]);
        }
    }

    fclose(fp);

    // In ma tran ra de kiem tra mang nhap vao
    printf("\nMa tran bo sung M la:\n\n");
    InMt(M, m, n);

    // Dua ma tran ve dang bac thang rut gon
    RutGon(M, m, n);

    printf("\nMa tran bac thang rut gon la:\n\n");
    InMt(M, m, n);
    // Rut ra nghiem tu ma tran bac thang rut gon vua thu duoc sau khi xu li
    BienLuan(M, m, n);
}

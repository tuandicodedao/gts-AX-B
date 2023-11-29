#include <iostream>
#include <fstream>
#include<math.h>
using namespace std;
int n,k;
double a[10000][10001];
 
 //ham nhap
void nhap() {
    ifstream fcin;
    fcin.open("nhap.txt");
    fcin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<=n;j++)fcin>>a[i][j];
    fcin.close();
}

//ham xuat
void xuat() {
    for(int i=0;i<n;i++) {
        for(int j=0;j<=n;j++)cout<<a[i][j]<<" ";
        cout<<endl;
        }
}

//đổi chỗ hàng i và j
void swap (double a[10000][10001],int i,int j) {
    for(int k=0;k<=n;k++) {
        double temp=a[i][k];
        a[i][k]=a[j][k];
        a[j][k]=temp;
    }
}

//chuyển về bậc thang
int gauss(double a[10000][10001]) {
    for(int i=0;i<n;i++) {
        int imax=i;
        for(int j=i+1;j<n;j++) {
            if(fabs(a[j][i])>fabs(a[imax][i])) imax=j;
        }
        if(a[i][imax]==0) {
            //cout<<"det = 0"<<endl;
            return i;
        }
        if(imax!=i)swap(a,imax,i);
        for(int j=i+1;j<n;j++) {
            double h =a[j][i]/a[i][i];
            for(int k=i+1;k<=n;k++) a[j][k]-=a[i][k]*h;
            a[j][i]=0;
        }
        k++;
        cout<<k<<endl;
        xuat();
        cout<<endl;
    }
    return -1;
}

//tính nghiệm
void nghiem (double a[10000][10001]) {
    double x[10000];
    for(int i=n-1;i>=0;i--) {
        x[i]=a[i][n];
        for(int j=i+1;j<n;j++) x[i]-=x[j]*a[i][j];
        x[i]/=a[i][i];
    }
    cout<<"Solution:\n";
    for(int i=0;i<n;i++)
        cout<<"x["<<i<<"] = "<<x[i]<<endl;
}

//kết quả
/*void result (double a[10000][10001]) {
    int m =gauss(a);
    if(m!=-1) {
        if(a[m][n]!=0) cout<<"No solution!";
        else cout<<"Infinite solution!";
        return;
    }
    else nghiem(a);
}*/

void result (double a[10000][10001]) {
    int m =gauss(a);
    if(m!=-1) {
    	for(int i=m;i<n;i++){
    		int count=0; 
    		for(int j=m;j<n;j++) 
    		    if(a[i][j]!=0) count++;
			if(count==0&&a[i][n]!=0) { cout<<"No solution!"; break; }
			else { cout<<"Infinite solution!"; break; }
		}
        return;
    }
    else nghiem(a);
}

int main() {
    nhap();
    gauss(a);
    //xuat();  
    result(a);
    return 0;
}

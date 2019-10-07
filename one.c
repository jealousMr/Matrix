#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 1024*2

double A[N][N];
double B[N][N];
double C[N][N];

void no_change()
{
    int i,j,k;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int k=0;k<N;k++)
                C[i][j]+=A[i][k]*B[k][j];
}
void base_little_change()
{
    int i,j,k;
    double temp;
    for(int k=0;k<N;k++)
        for(int i=0;i<N;i++)
        {
            temp=A[i][k];
            for(int j=0;j<N;j++)
            {
                C[i][j]+=temp*B[k][j];
            }
        }
}
void base_lot_change(int bsize)
{
    int r, c, k, kk, cc;
    double sum;
    int en = bsize * (N/bsize);
 
    for (kk = 0; kk < en; kk += bsize) {
        for (cc = 0; cc < en; cc += bsize) {
            for (r = 0; r < N; r++) {
                for (c = cc; c < cc + bsize; c++) {
                    sum = C[r][c];
                    for (k = kk; k < kk + bsize; k++) {
                         sum += A[r][k]*B[k][c];
                    }
                    C[r][c] = sum;
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            A[i][j]=(i+j)%3;
            B[i][j]=(i*j)%7;
            C[i][j]=0;
        }
    time_t start,end;
    start=clock();
     //no_change();//take sum time: 246.365000 check one number:C[3][3]= 6141.000000
   // base_little_change();//take sum time: 50.360000 check one number:C[3][3]= 6141.000000
    base_lot_change(32);//take sum time: 36.047000 check one number:C[3][3]= 6141.000000
    end=clock();
    printf("take sum time: %f\n",((double)(end-start)/CLOCKS_PER_SEC));
    printf("check one number:C[3][3]= %f\n",C[3][3]);

    return 0;
}

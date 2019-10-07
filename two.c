#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 1024*2

double A[N][N];
double B[N][N];
double C[N][N];


void base_turn()
{
    double temp;
    for(int i=0;i<N;i++)
        for(int j=0;j<i;j++)
        {
            temp=B[i][j];
            B[i][j]=B[j][i];
            B[j][i]=temp;
        }
    
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            for(int k=0;k<N;k++)
                C[i][j]+=A[i][k]*B[j][k];
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
    base_turn();//take sum time: 36.139000  check one number:C[3][3]= 6141.000000
    end=clock();
    printf("take sum time: %f\n",((double)(end-start)/CLOCKS_PER_SEC));
    printf("check one number:C[3][3]= %f\n",C[3][3]);

    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<immintrin.h>
#include<omp.h>
#define N 2*1024

#pragma pack(16)
double A[N][N];
double B[N][N];
double C[N][N];
#pragma pack()

void deal(double **package,int row,int col)
{
    __m256d vec_1,vec_2,vec_3,vec_4,vec_5,vec_6,vec_7,vec_8;
    __m256d a0,a1,b0,b1,b2,b3;
    vec_1=vec_2=vec_3=vec_4=vec_5=vec_6=vec_7=vec_8=_mm256_set1_pd(0);
    double *pb0=A[col],*pb1=A[col+1],*pb2=A[col+2],*pb3=A[col+3],*endb0=pb0+N;
    double *pa0=package[0],*pa1=package[1];
    while (pb0!=endb0)
    {
        a0=_mm256_loadu_pd(pa0);
        a1=_mm256_loadu_pd(pa1);
        b0=_mm256_set1_pd(*(pb0++));
        b1=_mm256_set1_pd(*(pb1++));
        b2=_mm256_set1_pd(*(pb2++));
        b3=_mm256_set1_pd(*(pb3++));
        vec_1=_mm256_fmadd_pd(a0,b0,vec_1);
        vec_2=_mm256_fmadd_pd(a0,b1,vec_2);
        vec_3=_mm256_fmadd_pd(a0,b2,vec_3);
        vec_4=_mm256_fmadd_pd(a0,b3,vec_4);
        vec_5=_mm256_fmadd_pd(a1,b0,vec_5);
        vec_6=_mm256_fmadd_pd(a1,b1,vec_6);
        vec_7=_mm256_fmadd_pd(a1,b2,vec_7);
        vec_8=_mm256_fmadd_pd(a1,b3,vec_8);
        pa0+=4;
        pa1+=4;
    }
    _mm256_storeu_pd(&C[col][row],vec_1);
    _mm256_storeu_pd(&C[col+1][row],vec_2);
    _mm256_storeu_pd(&C[col+2][row],vec_3);
    _mm256_storeu_pd(&C[col+3][row],vec_4);
    _mm256_storeu_pd(&C[col][row+4],vec_5);
    _mm256_storeu_pd(&C[col+1][row+4],vec_6);
    _mm256_storeu_pd(&C[col+2][row+4],vec_7);
    _mm256_storeu_pd(&C[col+3][row+4],vec_8);
    
}


void compute()
{
    double *package[2];
    package[0]=(double*)malloc(sizeof(double)*N*4);
    package[1]=(double*)malloc(sizeof(double)*N*4);

   
#pragma omp parallel for schedule(dynamic)
    for(int j=0;j<N;j+=8)
    {
        int k=0,i=0;
          do{
            package[0][k]=B[i][j];
            package[1][k++]=B[i][j+4];
            package[0][k]=B[i][j+1];
            package[1][k++]=B[i][j+5];
            package[0][k]=B[i][j+2];
            package[1][k++]=B[i][j+6];
            package[0][k]=B[i][j+3];
            package[1][k++]=B[i++][j+7];
          }while(i<N);
        for(int col=0;col<N;col+=4)
            deal(package,j,col);
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
    compute();
    end=clock();
    printf("take sum time: %f\n",((double)(end-start)/CLOCKS_PER_SEC));//7.986000
    printf("check one number:C[3][3]= %f\n",C[3][3]);
 


    return 0;
}
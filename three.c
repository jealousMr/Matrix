#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<immintrin.h>
#define N 1024*2

double A[N][N];
double B[N][N];
double C[N][N];


void height_base_turn()
{
    __m256d t1,t2,sum;
    double temp;
    for(int i=0;i<N;i++)
        for(int j=0;j<i;j++)
        {
            temp=B[i][j];
            B[i][j]=B[j][i];
            B[j][i]=temp;
        }
    double *list=(double*)malloc(sizeof(double)*4);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            C[i][j]=0.0;
            sum=_mm256_setzero_pd();
            for(int k=N-4;k>=0;k=k-4)
            {
                t1=_mm256_loadu_pd(A[i]+k);
                t2=_mm256_loadu_pd(B[j]+k);

                //t1=_mm256_mul_pd(t1,t2);
                //sum=_mm256_add_pd(sum,t1);
                sum=_mm256_fmadd_pd(t1,t2,sum);//此处替代上两条

            }
            //sum=_mm256_hadd_pd(sum,sum);
            //sum=_mm256_hadd_pd(sum,sum);
            //_mm_store_sd(C[i]+j,sum);
            _mm256_storeu_pd(list,sum);//此处替代上3条
            *(C[i]+j)=list[0]+list[1]+list[2]+list[3];
            for(int k=(N%4)-1;k>=0;k--)
                C[i][j]+=A[i][k]*B[j][k];
        }
        free(list);
}

void height_lot_change(int bsize)
{
    double temp;
    for(int i=0;i<N;i++)
        for(int j=0;j<i;j++)
        {
            temp=B[i][j];
            B[i][j]=B[j][i];
            B[j][i]=temp;
        }
    int r,c,k,kk,cc;
    float sum;
    int en=bsize*(N/bsize);
__m256d t1,t2,local_sum;
double local_temp;
double *list=(double *)malloc(sizeof(double)*4);
  for(kk=0;kk<en;kk+=bsize){
        for(cc=0;cc<en;cc+=bsize){
            for(r=0;r<N;r++){
                for(c=cc;c<cc+bsize;c++)
                {
                    local_temp=C[r][c];
                    local_sum=_mm256_setzero_pd();
                    for(k=kk+bsize-4;k>=kk;k=k-4)
                    {
                        t1=_mm256_loadu_pd(A[r]+k);
                        t2=_mm256_loadu_pd(B[c]+k);
                        local_sum=_mm256_fmadd_pd(t1,t2,local_sum);
                    }
                    _mm256_storeu_pd(list,local_sum);
                    *(C[r]+c)=list[0]+list[1]+list[2]+list[3];
                    C[r][c]+=local_temp;
                    for(k=(bsize%4)-1+kk;k>=kk;k--)
                    {
                        C[r][c]+=A[r][k]*B[k][c];
                    }
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
    //height_base_turn();//take sum time: 20.907000
    height_lot_change(32);
    end=clock();
    printf("take sum time: %f\n",((double)(end-start)/CLOCKS_PER_SEC));
    printf("check one number:C[3][3]= %f\n",C[3][3]);





    return 0;
}



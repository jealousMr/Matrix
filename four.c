#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 2*1024


double A[N][N];
double B[N][N];
double C[N][N];

                          
void deal(double **package,int row,int col)
{
    register double t0=0.0,t1=0.0,t2=0.0,t3=0.0,t4=0.0;
    register double t5=0.0,t6=0.0,t7=0.0,t8=0.0,t9=0.0;
    register double t10=0.0,t11=0.0,t12=0.0,t13=0.0,t14=0.0;
    register double t15=0.0;
    double *b0=package[0];
    double *b1=package[1];
    double *b2=package[2];
    double *b3=package[3];
    double *a0=A[col];
    double *a1=A[col+1];
    double *a2=A[col+2];
    double *a3=A[col+3];
    double *end=a0+N;
    do
    {
       t0+=*(b0)**(a0);
       t1+=*(b0)**(a1);
       t2+=*(b0)**(a2);
       t3+=*(b0++)**(a3);

       t4+=*(b1)**(a0);
       t5+=*(b1)**(a1);
       t6+=*(b1)**(a2);
       t7+=*(b1++)**(a3);

       t8+=*(b2)**(a0);
       t9+=*(b2)**(a1);
       t10+=*(b2)**(a2);
       t11+=*(b2++)**(a3);

       t12+=*(b3)**(a0++);
       t13+=*(b3)**(a1++);
       t14+=*(b3)**(a2++);
       t15+=*(b3++)**(a3++);
    } while (a0!=end);

        C[col][row]=t0;
        C[col+1][row]=t1;
        C[col+2][row]=t2;
        C[col+3][row]=t3;
        C[col][row+1]=t4;
        C[col+1][row+1]=t5;
        C[col+2][row+1]=t6;
        C[col+3][row+1]=t7;
        C[col][row+2]=t8;
        C[col+1][row+2]=t9;
        C[col+2][row+2]=t10;
        C[col+3][row+2]=t11;
        C[col][row+3]=t12;
        C[col+1][row+3]=t13;
        C[col+2][row+3]=t14;
        C[col+3][row+3]=t15;
     
                
}


void special()
{
    double *package[4];
    int i,j;
    for(i=0;i<4;i++)
        package[i]=(double*)malloc(N*sizeof(double));
    for(j=0;j<N;j+=4)
    {
        for(i=0;i<N;i++)
        {
            package[0][i]=B[i][j];
            package[1][i]=B[i][j+1];
            package[2][i]=B[i][j+2];
            package[3][i]=B[i][j+3];
        }
        for(i=0;i<N;i+=4)
        {
            deal(package,j,i);
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
            D[i][j]=0;
        }
    time_t start,end;
    start=clock();
    special();
    end=clock();
    printf("take sum time: %f\n",((double)(end-start)/CLOCKS_PER_SEC));
    printf("check one number:C[3][3]= %f\n",C[3][3]);

 


    return 0;
}
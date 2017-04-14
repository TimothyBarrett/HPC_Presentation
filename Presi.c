
#include <stdio.h>
#include <complex.h>
#include "linear_algebra.h"

#define N 4000

int
Gauss(float A[N][N+1])
{
    int i,j,k,n;
    n=N-1;
   float c,sum=0.0;
    
   float x[n];
  
    for(j=1; j<=n; j++) /* loop for the generation of upper triangular matrix*/
    {
     #pragma omp parallel for private(c)  
  
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
               c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];
    /* this loop is for backward substitution*/
    for(i=n-1; i>=1; i--)
    {
        sum=0;
//        for(j=i+1; j<=n; j++)
      #pragma  omp parallel for 
      for(j=1; j<=n; j++){
	if(j>i) 
        {
	    #pragma omp critical	  
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
    }
   
    printf("\nx%d=%f\t",i,x[n]);
    float Fr=A[1][0]*x[1];
    printf("\nThe solution is: Fr= %f \n", Fr);
   
    
    //for(i=1; i<=n; i++)
    //{
    //    printf("\nx%d=%f\t",i,x[i]); /* x1, x2, x3 are the required solutions*/
    //}
    
  return(0);
}

int
main(int argc, char **argv)
{

  double r=0.01;
  double E=200e9;
  double L=1;
  float Le=L/(N-1);
  double f=5e6;
  float A=3.1415*r*r;
  float k=A*E/Le;
  double start=WTime();
 static float K[N][N+1];
  #pragma omp parallel for collapse(2)
  for (int i = 0; i < N; i++) {
    //double F[i]=f;
    for (int j = 0; j < N+1; j++) {
      if (i==0 && j==0){
	K[i][j]=k;
      }
      else if (j==N && i==N-1){
	K[i][j]=f;
      }
      else if (i==j-1 || j==i-1){
	K[i][j]=-k;
      }
      else if (i==j && j==N-1){
	K[i][j]=k;
      }
      else if (i==j){
	K[i][j]=2*k;
      }
      else{
	K[i][j]=0;
      }
    }
  }
  #if 0  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N+1; j++) {
      printf("%f  ", K[i][j]);
    }
    printf("\n");
  }
  #endif  
  
  
  Gauss(K);
  double tot_time=WTime()-start;
  printf("Parallel loop took %g seconds\n", tot_time);
}

/*this function calculates the dot product of 2 matrices using vectors*/

#include<stdio.h>
#include<stdlib.h>

double *prod_mat(double *a,int na,int ma, double *b, int nb, int mb){

   int i,j,r,s,t,u;
   double *c;

   /*suppose that the dimensions of the matrices are correct to multiply*/

   /*Inicialize the product matrix we use calloc for setting all elements to 0*/
   c=(double *)calloc(na*mb, sizeof(double));
   if(c==NULL){
      printf("Error de memoria\n");
      exit(1);
   }

   /*Inicialitzem a 0 la matriu C*/
   for(i=0;i<na;i++){
      for(j=0;j<mb;j++){
         r=f(i,j,mb);
         c[r]=0;
      }   
   }

   /*Fem el producte*/
   for(i=0;i<na;i++){
      for(j=0;j<mb;j++){
          for(r=0;r<ma;r++){
             s=f(i,j,mb);
             t=f(i,r,ma);
             u=f(r,j,mb);
             c[s]=a[t]*b[u]+c[s];
          }
      }
   }

   return c;

}


/*Newton method to find zeros in polinomials*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double horner(double *,int,double);
double *der_pol(double *,int);
int newton(double, double, int, double *,double *,int);

int main(void){

   int n,maxIter,i,t;
   double x0,tol,*sol,*p;

   /*Solution vector*/
   sol=(double *)malloc(sizeof(double));
   if(sol==NULL){
      printf("Error de memoria\n");
      exit(1);
   }


   printf("Insert polinomial degree\n");
   scanf("%d",&n);

   /*Inicialitzem el polinomi p*/
   p=(double *)malloc((n+1)*sizeof(double));
   if(p==NULL){
      printf("Error, out of memory\n");
      exit(1);
   }


   printf("Insert the polinomial, from lesser to higher\n");
   for(i=0;i<=n;i++)
      scanf("%le",&p[i]);

   printf("Insert the tolerated errror\n");
   scanf("%le",&tol);

   printf("Insert the maximum number of iterations\n");
   scanf("%d",&maxIter);

   printf("Insert initial approximation\n");
   scanf("%le",&x0);

   t=newton(x0,tol,maxIter,sol,p,n);

   switch(t){
      case 1:
         printf("maximum number of iterations reached, no solution\n");
         break;
      case 2:
         printf("Derivative equals 0 at some point\n");
         break;
      case 0:
         printf("Soultion reached. Sol=%le\n",*sol);
         break;
   }

   free(sol);
   free(p);

   return 0;

}


double horner(double *p,int n, double z){

   int i;
   double h=0;

   for(i=n;i>=0;i=i-1){
      h=h*z+p[i];
   }

   return h;

}


double *der_pol(double *p,int n){

   int i;
   double *d;

   d=(double *)malloc((n)*sizeof(double));
   if(d==NULL){
      printf("Error, out of memory\n");
      exit(1);
   }

   for(i=0;i<n;i++)
      d[i]=p[i+1]*(i+1);

   return d;

}


int newton(double x0, double tol, int maxIter, double *sol, double *p, int n){

   int i;
   double x1,*q;

   x1=x0;


   for(i=0;(i<=maxIter)&&((fabs(x1-x0)>tol)||i==0)&&((fabs(x1)>tol)||i==0);i++){

      x0=x1;
      q=der_pol(p,n);
      if(fabs(horner(q,n-1,x0))<=tol){
         free(q);
         return 2;
      }

      x1=x0-horner(p,n,x0)/horner(q,n-1,x0);
   }


   if(i==maxIter+1){
      free(q);
      return 1;
   }

   *sol=x1;

   free(q);

   return 0;

}

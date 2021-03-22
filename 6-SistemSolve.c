/*Solution system of equations using Gauss method using file as an input and output*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void substitucio(double **,double *,int,char []);
int gaussNoPiv(double **,int);

int main(void){

   double *b,**ab,**a,dada;
   char nom1[50],nom2[50];
   int i,n,j,d;
   FILE *ent;

   printf("Insert input filename\n");
   scanf("%s",nom1);

   printf("Insert output filename\n");
   scanf("%s",nom2);

   ent=fopen(nom1,"r");
   if(ent==NULL){
      printf("Error reading the file\n");
      exit(1);
   }

   fscanf(ent,"%d",&n);

   /*Memory allocation for a triangular matrix, b free coeficients, ab whole matrix*/

   b=(double *)malloc(n*sizeof(double));
   if(b==NULL){
      printf("Out of memory\n");
      exit(1);
   }

   ab=(double **)malloc(n*sizeof(double *));
   if(ab==NULL){
      printf("Out of memory\n");
      exit(1);
   }
   for(i=0;i<n;i++){
      ab[i]=(double *)malloc((n+1)*sizeof(double));
      if(ab[i]==NULL){
         printf("Out of memory\n");
         exit(1);
      }
   }

   a=(double **)malloc(n*sizeof(double *));
   if(a==NULL){
      printf("Out of memory\n");
      exit(1);
   }
   for(i=0;i<n;i++){
      a[i]=(double *)malloc((n-i)*sizeof(double));
      if(a[i]==NULL){
         printf("Out of memory\n");
         exit(1);
      }
   }


   /*Read the data*/

   while(fscanf(ent,"%d %d %le",&i,&j,&dada)!=EOF){
      ab[i][j]=dada;
      if(j==n)
         b[i]=dada;
      else
         ab[i][j]=dada;
   }


   d=gaussNoPiv(ab,n);
   if(d==1){
      printf("Not finished\n");
      exit(1);
   }

   for(i=0;i<n;i++)
      b[i]=ab[i][n];

   if(fabs(ab[n-1][n-1])<10e-8){
      printf("Not finished\n");
      exit(1);
   }

   for(i=0;i<n;i++){
      for(j=0;j<n;j++)
         a[i][j]=ab[i][i+j];
   }


   substitucio(a,b,n,nom2);

   for(i=0;i<n;i++)
      free(ab[i]);
   free(a);
   free(ab);
   free(b);
   fclose(ent);

   return 0;

}


int gaussNoPiv(double **ab,int n){

   int k,i,j;
   double m;

   for(k=0;k<n-1;k++){
      for(i=k+1;i<n;i++){
         if(fabs(ab[k][k])<10e-8)
            return 1;
         m=ab[i][k]/ab[k][k];
         for(j=0;j<=n;j++)
            ab[i][j]=ab[i][j]-m*ab[k][j];
      }
   }

   return 0;

}


void substitucio(double **matU,double *c,int n,char nom[]){

   int i,r;
   double z=0;
   FILE *sor;

   sor=fopen(nom,"w");
   if(sor==NULL){
      printf("Error opening the file\n");
      exit(1);
   }

   for(i=n-1;i>=0;i=i-1){
      z=c[i];
      for(r=1;r<n-i;r++){
         z=z-matU[i][r]*c[r+i];
      }
      c[i]=z/matU[i][0];
   }

   for(i=0;i<n;i++)
      fprintf(sor,"%le  ",c[i]);

   fclose(sor);

   return;
}

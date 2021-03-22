/*Programa 15*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define DIM 50

/*Funció principal: llegeix el grau d'un polinomi i els seus coeficients. El grau ha de ser major o igual a dos. Després calcula un extrem del polinomi*/

double horner(double*, int, double);
double *der_pol(double*, int);
int newton(double, double, int, double*, double*, int);
int max_min_pol(double, double, int, double*, double*, int);

int main(void){
	int k, i, maxIter, indicador;
	double *pol, *sol, x0, tol, polinomi[DIM];

	do{
                printf("Grau del polinomi?\n");
                scanf("%d", &k);
        }while(k<2||k>DIM-1);

	/*Inicialitzem pol i sol*/

        pol=(double *)malloc((k+1)*sizeof(double));
        if(pol==NULL){
                printf("Error de memoria\n");
                exit(1);
        }
	sol=(double *)malloc(sizeof(double));
        if(sol==NULL){
                printf("Error de memoria\n");
                exit(1);
        }

	printf("Coeficients del polinomi?\ncomença pel terme independent i acaba amb el coeficient de la x de major grau\n");
	for(i=0;i<=k;i++){ 
		scanf("%le", &polinomi[i]);
		*(pol+i) = polinomi[i];
	}
	if(pol[k]==0){
		printf("Trapella, aquest polinomi no és de grau %d, ara et quedes sense programa\n", k);
		return 4;
	}
	
	printf("Dona'm un nombre real:\n");
	scanf("%le", &x0);
	printf("Maxim nombre d'interacions?\n");
	scanf("%d", &maxIter);
	printf("Tolerància?\n");
	scanf("%le",&tol);

	indicador = max_min_pol(x0, tol, maxIter, sol, pol, k);
	switch(indicador){
		case 1:
         		printf("Màxim en x = %20.12le\n\n", *sol);

         		break;
      		case 2:
         		printf("Mínim en x = %20.12le\n\n", *sol);
        		break;
      		case 3:
         		printf("Hem tingut un problema en el procés o no podem decidir si és un màxim o un mínim\n\n");
        		break;
  		 }

	free(pol);
	free(sol);	

	return 0;
}


/*Funció que calcula el màxim o mínim local d'un polinomi*/

double horner(double*, int, double);
double *der_pol(double*, int);
int newton(double, double, int, double*, double*, int);

int max_min_pol(double x0, double tol, int maxIter, double *punt, double *p, int n){
	
	int indicador, retornNewton, m;	
	double *polDer, *polDer2;
	
	polDer=(double *)malloc(n*sizeof(double));
        if(p==NULL){
                printf("Error de memoria\n");
                exit(1);
        }	

	polDer2=(double *)malloc((n-1)*sizeof(double));
        if(p==NULL){
                printf("Error de memoria\n");
                exit(1);
        }	

	/*Derivem el nostre polinomi*/
	polDer = der_pol(p,n);

	/*Busquem zeros en el nostre polinomi derivat*/
	retornNewton = newton(x0, tol, maxIter, punt, polDer, n);
	
	if(retornNewton !=0){
		free(polDer);
		free(polDer2);
		return 3;
	}

	m = n-1;
	polDer2 = der_pol(polDer, m);

	if(horner(polDer2, m, *punt)>0){
		indicador = 2;
	}else{
		if(horner(polDer2, m, *punt)<0){
			indicador = 1;
		}else{
			indicador = 3;
		}
	}

	free(polDer);
	free(polDer2);

	return indicador;

}

/*Funció Newton. Segur que es pot fer més senzilla*/

double horner(double*, int, double);
double *der_pol(double*, int);

int newton(double x0, double tol, int maxIter, double *sol, double *p, int n){
	int i, m;
	double x1=0;
	double *pol2;
	m = n-1;	

	pol2=(double *)malloc((n-1)*sizeof(double));
        if(p==NULL){
                printf("Error de memoria\n");
                exit(1);
        }
	
	pol2 = der_pol(p, n);

	if(fabs(horner(pol2, m,x0))>tol){
		x1 = x0 - horner(p, n, x0)/horner(pol2, m, x0);	
	}
	i=1;
	while(fabs(x1-x0)<tol){
		x0 = x1;
		if(fabs(horner(pol2, m, x1))<tol){
			free(pol2);
			return 2;
		}
		x1 = x0 - horner(p, n, x0)/horner(pol2, m, x0);
		i++; 
		if(i>=maxIter){
			free(pol2);
			return 1;
		}	
	}
	
	free(pol2);
	*sol = x1;
	return 0;	
}

/*Funció Horner. És la funció de la Júlia!*/

double horner(double *p,int n, double z){
   int i;
   double h=0;

   for(i=n;i>=0;i=i-1){
      h=h*z+p[i];
   }
   return h;
}

/*Funció per derivar, de la Júlia també!*/

double *der_pol(double *p,int n){

   int i;
   double *d;

   d=(double *)malloc((n)*sizeof(double));
   if(d==NULL){
      printf("Error de memoria\n");
      exit(1);
   }

   for(i=0;i<n;i++)
      d[i]=p[i+1]*(i+1);

   return d;
}

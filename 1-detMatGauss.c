/* Function that calculates the determinant of a matrix using gauss reduction method*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gaussPivot(double **,int);
int pivot(double **,int,int);

int main(void){
	FILE *eF;
	int dim,gauss,j,i;
	double **A,det=1;
	char entrada[50];
	
	do{
		printf("Input file: ");
		scanf(" %s",entrada);
		eF=fopen(entrada,"r");
	} while(eF==NULL);
	/* Read dimension and matrix*/
	fscanf(eF," %d",&dim);
	A=(double**)malloc(dim*sizeof(double*));
	for(i=0;i<dim;i++){
		A[i]=(double*)calloc(dim,sizeof(double));
		if(A[i]==NULL){ printf("Out of memory\n"); exit(-1);}
	}
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			fscanf(eF," %lf",&A[i][j]);
		}
	}
	printf("Matrix A.");
	for(i=0;i<dim;i++){
		printf("\n");
		for(j=0;j<dim;j++){
			printf("%-lg ",A[i][j]);
		}
	}
	/* Reduce the matrix*/
	gauss=gaussPivot(A,dim);
	if(gauss==1) printf("\n Reduction failed\n");
	printf("\n Matrix A has been reduced.");
	for(i=0;i<dim;i++){
		printf("\n");
		for(j=0;j<dim;j++){
			printf("%-lg ",A[i][j]);
		}
	}
	/* The determinant of a triangular matrix is the product of its diagonal elements */
	for(i=0;i<dim;i++){
		det=det*A[i][i];
	}
	printf("\nDet(A)= %lf\n",det);
	return 0;
}


int gaussPivot(double **A,int dim){
	int i,j,k,fin=0,piv;
	double lambda,*aux;
	/*Apply reduction method*/
	for(i=0;i<(dim-1);i++){
		
		piv=pivot(A,i,dim);
		aux=A[piv];
		A[piv]=A[i];
		A[i]=aux;
		/*Apply Gauss*/
		if(A[i][i]==0){ printf("Error, divide by 0\n"); fin=1; }
		else{
			for(j=i+1;j<dim;j++){
				if(A[j][i]!=0){
					lambda=A[j][i]/A[i][i];
					for(k=i;k<=dim;k++){
						A[j][k]=A[j][k] - (lambda*A[i][k]);
					}
				}
			}
		}
	}
return fin;
}

int pivot(double **A,int k,int dim){
	int maxElement,maxFila,i;
	maxElement=fabs(A[k][k]);
	maxFila=k;
	for(i=k;i<dim;i++){
		if(fabs(A[i][k])>maxElement){
			maxElement=fabs(A[i][k]);
			maxFila=i;
		}
	}
	return maxFila;
}


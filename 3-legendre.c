
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double legendreRecursiu(double y, int n);
int main(void){
	int n;
	double  y, valor;
	do{
		printf("Quina n vols?\n");
		scanf("%d", &n);
	}while(n<0);
	printf("En quin punt vols calcular el valor de Pn?\n");
	scanf("%le", &y);

	valor=legendreRecursiu(y,n);

	printf("El valor de P %d en el punt %10.3le és %10.3le\n", n, y, valor);
	return 0;
}

double legendreRecursiu(double y, int n){
		
		double valor;
		
		/*Simple cases*/
		if(n==0){
			valor=0;
		 }else if(n==1){
			valor=y;
		}else{
			valor=((2*n+1)*y*legendreRecursiu(y, n-1))/n - (n*legendreRecursiu(y, n-2))/n;	

		}

	return valor;
}	


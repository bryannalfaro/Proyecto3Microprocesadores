/*
*	Proyecto 3 ejercicio D
*------------------------------------
*Realiza en ejercicio D del proyecto
*numero 3 de dos maneras distintas 
* y muestra el resultado al final
*------------------------------------
*Raul Jimenez 19017
*Donaldo Garcia 19683
*Bryan Alfaro 19372
*Oscar Saravia 19322
*Diego Arredondo 19422
*-----------------------------------*/
#include <omp.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <ctime>



int main(){
	
	#define n 10000
	int hilos;
	double convergencia=0;
	double expresion=0;
	double valor=0;
	double convergencia2=0;
	double expresion2=0;
	double valor2=0;
	
	printf("Bienvenido al programa de calculo de serie\n");
	printf("Se calculara la serie de e-(1+1/n^2)^n\n");
	
	//Se permite especificar los hilos que desea
	printf("----------------------------------------------\n");
	printf("Porfavor ingrese la cantidad de hilos que desea para el programa: (menor a 250)\n");
	
	scanf("%d",&hilos);
	
	if(hilos>250){
		printf("El numero de hilos debe ser menor a 250. Intente de nuevo.\n");
		return(1);
		}
		
	
	//Limite cuando la serie tiende a infinito
	printf("Teorema de la divergencia: \n");
	
	expresion = exp(1)-pow(1+(1/pow(n,2)),n);
	
	printf("Valor del limite: %lf\n",expresion);
	if(expresion!=0)
	{
		printf("Por el teorema la serie diverge\n");
	}
	else
	{
		printf("La serie es potencialmente convergente\n");
	}
	
	printf("----------------------------------------------\n");
	printf("EVALUANDO LA SERIE...........\n");
	
	//parte paralela para obtener las sumatorias
	#pragma omp parallel for num_threads(hilos)
		for(int i =1; i<700000; i++)
		{
			 valor = exp(1)-pow(1+(1/pow(i,2)),i);
			
			#pragma omp atomic 
				convergencia+=valor;
				
		}
		
	#pragma omp parallel for num_threads(hilos)
		for(int i =1; i<710000; i++)
		{
			
			 valor2 = exp(1)-pow(1+(1/pow(i,2)),i);
			
			#pragma omp atomic 
				convergencia2+=valor2;
				
		}	
	
	
	printf("El valor de la serie con n=700,000 es: %lf \n", convergencia);
	printf("El valor de la serie con n=710,000 es: %lf \n", convergencia2);
	if(convergencia2!=convergencia)
	{
		printf("La serie diverge\n");
	}
		
	else
	{
		printf("El valor de convergencia aproximado es: %lf \n", convergencia);
	}
	
	return 0;	
	
	}

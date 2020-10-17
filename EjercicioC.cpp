/*
*	Proyecto 3 ejercicio C
*------------------------------------
*Realiza el ejercicio C del proyecto
*numero 3 de dos maneras distintas 
* y muestra el resultado al final
*------------------------------------
*Raul Jimenez 19017
*Donaldo Garcia 19683
*Bryann Alfaro 19372
*Oscar Saravia 19322
*Diego Arreondo 19422
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
	int convergenciaEntera=0;
	double expresion=0;
	double valor=0;
	
	double convergencia2=0;
	int convergenciaEntera2=0;
	double expresion2=0;
	double valor2=0;
	
	printf("Bienvenido al programa de calculo de serie\n");
	printf("Se calculara la serie de (1-1/raiz(n))^n\n");
	
	printf("----------------------------------------------\n");
	printf("Porfavor ingrese la cantidad de hilos que desea para el programa: (menor a 250)\n");
	
	scanf("%d",&hilos);
	
	if(hilos>250){
		printf("El numero de hilos debe ser menor a 250. Intente de nuevo.\n");
		return(1);
		}
		
	
	//Limite cuando la serie tiende a infinito
	printf("Teorema de la divergencia: \n");
	
	expresion = 1-(1/sqrt(n));
	
	valor = pow(round(expresion),n);
	printf("Valor del limite: %lf\n",valor);
	if(valor!=0)
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
			 
			 valor = pow(1-(1/sqrt(i)),i);
			
			#pragma omp atomic 
				convergencia+=valor;
				
		}
		
	#pragma omp parallel for num_threads(hilos)
		for(int i =1; i<710000; i++)
		{
			
			 
			 valor2 = pow(1-(1/sqrt(i)),i);
			
			#pragma omp atomic 
				convergencia2+=valor2;
				
		}	
	
	
	convergenciaEntera = round(convergencia);
	convergenciaEntera2 = round(convergencia2);
	printf("El valor de la serie con n = 700,000 es: %lf \n", convergencia);
	printf("El valor de la serie con n = 710,000 es: %lf \n", convergencia2);
	if(convergencia2!=convergencia)
	{
		printf("La serie diverge\n");
	}
		
	else
	{
		printf("El valor de convergencia aproximado es: %lf \n", convergencia);
		printf("El valor de convergencia entero es: %d \n", convergenciaEntera);
	}
	
	return 0;	
	
	}

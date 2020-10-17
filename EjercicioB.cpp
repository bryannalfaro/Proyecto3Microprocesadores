/*
*	Proyecto 2 ejercicio B
*------------------------------------
*Realiza el ejercicio B del proyecto
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

#define n 250

int main()
{
	//Informacion de lo que va a hacer le programa
	printf("A continuacion se va ha resolver la sumatoria de 1 hasta infinito hasta infinito de la ecuacion  1/(n*(n+1)) \n");
	
	//variables para convergencia
	double convergencia = 0;
	int convergenciaEntera = 0;
	int valorLimite = 0;
	
	//valor con limites
	for(int i = 1; i < 10000; i+=1000)
	{
		//se utiliza la ecuacion obtenida con limites
		double num = i/(i+2.f);
				
		//se muestran los cambios en cada corrida del limite
		printf("Con i = %d Valor limite es  => %lf \n", i, num);
		//se hace una pausa para ver la diferencia entre datos
		sleep(1);
	}
	
	//parte paralela para obtener las sumatorias
	#pragma omp parallel for num_threads(n)
		for(int i =1; i<598461; i++)
		{
			//cada hilo realiza la operacion dada
			double valor = 1.f/(i*(i+1.f));
			
			//cada hilo almacena el dato en la variable convergencia
			#pragma omp atomic 
				convergencia+=valor; 
		}	
	
	//se redondea la la sumatoria 
	convergenciaEntera = round(convergencia);
	//Se muestran los valores originales y redondeados
	printf("El valor de convergencia aproximado es: %lf \n", convergencia);
	printf("El valor de convergencia entero es: %d \n", convergenciaEntera);
	
	return 0;
}

/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3056-10 Programación de microprocesadores
* Autor: Oscar Saravia
*
* Euler.cpp
* Fecha: 18/10/2020
* --------------------------------------------------------*/
// omp_init_lock.cpp
// compile with: /openmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;


// Metodo para calcular factorial
double fact(int n) {
   if ((n==0)||(n==1))
   return 1;
   else
   return n*fact(n-1);
}

// Inicizalizacion de variables
omp_lock_t lck;
double resultado = 0;
double   valor = 0;

int main() {

   omp_init_lock(&lck);

   #pragma omp parallel for
   for (int i = 0; i < 13; i++)
   {
       omp_set_lock(&lck);
       valor = 1/(fact(i));
       resultado = resultado + valor;
       omp_unset_lock(&lck);

   }


    cout <<"El valor de e es aproximadamente: " << setprecision(10)<< resultado<<"\n";
   omp_destroy_lock(&lck);

   return 0;
}

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <vector>

using namespace std;

/*
    5        3         4         5
  3   2    2   1     3   1     3   2        <- función fitnes/aptitud
101010101 11000111 110101110 110100101

    5                            5
101010101                    110100101      cruce / mutación


1010-00101                  1101-10101
101000101                   110110101 <- sin mutar

|    5    |                       7
|  3   2  |                     4   3
|101100101|                   110110001 <- mutado


------- SEGUNDA GENERACIÓN ----------
    5         4         5          7
  3   2     3   1     3   2      4   3     <- nuevos candidatos
101010101 110101110 110100101  110110001

101010101                      110110001

   7                             5
 3    4                         4   1
101010000                      110111101


    5         5          7         7
  3   2     3   2      4   3     3   4             <- nuevos candidatos
101010101 110100101  110110001 101010000

-------------
    9
  5   4
111110000
-------------

*/
const int TAM = 11;

char * generarIndividuo(int tam = TAM){
    char * individuo = new char[tam];

    for (int idx = 0; idx < tam; idx++){
        int valor = rand() % 10;
        if (valor > 5){
            individuo[idx] = '0';
        } else {
            individuo[idx] = '1';
        }
    }

    return individuo;
}

void mostrarIndividuo(char * individuo, int tam = TAM){
    for(int idx = 0; idx < tam; idx++){
        cout << individuo[idx];
    }
    cout << endl;
}

/* 010101  01111 */
int funcionAptitud(char * individuo, int tam){
    int inicio = (tam / 2) + 1;
    int contarUnos = 0;
    int contarCeros = 0;
    for(int idx = 0; idx < inicio; idx++){
        if (individuo[idx] == '1')
            contarUnos++;
    }
    for(int idx = inicio; idx < tam; idx++){
        if (individuo[idx] == '0')
            contarCeros++;
    }

    return contarUnos + contarCeros;
}

bool operacionCruce(char * individuo1, char * individuo2, int tam = TAM){
   // solo será una partición
   int mitad = (tam / 2) + 1; // pseudo-mitad

   char * primeraParte1 = new char[mitad];
   // guardamos la cabeza del primero
   for (int idx = 0; idx < mitad; idx++){
       primeraParte1[idx] = individuo1[idx];
   }
   // pasamos la cabeza del segundo al primero
   for (int idx = 0; idx < mitad; idx++){
       individuo1[idx] = individuo2[idx];
   }
   // le ponemos la cabeza del individuo uno en dos
   for (int idx = 0; idx < mitad; idx++){
       individuo2[idx] = primeraParte1[idx];
   }
   return true;
}

bool operacionMutacion(char * individuo1, int tam = TAM){
    int idx = rand() % tam;
    if (individuo1[idx] == '1'){
        individuo1[idx] = '0';
    } else {
        individuo1[idx] = '1';
    }
    return true;
}

int main(){
    srand(time(NULL));

    const int cantidadIndividuos = 10;
    // cantidad de bits 11 <-- TAM
    // 6 -> 1 >  11
    // 5 -> 0 >




    return 0;
}

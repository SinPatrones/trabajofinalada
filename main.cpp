#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

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

unsigned long long binarioADecimal(char *individuo, int tam) {
    unsigned long long decimal = 0;
    int multiplicador = 1;
    char caracterActual;
    for (int i = tam - 1; i >= 0; i--) {
        caracterActual = individuo[i];
        if (caracterActual == '1') {
            decimal += multiplicador;
        }
        multiplicador = multiplicador * 2;
    }

    return decimal;
}

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
}

/* 010101  01111 */
long long funcionAptitud(char * individuo, int tam = TAM){
    // conversión de binario a decimal
    unsigned long long numeroX = binarioADecimal(individuo, tam);
    // ecuación
    const  long long resultado = (numeroX * numeroX) + (numeroX * 2) - 10;

    return resultado;
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

void mostrarTodosLosCandidatos(vector<pair<char *,int>> candidatos){
    for(auto & candidato: candidatos){
        mostrarIndividuo(candidato.first);
        cout << "->" << candidato.second << " ";
    }
    cout << endl;
}

void asignarCalificacion(vector<pair<char *,int>> & candidatos){
    for(auto & candidato: candidatos){
        candidato.second = funcionAptitud(candidato.first);
    }
}

int main(){
    srand(time(NULL));

    // el mejor candidado mide 11

    const int cantidadIndividuos = 10;
    // cantidad de bits 11 <-- TAM
    // 6 -> 1 >  11
    // 5 -> 0 >
         //     candidato, aptitud
    vector<pair<char *   ,   int    >> candidatos;

    for (int idx = 0; idx < cantidadIndividuos; idx++){
        pair<char *, int> candidato(generarIndividuo(), 0);
        candidatos.push_back(candidato);
    }

    mostrarTodosLosCandidatos(candidatos);
    asignarCalificacion(candidatos);
    mostrarTodosLosCandidatos(candidatos);

    /* condiciones
     1.- Definamos cantidad de generaciones
     2.- Encontremos o aproximemos a la respuesta
     3.- DETENGAMOS
     4.- ERROR
    */

    long long respuestaOptima = 50;

    sort(candidatos.begin(), candidatos.end(), [](pair<char *,int> candidato1, pair<char *,int> candidato2){
        return candidato1.second > candidato2.second;
    });

    mostrarTodosLosCandidatos(candidatos);

    int generacion = 1;

    while(true){
        // Son los dos mejores
        char * candidato1 = new char[TAM];
        char * candidato2 = new char[TAM];

        candidato1 = candidatos[0].first;
        candidato2 = candidatos[1].first;

        operacionMutacion(candidato1);
        operacionMutacion(candidato2);

        operacionCruce(candidato1, candidato2);

        // botando al menos optimo
        candidatos.pop_back();
        // botando a los padres antiguos
        if (funcionAptitud(candidato1) > funcionAptitud(candidato2)){
            pair<char*,int> nuevoCandidato(candidato1, funcionAptitud(candidato1));
            candidatos.push_back(nuevoCandidato);
        } else {
            pair<char*,int> nuevoCandidato(candidato2, funcionAptitud(candidato2));
            candidatos.push_back(nuevoCandidato);
        }

        //asignarCalificacion(candidatos);
        sort(candidatos.begin(), candidatos.end(), [](pair<char *,int> candidato1, pair<char *,int> candidato2){
            return candidato1.second > candidato2.second;
        });

        // VALOR OPTIMO --> TOTAL: 100;
        // UMBRAL: -10 a 10
        if (candidatos[0].second == 1000){
            break;
        }
        cout << "GENERACION " << ++generacion << endl;
    }

    cout << "Mostrando Solución" << endl;
    mostrarTodosLosCandidatos(candidatos);

    return 0;
}

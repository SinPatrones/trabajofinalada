#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>

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

char * generarIndividuo(int tam = 11){
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

void mostrarIndividuo(char * individuo, int tam){
    for(int idx = 0; idx < tam; idx++){
        cout << individuo[idx];
    }
    cout << endl;
}


int main(){
    srand(time(NULL));

    mostrarIndividuo(generarIndividuo(), 11);

    return 0;
}

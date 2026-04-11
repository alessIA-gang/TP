#include <iostream>
#include <iomanip>
#include "biblioteca/funcionesAdicionales.h"
using namespace std;

int main(int argc,char** argv) {
    int diaInicial, mesInicial, añoInicial, diaFinal, mesFinal,añoFinal;
    cout.precision(2);
    cout<<fixed;
    leerFechasYMostrarTitulos(diaInicial, mesInicial, añoInicial,
                              diaFinal, mesFinal,añoFinal);
    emitirReporteCalculandoInfracciones(diaInicial, mesInicial, añoInicial,
                              diaFinal, mesFinal,añoFinal);
    return 0;
}
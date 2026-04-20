/* 
 * Archivo:   main.cpp
 * Autor: Alessia Isabella Gastello Anglas
 * 
 * ==========================================================================
 * descprición
 * ==========================================================================
 */

#include <iostream>
#include <iomanip>
#include "Bibliotecas/funciones.h"
using namespace std;

int main(int argc, char **argv) {
    procesarArchivos("ArchivosDeReporte/reporte.txt", "ArchivosDeDatos/InfraccionesCometidas.txt",
                  "ArchivosDeDatos/InfraccionesDeTransito.txt");


    return 0;
}

//
// Created by isabe on 19/04/2026.
//

#ifndef SOLU_FUNCIONES_H
#define SOLU_FUNCIONES_H
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void procesarArchivos(const char *nomRep, const char *nomInf, const char *nomTran);

void imprimirCabecera(ofstream &rep);

void emitirReporte(ofstream &rep, ifstream &inf, ifstream &tran);

void leerImprimir(ifstream &inf, ofstream &rep, char delim);

void imprimeSubtitulos(ofstream &rep);

void procesarInfracciones(ofstream &rep, ifstream &inf, ifstream &tran, int &cantLeve, int &cantGrav, int &cantMuyGrave,
                          double &totalLeve, double &totalGrave, double &totalMuyGrave);

#endif //SOLU_FUNCIONES_H

//
// Created by aml on 1/09/2025.
//

#ifndef FUNCIONESADICIONALES_H
#define FUNCIONESADICIONALES_H

void leerFechasYMostrarTitulos(int &diaInicial, int &mesInicial, int &añoInicial,
                               int &diaFinal, int &mesFinal,int &añoFinal);
void emitirReporteCalculandoInfracciones(int diaInicial, int mesInicial, int añoInicial,
                                         int diaFinal, int mesFinal,int añoFinal);

void leerFecha(int &diaInicial,int &mesInicial, int &añoInicial);
void imprimirLinea(char car,int n);
void leerImprimirTexto(char delimitador);
void colocarSubtitulos();
int ddmmaa_fecha(int dia, int mes,int año);
void procesarInfracciones(int fechaIni,int fechaFin,int dni,double &totalRecaudado);
void imprimirFechaHora(int dia,int mes,int año,int hora,int min,int seg);
void imprimirMontos(double multa,double incrTipo,double incrFecha, double incrHora,double totalPagar);
void imprimeTipo(char letraPlaca);
void imprimeGravedad(char gravedad);
double calcularMulta(char gravedad);
double calcularIncrementoTipo(double multa, char letraPlaca);
double calcularIncrementoFecha(double multa,int fechaIni, int fechaFin, int fechaInfraccion);
double calcularIncrementoHora(double multa, int hora, int min, int seg);
int hhmmss_hora(int hora, int min,int seg);
void evaluarMayorPago(double totalRecaudado, int dni, int i,int &mayorDNI, double &mayorRecaudacion, int &mayorCompañia);
void evaluarMenorPago(double totalRecaudado,int dni, int i,int &menorDNI, double &menorRecaudacion, int &menorCompañia);
void imprimeConclusiones(int menorDNI, int mayorDNI, double menorRecaudacion, double mayorRecaudacion,
                        int menorcompañia, int mayorCompañia);

#endif //FUNCIONESADICIONALES_H

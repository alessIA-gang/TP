//
// Created by aml on 1/09/2025.
//

#include "funcionesAdicionales.h"

#include <iomanip>
#include <iostream>
using namespace std;

void leerFechasYMostrarTitulos(int &diaInicial, int &mesInicial, int &añoInicial,
                               int &diaFinal, int &mesFinal, int &añoFinal) {
    leerFecha(diaInicial, mesInicial, añoInicial);
    leerFecha(diaFinal, mesFinal, añoFinal);
    cout << setw(82) << "MINISTERIO DE TRANSPORTE" << endl;
    cout << setw(86) << "MULTAS IMPUESTAS A LAS COMPAÑIAS" << endl;
    cout << setw(26) << "RANGO DE FECHAS A CONSIDERAR: DEL ";
    cout << setfill('0') << setw(2) << diaInicial << '/' << setw(2) << mesInicial << '/' << setw(4) << añoInicial <<
            " AL " << setw(2) << diaFinal << '/' << setw(2) << mesFinal << '/' << setw(4) << añoFinal << endl;
    imprimirLinea('=', 140);
}

void leerFecha(int &diaInicial, int &mesInicial, int &añoInicial) {
    char c;
    cin >> diaInicial >> c >> mesInicial >> c >> añoInicial;
}

void imprimirLinea(char car, int n) {
    for (int i = 0; i < n; i++) cout.put(car);
    {
        cout << endl;
    }
}

void emitirReporteCalculandoInfracciones(int diaInicial, int mesInicial, int añoInicial,
                                         int diaFinal, int mesFinal, int añoFinal) {
    int dni, fechaIni, fechaFin, i = 1, mayorDNI, menorDNI, mayorCompañia, menorCompañia;
    double totalRecaudado, mayorRecaudacion = 0, menorRecaudacion = 999999, totalDefinitivo = 0;
    while (true) {
        cin >> dni;
        if (cin.eof())break;
        cout << "COMPANIA No. " << i << endl;
        cout << "REPRESENTANTE LEGAL: ";
        leerImprimirTexto(' ');
        cout << "DNI: " << dni << endl;
        imprimirLinea('-', 140);
        colocarSubtitulos(); //
        fechaIni = ddmmaa_fecha(diaInicial, mesInicial, añoInicial);
        fechaFin = ddmmaa_fecha(diaFinal, mesFinal, añoFinal);
        procesarInfracciones(fechaIni, fechaFin, dni, totalRecaudado);

        imprimirLinea('=', 140);

        evaluarMenorPago(totalRecaudado, dni, i, menorDNI, menorRecaudacion,
                         menorCompañia);
        evaluarMayorPago(totalRecaudado, dni, i, mayorDNI, mayorRecaudacion,
                         mayorCompañia);
        totalDefinitivo += totalRecaudado;
        i++;
    }
    cout << "TOTAL RECAUDADO POR INFRACCIONES: " << totalDefinitivo << endl;
    imprimirLinea('=', 140);
    cout << endl;
    imprimeConclusiones(menorDNI, mayorDNI, menorRecaudacion, mayorRecaudacion,
                        menorCompañia, mayorCompañia);
}

void leerImprimirTexto(char delimitador) {
    char c;
    int numCar = 0, numBlancos;
    cin >> ws;
    while (true) {
        c = cin.get();
        if (c == delimitador)break;
        if (c == '/' or c == '-') c = ' ';
        if (c >= 'a' and c <= 'z') c -= 'a' - 'A';// 'a' - 'A' viene de la tabla ASCII, para cambiar el caracter a mayúscula. 
      //En la tabla ASCII la distancia entre la misma letra en minúscula y mayúscula es la misma, por eso sirve esta resta.
        cout.put(c);
        numCar++;
    }
    numBlancos = 42 - numCar;//le da formato a un espacio determinado para calzar el nombre
    for (int i = 0; i < numBlancos; i++)cout.put(' ');
}

void colocarSubtitulos() {
    cout << setfill(' ') << setw(90) << "INCREMENTOS" << endl;
    cout << setw(8) << "TIPO" << setw(12) << "PLACA" << setw(13) << "FECHA" << setw(13) << "HORA" << setw(15)
            << "GRAVEDAD" << setw(11) << "MULTA" << setw(12) << "POR TIPO" << setw(12) << "POR FECHA" << setw(11)
            << "POR HORA" << setw(20) << "TOTAL A PAGAR" << endl;
}

int ddmmaa_fecha(int dia, int mes, int año) {
    return año * 10000 + mes * 100 + dia;
}

int hhmmss_hora(int hora, int min, int seg) {
    return hora * 10000 + min * 100 + seg;
}

void procesarInfracciones(int fechaIni, int fechaFin, int dni, double &totalRecaudado) {
    char letraPlaca, gravedad, c; //P599-629    12/12/2023  10:42:26      L
    int placa1, placa2, dia, mes, año, hora, min, seg, fechaInfraccion;
    double multa, incrTipo, incrFecha, incrHora, totalMulta = 0, totalPagar = 0, totalIncrTipo = 0, totalIncrFecha = 0,
            totalIncrHora = 0;
    totalRecaudado = 0;
    while (true) {
        cin >> letraPlaca >> placa1 >> c >> placa2 >> dia >> c >> mes >> c >> año >> hora >> c >> min >> c >> seg >>
                gravedad;
        fechaInfraccion = ddmmaa_fecha(dia, mes, año);
        cout << "- ";
        imprimeTipo(letraPlaca);
        cout << letraPlaca << placa1 << placa2 << "    ";
        imprimirFechaHora(dia, mes, año, hora, min, seg);
        imprimeGravedad(gravedad);
        multa = calcularMulta(gravedad);
        incrTipo = calcularIncrementoTipo(multa, letraPlaca);
        incrFecha = calcularIncrementoFecha(multa, fechaIni, fechaFin, fechaInfraccion);
        incrHora = calcularIncrementoHora(multa, hora, min, seg);
        totalPagar = multa + incrTipo + incrFecha + incrHora;
        imprimirMontos(multa, incrTipo, incrFecha, incrHora, totalPagar);
        totalMulta += multa;
        totalIncrTipo += incrTipo;
        totalIncrFecha += incrFecha;
        totalIncrHora += incrHora;
        totalRecaudado += totalPagar;
        if (cin.get() == '\n') break;
        cout << endl;
    }
    cout << endl;
    imprimirLinea('-', 140);
    cout << "PAGO TOTAL : " << setw(59) << totalMulta << setw(11) << totalIncrTipo << setw(11) << totalIncrFecha <<
            setw(11)
            << totalIncrHora << setw(18) << totalRecaudado << endl;
}

void imprimirFechaHora(int dia, int mes, int año, int hora, int min, int seg) {
    cout << setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/' << setw(4) << año << "    "
            << setw(2) << hora << ':' << setw(2) << min << ':' << setw(2) << seg << setfill(' ') << "    ";
}

void imprimirMontos(double multa, double incrTipo, double incrFecha, double incrHora, double totalPagar) {
    cout << setw(7) << right << multa << setw(11) << incrTipo << setw(11) << incrFecha << setw(11) << incrHora
            << setw(18) << totalPagar;
}

void imprimeConclusiones(int menorDNI, int mayorDNI, double menorRecaudacion, double mayorRecaudacion,
                         int menorCompañia, int mayorCompañia) {
    imprimirLinea('/', 49);
    cout << "//" << "COMPANIA CON MAYOR PAGO POR INFRACCIONES: " << left << setw(3) << mayorCompañia << "//" << endl;
    cout << "//" << "DNI: " << left << setw(40) << mayorDNI << "//" << endl;
    cout << "//" << "TOTAL PAGADO: " << left << setw(31) << mayorRecaudacion << "//" << endl;
    imprimirLinea('/', 49);
    cout << "//" << "COMPANIA CON MENOR PAGO POR INFRACCIONES: " << left << setw(3) << menorCompañia << "//" << endl;
    cout << "//" << "DNI: " << left << setw(40) << menorDNI << "//" << endl;
    cout << "//" << "TOTAL PAGADO: " << left << setw(31) << menorRecaudacion << "//" << endl;
    imprimirLinea('/', 49);
}

void imprimeTipo(char letraPlaca) {
    switch (letraPlaca) {
        case'P': cout << "PEQUENO     ";
            break;
        case 'M': cout << "MEDIANO     ";
            break;
        default: cout << "GRANDE      ";
            break;
    }
}

void imprimeGravedad(char gravedad) {
    switch (gravedad) {
        case'L': cout << left << setw(14) << "LEVE";
            break;
        case 'G': cout << left << setw(14) << "GRAVE";
            break;
        default: cout << left << setw(14) << "MUY GRAVE";
            break;
    }
}

double calcularMulta(char gravedad) {
    double multa;
    switch (gravedad) {
        case'L': multa = 158.33;
            break;
        case 'G': multa = 516.75;
            break;
        default: multa = 3920.25;
            break;
    }
    return multa;
}

double calcularIncrementoTipo(double multa, char letraPlaca) {
    double incrementoTipo, tasa;
    switch (letraPlaca) {
        case'P': tasa = 0.027;
            break;
        case 'M': tasa = 0.117;
            break;
        default: tasa = 0.153;
            break;
    }
    incrementoTipo = tasa * multa;
    return incrementoTipo;
}

double calcularIncrementoFecha(double multa, int fechaIni, int fechaFin, int fechaInfraccion) {
    double incrementoFecha, tasa;
    if (fechaInfraccion >= fechaIni and fechaInfraccion <= fechaFin) {
        tasa = 0.0725;
    } else {
        if (fechaInfraccion < fechaIni) {
            tasa = 0.1075;
        } else {
            tasa = 0;
        }
    }
    incrementoFecha = tasa * multa;
    return incrementoFecha;
}

double calcularIncrementoHora(double multa, int hora, int min, int seg) {
    double incrementoHora, tasa;
    int hora2 = hhmmss_hora(hora, min, seg);
    if (hora2 >= 43000 and hora2 <= 112500) {
        tasa = 0.085;
    } else {
        if (hora2 > 112500 and hora2 <= 204000) {
            tasa = 0.058;
        } else {
            tasa = 0.037;
        }
    }
    incrementoHora = multa * tasa;
    return incrementoHora;
}

void evaluarMayorPago(double totalRecaudado, int dni, int i, int &mayorDNI, double &mayorRecaudacion,
                      int &mayorCompañia) {
    if (i == 1 or (totalRecaudado > mayorRecaudacion)) {
        mayorRecaudacion = totalRecaudado;
        mayorDNI = dni;
        mayorCompañia = i;
    }
}

void evaluarMenorPago(double totalRecaudado, int dni, int i, int &menorDNI, double &menorRecaudacion,
                      int &menorCompañia) {
    if (i == 1 or (totalRecaudado < menorRecaudacion)) {
        menorRecaudacion = totalRecaudado;
        menorDNI = dni;
        menorCompañia = i;
    }
}

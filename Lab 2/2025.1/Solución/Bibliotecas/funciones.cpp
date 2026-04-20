//
// Created by isabe on 19/04/2026.
//

#include "funciones.h"
#define MAX_LINEA 230

void imprimirLinea(ofstream &rep, char c, int n) {
    for (int i = 0; i < n; i++) {
        rep << c;
    }
    rep << endl;
}

void procesarArchivos(const char *nomRep, const char *nomInf, const char *nomTran) {
    ofstream rep(nomRep, ios::out);
    if (not rep.is_open()) {
        cout << "Error al abrir reporte" << endl;
        exit(1);
    }
    ifstream inf(nomInf, ios::in);
    if (not inf.is_open()) {
        cout << "Error al abrir cometidos" << endl;
        exit(1);
    }
    ifstream tran(nomTran, ios::in);
    if (not tran.is_open()) {
        cout << "Error al abrir registros" << endl;
        exit(1);
    }
    rep << setprecision(2) << fixed; //para que double se imprima con 2 decimales
    imprimirCabecera(rep);
    emitirReporte(rep, inf, tran);
}

void imprimeTipoPlaca(char letraPlaca, ofstream &rep) {
    switch (letraPlaca) {
        case 'P': rep << left<<setw(10) << "PEQUEÑO   "<<right;
            break;
        case 'G': rep <<left<< setw(10) << "GRANDE  "<<left;
            break;
        case 'M': rep << left<<setw(10) << "MEDIANO "<<left;
            break;
        default:
            break;
    }
}

void imprimeGravedad(char letraPlaca, ofstream &rep) {
    switch (letraPlaca) {
        case 'L': rep <<left <<setw(13) << "LEVE     "<<right;
            break;
        case 'G': rep << left <<setw(13) << "GRAVE    "<<right;
            break;
        case 'M': rep << left <<setw(13) << "MUY GRAVE"<<right;
            break;
        default:
            break;
    }
}

void evaluarGravedad(double multa, char letra, int &cantLeve, int &cantGrav, int &cantMuyGrave,
                     double &totalLeve, double &totalGrave, double &totalMuyGrave) {
    if (letra == 'L') {
        cantLeve++;
        totalLeve += multa;
    } else if (letra == 'G') {
        cantGrav++;
        totalGrave += multa;
    } else if (letra == 'M') {
        cantMuyGrave++;
        totalMuyGrave += multa;
    }
}

void buscarInfraccion(ofstream &rep, ifstream &tran, int &cantLeve, int &cantGrav, int &cantMuyGrave,
                      double &totalLeve, double &totalGrave, double &totalMuyGrave, int codInfraccion) {
    tran.clear(); //limpia bandera
    tran.seekg(0, ios::beg); //reinicia el archivo al inicio
    bool encuentraMulta = false;
    int codigo;
    char c, letra;
    double multa;
    while (true) {
        tran >> letra >> codigo;
        if (tran.eof())break;
        tran >> multa;
        if (codigo == codInfraccion) {
            encuentraMulta = true;
            imprimeGravedad(letra, rep);
            rep <<right<< setw(7) << multa << "   ";
            leerImprimir(tran, rep, '\n');
            evaluarGravedad(multa, letra, cantLeve, cantGrav, cantMuyGrave, totalLeve, totalGrave, totalMuyGrave);
        } else {
            while (tran.get() != '\n');
        }
    }
    if (not encuentraMulta) {
        rep << "NO SE ENCONTRÓ LA MULTA";
    }
}

void procesarInfracciones(ofstream &rep, ifstream &inf, ifstream &tran, int &cantLeve, int &cantGrav, int &cantMuyGrave,
                          double &totalLeve, double &totalGrave, double &totalMuyGrave) {
    // P599-629    12/12/2023  2036       M852-620  23/01/2024    2029  P282-128    12/11/2023  2067
    char letraPlaca, c;
    int placa1, placa2, dia, mes, año, codInfraccion;
    while (true) {
        inf >> letraPlaca;
        inf >> placa1 >> c >> placa2 >> dia >> c >> mes >> c >> año >> codInfraccion;
        rep << "- " << placa1 << placa2 << left << setw(5) << letraPlaca << right;
        imprimeTipoPlaca(letraPlaca, rep);
        rep << right<<setw(2)<<' '<<setfill('0') << setw(2) << dia << '/' << setw(2) << mes << '/' << setw(4) << año << setfill(' ') <<
                setw(10) << codInfraccion<<setw(6)<<' ';
        buscarInfraccion(rep, tran, cantLeve, cantGrav, cantMuyGrave, totalLeve, totalGrave, totalMuyGrave,
                         codInfraccion);
        rep << endl;
        if (inf.get() == '\n')break;
    }
}

void imprimirResumen(int cantLeve, int cantGrav, int cantMuyGrave, double totalLeve, double totalGrave,
                     double totalMuyGrave, double &totalTotal, ofstream &rep) {
    totalTotal = totalLeve + totalGrave + totalMuyGrave;
    imprimirLinea(rep, '-',MAX_LINEA);
    rep << setw(30) << "CANTIDAD" << setw(15) << "MONTO PAGADO" << endl;
    rep << "FALTAS LEVES      :  " << setw(5)<<cantLeve << setw(18) << totalLeve << endl;
    rep << "FALTAS GRAVES     :  " <<  setw(5)<<cantGrav << setw(18) << totalGrave << endl;
    rep << "FALTAS MUY GRAVES :  " <<  setw(5)<<cantMuyGrave << setw(18) << totalMuyGrave << endl;
    imprimirLinea(rep, '-', 70);
    rep << "TOTAL: " << setw(19) << cantLeve + cantGrav + cantMuyGrave << setw(18) << totalTotal << endl;
}

void evaluarMayorPago(int &dniMayor, double &pagoMayor, double totalTotal, int dni) {
    if (pagoMayor < totalTotal) {
        dniMayor = dni;
        pagoMayor = totalTotal;
    }
}

void resumenFinal(ofstream &rep, int dniMayor, double pagoMayor) {
    rep << endl;
    imprimirLinea(rep, '/', 50);
    rep << "//COMPAÑIA CON MAYOR PAGO DE INFRACCIONES:"<<setw(8)<<"//" << endl;
    rep << "//DNI:" << setw(30) << dniMayor << setw(14)<<"//" << endl;
    rep << "//TOTAL PAGADO:" << setw(21) << pagoMayor << setw(14)<<"//" << endl;
    imprimirLinea(rep, '/', 50);
}

void emitirReporte(ofstream &rep, ifstream &inf, ifstream &tran) {
    int contador = 0, dni, dniMayor;
    double pagoMayor = -99;
    //79672079 CONTRERAS/CHANG/JOHANA-CINTHIA    P599-629    12/12/2023  2036       M852-620  23/01/2024    2029  P282-128    12/11/2023  2067
    while (true) {
        int cantLeve = 0, cantGrav = 0, cantMuyGrave = 0;
        double totalLeve = 0, totalGrave = 0, totalMuyGrave = 0, totalTotal = 0;
        inf >> dni;
        if (inf.eof())break;
        rep << "COMPAÑIA No. " << contador + 1 << endl << "REPRESENTANTE LEGAL: ";
        leerImprimir(inf, rep, ' ');
        rep << setw(10) << "DNI: " << dni << endl;
        imprimirLinea(rep, '-', MAX_LINEA);
        imprimeSubtitulos(rep);
        procesarInfracciones(rep, inf, tran, cantLeve, cantGrav, cantMuyGrave, totalLeve, totalGrave, totalMuyGrave);
        imprimirResumen(cantLeve, cantGrav, cantMuyGrave, totalLeve, totalGrave, totalMuyGrave, totalTotal, rep);
        evaluarMayorPago(dniMayor, pagoMayor, totalTotal, dni);
        imprimirLinea(rep, '=', MAX_LINEA);
        contador++;
        // break;
    }
    resumenFinal(rep, dniMayor, pagoMayor);
}

void imprimirCabecera(ofstream &rep) {
    rep << setw(122)<<"MINISTERIO DE TRANSPORTE" << endl;
    rep << setw(126)<<"MULTAS IMPUESTAS A LAS COMPAÑIAS" << endl;
    imprimirLinea(rep, '=',MAX_LINEA);
}

void leerImprimir(ifstream &inf, ofstream &rep, char delim) {
    char c;
    int contador = 0;
    bool mayus = true;
    inf >> ws;
    while (true) {
        c = inf.get();
        if (c == delim) break;
        if (c == '/' or c == '-') {
            c = ' ';
            mayus = true;
        }
        if (mayus) {
            if (c >= 'a' and c <= 'z') {
                c -= 'a' - 'A';
            }
        } else {
            if (c >= 'A' and c <= 'Z') {
                c += 'a' - 'A';
            }
        }
        rep << c;
        if (c != ' ') mayus = false;
        // para que la bandera no se baje inmediatamente después de que se imprime el espacio
        contador++;
    }
}

void imprimeSubtitulos(ofstream &rep) {
    rep << "VEHICULOS INFRACCIONADOS:" << endl;
    rep << setw(8) << "PLACAS" <<
            setw(10) << "TIPO" <<
            setw(15) << "FECHA" <<
            setw(15) << "INFRACCION" <<
            setw(12) << "GRAVEDAD" <<
            setw(10) << "MULTA" <<
            setw(15) << "DESCRIPCION" << endl;
}

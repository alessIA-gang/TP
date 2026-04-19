//
// Created by isabe on 15/09/2025.
//

#include "funciones.h"

void imprimir(const char *nombrArchLeer, const char *nombrArchImprime) {
    //open
    ifstream archLeer(nombrArchLeer, ios::in);
    if (not archLeer.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombrArchLeer;
        exit(1);
    }

    ofstream archImprime(nombrArchImprime, ios::out);
    if (not archImprime.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombrArchImprime;
        exit(1);
    }

    imprimeLeer(archImprime, archLeer);
}

void imprimeLeer(ofstream &archImprime, ifstream &archLeer) {
    char c;
    while (true) {
        c = archLeer.get();
        if (c == '{') {
            while (true) {
                c = archLeer.get();
                if (c == '}') {
                    c= archLeer.get();
                    break;
                }
            }
        }
        archImprime.put(c);
        if (archLeer.eof())break;
    }
}

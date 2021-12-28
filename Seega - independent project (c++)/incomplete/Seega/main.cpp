#include "funciones.h"


int main() {
    mesa tablero;

    pieza bloqueo;
    pieza j1[12];
    pieza j2[12];
    //hacer un tablero global en el arreglo
    char **p = new char*[5];
    for (int i = 0; i < 5; ++i) {
        p[i] = new char[5];
    }
    for (int i = 0; i < 12; ++i) {
        j1[i].tablero = p;
    }
    for (int i = 0; i < 12; ++i) {
        j2[i].tablero = p;
    }
    bloqueo.tablero = p;

    seleccionar_color(j1, j2);

    //Seleccionar posiciones de las fichas
    posicionar_fichas(j1, j2, bloqueo, tablero);

    //Movimiento de las fichas
    bloqueo.tablero[2][2] = ' ';
    int x,y;
    char fichaj2 = j2[0].ficha;
    char fichaj1 = j1[0].ficha;
    for (int i = 0; finish(j1, j2); ++i) {

        if (i % 2 == 0) {
            cout<<"J2 ";
            mover_fichas(tablero, j2, bloqueo, fichaj2);
        } else {
            cout<<"J1 ";
            mover_fichas(tablero, j1, bloqueo, fichaj1);
        }
    }
}
#include "funciones.h"

void seleccionar_color(pieza j1[12], pieza j2[12]){
    char color;
    cout << "ingrese su color(B, R, N)" << endl;
    cin >> color;
    for (int i = 0; i < 12; ++i) {
        j1[i].ficha = color;
    }
    cout << "ingrese su color(B, R, N)" << endl;
    cin >> color;
    for (int i = 0; i < 12; ++i) {
        j2[i].ficha = color;
    }
}

void posicionar_fichas (pieza j1[12], pieza j2[12], pieza bloqueo, mesa tablero) {
    int cont1 = 2;
    int cont2 = 2;
    bloqueo.tablero[2][2] = 'X';
    j1[0].pos_x = 0;
    j1[0].pos_y = 2;
    j1[0].tablero[j1[0].pos_y][j1[0].pos_x] = j1[0].ficha;
    j1[1].pos_x = 2;
    j1[1].pos_y = 4;
    j1[1].tablero[j1[1].pos_y][j1[1].pos_x] = j1[1].ficha;
    j2[0].pos_x = 2;
    j2[0].pos_y = 0;
    j2[0].tablero[j2[0].pos_y][j2[0].pos_x] = j2[0].ficha;
    j2[1].pos_x = 4;
    j2[1].pos_y = 2;
    j2[1].tablero[j2[1].pos_y][j2[1].pos_x] = j2[1].ficha;
    tablero.dibujar_tablero(j1[0].tablero);
    for (int i = 2; i < 12; ++i) {
        if (i % 2 == 0) {
            for (int j = 0; j < 2; ++j) {
                cout<<"J1 ";
                tablero.dibujar_tablero(j1[cont1].insertar_ficha());
                cont1++;
            }
        } else {
            for (int j = 0; j < 2; ++j) {
                cout<<"J2 ";
                tablero.dibujar_tablero(j2[cont2].insertar_ficha());
                cont2++;
            }
        }
    }
}

void mover_fichas (mesa tablero, pieza jugador[12], pieza bloqueo, char ficha){
    int x, y;
    bool value = true;
    while(value){
        cout<<"seleccione ficha a mover"<<endl;
        cout<<"Posicion x:"<<endl;
        cin>>x;
        cout<<"Posicion y:"<<endl;
        cin>>y;
        if (bloqueo.tablero[y-1][x-1] == ficha){
            if (y-1 == 0 and x-1 == 0){
                if (bloqueo.tablero[y][x-1] == ' ' or bloqueo.tablero[y-1][x] == ' '){
                    value = false;
                }
            }
            else if (y-1 == 4 and x-1 == 4){
                if (bloqueo.tablero[y-2][x-1] == ' ' or bloqueo.tablero[y-1][x-2] == ' '){
                    value = false;
                }
            }
            else if (y-1 == 0 and x-1 == 4){
                if (bloqueo.tablero[y][x-1] == ' ' or bloqueo.tablero[y-1][x-2] == ' '){

                    value = false;
                }
            }
            else if (y-1 == 4 and x-1 == 0){
                if (bloqueo.tablero[y-1][x] == ' ' or bloqueo.tablero[y-2][x-1] == ' '){
                    value = false;
                }
            }
            else if (y-1 == 0){
                if (bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y][x-1] == ' ' or bloqueo.tablero[y-1][x] == ' '){
                    value = false;
                }
            }
            else if (y-1 == 4){
                if (bloqueo.tablero[y-2][x-1] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y-1][x] == ' '){
                    value = false;
                }
            }
            else if (x-1 == 0){
                if (bloqueo.tablero[y-2][x-1] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y][x-1] == ' ' or bloqueo.tablero[y-1][x] == ' '){
                    value = false;
                }
            }
            else if (x-1 == 4){
                if (bloqueo.tablero[y-2][x-1] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y][x-1] == ' '){
                    value = false;
                }
            }
            else{
                if (bloqueo.tablero[y-2][x-1] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y-1][x-2] == ' ' or bloqueo.tablero[y][x-1] == ' ' or bloqueo.tablero[y-1][x] == ' '){
                    value = false;
                }
            }
        } else{
            cout<<"Ficha ingresada incorrecta. INTENTELO DE NUEVO!"<<endl;
        }
    }
    for (int j = 0; j < 12; ++j) {
        if (jugador[j].pos_x == x-1 and jugador[j].pos_y == y-1){
            tablero.dibujar_tablero(jugador[j].mover_ficha());
            break;
        }
    }
}

bool finish(pieza j1[12], pieza j2[12]){
    int contj1 = 0;
    for (int i = 0; i < 12; ++i) {
        if (j1[i].ficha != ' '){
            contj1++;
        }
    }
    int contj2 = 0;
    for (int i = 0; i < 12; ++i) {
        if (j2[i].ficha != ' '){
            contj2++;
        }
    }
    if (contj1 == 0){
        cout<<"GANA J2"<<endl;
        return false;
    }
    else if (contj2 == 0
    ){
        cout<<"GANA J2"<<endl;
        return false;
    }
    return true;
}
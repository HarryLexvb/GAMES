#include "piezas.h"

pieza::pieza() {
    for (int i = 0; i < 5; ++i) {
        tablero[i] = new char[5];
    }
}

bool pieza::verificar_insercion(int pos_x, int pos_y) {
    if (pos_x<0 or pos_x>4 or pos_y<0 or pos_y>4 or tablero[pos_y][pos_x] == 'B' or tablero[pos_y][pos_x] == 'R' or tablero[pos_y][pos_x] == 'N' or tablero[pos_y][pos_x] == 'X'){
        cout<<"INSERCION INVALIDA!"<<endl;
        return false;
    }
    else{
        return true;
    }
}

bool pieza::diagonal(int temp_x, int temp_y, int x, int y) {
    if ((temp_x == x + 1 and temp_y == y + 1) or (temp_x == x + 1 and temp_y == y - 1) or (temp_x == x - 1 and temp_y == y - 1) or (temp_x == x - 1 and temp_y == y + 1)){
        cout<<"Diagonal, MOVIMIENTO INVALIDO!"<<endl;
        return false;
    }
    else{
        return true;
    }
}

char **pieza::insertar_ficha(){
    int x = 0, y = 0;

    while(true){
        cout << "ingrese posicion x:" << endl;
        cin >> x;
        pos_x = x - 1;
        cout << "ingrese posicion y:" << endl;
        cin >> y;
        pos_y = y - 1;
        if (verificar_insercion(pos_x, pos_y)){
            break;
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (pos_x == i and pos_y == j) {
                tablero[j][i] = ficha;
            }
            else if (pos_x == i and pos_y == j) {
                tablero[j][i] = ficha;
            }
        }
    }
    return tablero;
}

char **pieza::custodiar_ficha(){
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (pos_x == i and pos_y == j) {
                tablero[j][i] = ficha;
                if (j < 2 and i < 0){
                    cout<<"entro 1"<<endl;
                    if (tablero[j+1][i] != ficha and tablero[j+2][i] == ficha){
                        tablero[j+1][i] = ' ';
                    }
                    if (tablero[j][i+1] != ficha and tablero[j][i+2] == ficha){
                        tablero[j][i+1] = ' ';
                    }
                }
                else if (j > 2 and i > 2){
                    cout<<"entro 2"<<endl;
                    if (tablero[j-1][i] != ficha and tablero[j-2][i] == ficha){
                        tablero[j-1][i] = ' ';
                    }
                    if (tablero[j][i-1] != ficha and tablero[j][i-2] == ficha){
                        tablero[j][i-1] = ' ';
                    }
                }
                else if (j < 2 and i > 2){
                    cout<<"entro 3"<<endl;
                    if (tablero[j+1][i] != ficha and tablero[j+2][i] == ficha){
                        tablero[j+1][i] = ' ';
                    }
                    if (tablero[j][i-1] != ficha and tablero[j][i-2] == ficha){
                        tablero[j][i-1] = ' ';
                    }
                }
                else if (j > 2 and i < 2){
                    cout<<"entro 4"<<endl;
                    if (tablero[j-1][i] != ficha and tablero[j-2][i] == ficha){
                        tablero[j-1][i] = ' ';
                    }
                    if (tablero[j][i+1] != ficha and tablero[j][i+2] == ficha){
                        tablero[j][i+1] = ' ';
                    }
                }
                else if (j < 2){
                    cout<<"entro 5"<<endl;
                    if (tablero[j+1][i] != ficha and tablero[j+2][i] == ficha){
                        tablero[j+1][i] = ' ';
                    }
                    if (tablero[j][i-1] != ficha and tablero[j][i-2] == ficha){
                        tablero[j][i-1] = ' ';
                    }
                    if (tablero[j][i+1] != ficha and tablero[j][i+2] == ficha){
                        tablero[j][i+1] = ' ';
                    }
                }
                else if (j > 2){
                    cout<<"entro 6"<<endl;
                    if (tablero[j-1][i] != ficha and tablero[j-2][i] == ficha){
                        tablero[j-1][i] = ' ';
                    }
                    if (tablero[j][i-1] != ficha and tablero[j][i-2] == ficha){
                        tablero[j][i-1] = ' ';
                    }
                    if (tablero[j][i+1] != ficha and tablero[j][i+2] == ficha){
                        tablero[j][i+1] = ' ';
                    }
                }
                else if (i < 2){
                    cout<<"entro 7"<<endl;
                    if (tablero[j-1][i] != ficha and tablero[j-2][i] == ficha){
                        tablero[j-1][i] = ' ';
                    }
                    if (tablero[j+1][i] != ficha and tablero[j+2][i] == ficha){
                        tablero[j+1][i] = ' ';
                    }
                    if (tablero[j][i+1] != ficha and tablero[j][i+2] == ficha){
                        tablero[j][i+1] = ' ';
                    }
                }
                else if (i > 2){
                    cout<<"entro 8"<<endl;
                    if (tablero[j-1][i] != ficha and tablero[j-2][i] == ficha){
                        tablero[j-1][i] = ' ';
                    }
                    if (tablero[j+1][i] != ficha and tablero[j+2][i] == ficha){
                        tablero[j+1][i] = ' ';
                    }
                    if (tablero[j][i-1] != ficha and tablero[j][i-2] == ficha){
                        tablero[j][i-1] = ' ';
                    }
                }
                else{
                    cout<<"entro 9"<<endl;
                    if (tablero[j-1][i] != ficha and tablero[j-2][i] == ficha){
                        tablero[j-1][i] = ' ';
                    }
                    if (tablero[j+1][i] != ficha and tablero[j+2][i] == ficha){
                        tablero[j+1][i] = ' ';
                    }
                    if (tablero[j][i-1] != ficha and tablero[j][i-2] == ficha){
                        tablero[j][i-1] = ' ';
                    }
                    if (tablero[j][i+1] != ficha and tablero[j][i+2] == ficha){
                        tablero[j][i+1] = ' ';
                    }
                }
            }
        }
    }
}

char **pieza::mover_ficha() {
    int x, y;
    int tem_x = pos_x, temp_y = pos_y;
    cout<<"Mover a..."<<endl;
    while(true){
        cout << "ingrese posicion x:" << endl;
        cin >> x;
        pos_x = x - 1;
        cout << "ingrese posicion y:" << endl;
        cin >> y;
        pos_y = y - 1;
        if (verificar_insercion(pos_x, pos_y) and diagonal(tem_x, temp_y, pos_x, pos_y)){
            tablero[temp_y][tem_x] = ' ';
            break;
        }
    }
    //custodiar ficha (comer)
    custodiar_ficha();
    return tablero;
}

#include <iostream>

using namespace std;

struct pieza {
    int pos_x = -1, pos_y = -1;
    char ficha;
    char **tablero = new char*[5];

    pieza();
    bool verificar_insercion(int, int);
    char **insertar_ficha();
    char **mover_ficha();

};
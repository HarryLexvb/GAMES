#include "iostream"
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include "windows.h"
#include <fstream>

#include <stack> 
#include <utility>

#define DERECHA 77
#define IZQUIERDA 75
#define ARRIBA 72
#define ABAJO 80

#define ponerBomba 112

using namespace std;
//variables globales 
int move1;
int mn = 41;
int i, j;
char Player[10];
char h = 205, v = 186, e1 = 201, e2 = 200, e3 = 187, e4 = 188;

 
void mover_XY(int x, int y) {

	HANDLE  hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}
void ocultarcursor() {
	HANDLE  hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hCon, &cci);
}
int random() {
	int x = rand() % 4 + 1;

	if (x == 1)
	{
		move1 = DERECHA;
	}
	else if (x == 2)
	{
		move1 = IZQUIERDA;
	}
	else if (x == 3)
	{
		move1 = ARRIBA;
	}
	else if (x == 4)
	{
		move1 = ABAJO;
	}
	return move1;
}

class Menu {
public:
	string opcion;
	string Frase;
	int height;
	int pos_y;
	string draw(int own_height, string own_frase, int ownpos_y);
};
string Menu::draw(int own_height, string own_frase, int ownpos_y) {
	height = own_height; string Frase = own_frase; pos_y = ownpos_y;
	///lineas horizontales
	for (int i = 2; i < 78; i++) {
		///arriba
		mover_XY(i, 3); ///nos situamos en la posicion i y en el eje y nos situamos a 3 espacios                     
		cout << h; ///imprimir el simbolo especificando que pertenece al codigo ascii
		///abajo
		mover_XY(i, height);///nos situamos en la posicion i y en el eje y nos situamos a 23 espacios
		cout << h; ///imprimir el simbolo especificando que pertenece al codigo ascii

	}

	///lineas verticales
	for (int i = 4; i < height; i++) {
		mover_XY(2, i); ///nos situamos en el eje x= 2 y en el eje y la i varie
		cout << v; ///imprimir el simbolo especificando que pertenece al codigo ascii
		mover_XY(77, i);///nos situamos en el eje x= 77 y en el eje y la i varie
		cout << v; ///imprimir el simbolo especificando que pertenece al codigo ascii
	}
	///esquinas
	mover_XY(2, 3); cout << e1;
	mover_XY(2, height); cout << e2;
	mover_XY(77, 3); cout << e3;
	mover_XY(77, height); cout << e4;
	//Escritura
	mover_XY(22, pos_y); cout << Frase; cin >> opcion;
	return opcion;
}
class bomba{
	public:
	int tiempo=3,x,y;
	int radio = 4;
	//vector<pair<int ,int>> explota;
	bomba(int,int);
	void pintar();
	void explotar(); 	
};
bomba::bomba(int _x,int  _y){
	x = _x; 
	y = _y; 
}
void bomba::pintar(){
	mover_XY(x,y);cout<<"o"; 
} 
void bomba::explotar(){
	if(tiempo == 0){
		x-4; 
		y-4; 
		
	}else{
		--tiempo; 
	}
		
}
class BomberMan {
	int x, y;
public:
	int energy;
	BomberMan(int _x, int _y, int _energy);
	void Pintar();
	void Borrar();
	stack<bomba> bomba1; 
	void Mover();
	void PintarVida();
	int getX();
	int getY();
	

};
BomberMan::BomberMan(int _x, int _y, int _energy) {
	x = _x;
	y = _y;
	energy = _energy;
}
void BomberMan::Pintar() {
	mover_XY(x, y); cout << (char)42;
}
void BomberMan::Borrar() {
	mover_XY(25, 1); cout << "                ";
	mover_XY(x, y); cout << (char)32;
}
void BomberMan::Mover() {

	if (_kbhit()) {
		Borrar();
		int tecla = _getch();

		//if ((x+1)%2!=0 && (y)%2!=0 || (x-1)%2!=0 && (y)%2!=0 || (x)%2!=0 && (y+1)%2!=0 || (x)%2!=0 && (y-1)%2!=0)
		//LAS RESTRICCIONES FALLAN POR AHORA, POR ESO NO SE PUEDE MOVER.
		if (tecla == DERECHA || tecla == IZQUIERDA || tecla == ARRIBA || tecla == ABAJO) {
		}
		if (tecla == DERECHA && x + 1 < mn - 1) {
			x += 2;
		}
		if (tecla == IZQUIERDA && x > 1) {
			x -= 2;
		}
		if (tecla == ARRIBA && y > 3) {
			y -= 2;
		}
		if (tecla == ABAJO && y + 1 < mn / 2 + 1) {
			y += 2;
		}
		if(tecla == ponerBomba){
			bomba1.push(bomba(x,y)); 					
		}
		if(!bomba1.empty()){
			bomba1.top().pintar();
		}
					    //mover_XY(x, y);
		/*if (tecla == DERECHA && (x + 1) % 2 != 0 && (y) % 2 != 0)x++;
		if (tecla == IZQUIERDA && (x - 1) % 2 != 0 && (y) % 2 != 0)x--;
		if (tecla == ARRIBA && (x) % 2 != 0 && (y + 1) % 2 != 0)y--;
		if (tecla == ABAJO && (x) % 2 != 0 && (y - 1) % 2 != 0)y++;*/
		if (tecla == 'e')energy--;
		Pintar();
		PintarVida();
		

	}
}
void BomberMan::PintarVida() {
	mover_XY(25, 0); cout << "BOMBERMAN ENERGY";

	for (i = 0; i < energy; i++)
	{
		mover_XY(25 + i, 1); cout << (char)254;
	}
}
int BomberMan::getX()
{
	return x;
}
int BomberMan::getY()
{
	return y;
}
class Jugador{
    public:
    string  Nickname;
    int score_actual;
    string Player;
    int score;
    string Enter_nickname();
    string Salon_fama();
    void Ordenar(int score_actual);
};
string Jugador::Enter_nickname(){//Ingresar nombre y guardarlo.
    system("cls"); ///limpiar pantalla
    Menu nick_ingresar;
    nick_ingresar.draw(14,"Ingrese nickname: ",8) ;
    Nickname= nick_ingresar.opcion;
    return Nickname;
}
void Jugador::Ordenar(int score_actual){//Compara las puntuaciones y ordena las tres primeras.Entre los parentesis esta el score del nuevo jugador.
    int pivote=score_actual;
    string pivote_nombre=Nickname;
    ifstream leer;
    ofstream Temp;
    leer.open("bomberman_ranking.txt");
    Temp.open("cambiante.txt",ios::app);
    leer>>Player;
    while(!leer.eof()){
        leer>>score;
        if (pivote>=score){
            Temp<<pivote_nombre<<" "<<pivote<<endl;
            pivote=score;
            pivote_nombre=Player;
        }
        else {Temp<<Player<<" "<<score<<endl;}
        leer>>Player;
    }
    leer.close();
    Temp.close();
    remove ("bomberman_ranking.txt");
    rename ("cambiante.txt","bomberman_ranking.txt");
}
string Jugador::Salon_fama(){//Imprime el salon de la fama.
    string score;
	string Almacenar="   SALON DE LA FAMA:\n";
	ifstream ranking;
	ranking.open("bomberman_ranking.txt",ios::app);
	ranking>>Player;
	while(!ranking.eof()){
		ranking>>score;
		Almacenar+="\n\n\t          "+ Player +"\t   -------- >   \t"+ score;
		ranking>>Player;
	}
	Almacenar+="\n\n\n\t\t\tPresione x para continuar:";
    system("cls");
	Menu Salon;
	Salon.draw(20,Almacenar,6);
	return Salon.opcion;
}

class BigBoss {
	int x, y;

public:
	int energy;
	BigBoss(int _x, int _y, int _energy);
	void Pintar();
	void Borrar();
	void Mover();
	void PintarVida();
	int getX();
	int getY();

};
BigBoss::BigBoss(int _x, int _y, int _energy) {
	x = _x;
	y = _y;
	energy = _energy;
}
void BigBoss::Pintar() {
	mover_XY(x, y);     cout << "   @@@@@@@   ";
	mover_XY(x, y + 1); cout << " °@@@@@@@@@° ";
	mover_XY(x, y + 2); cout << " @@@@@@@@@@@ ";
	mover_XY(x, y + 3); cout << "@@@       @@@";
	mover_XY(x, y + 4); cout << "@@@  BIG  @@@";
	mover_XY(x, y + 5); cout << "@@@ ===== @@@";
	mover_XY(x, y + 6); cout << "@@@ BO-SS @@@";
	mover_XY(x, y + 7); cout << "@@@       @@@";
	mover_XY(x, y + 8); cout << " @@@@@@@@@@@ ";
	mover_XY(x, y + 9); cout << " °@@@@@@@@@° ";
	mover_XY(x, y + 10);cout << "   @@@@@@@   ";

}
void BigBoss::Borrar() {
	mover_XY(0, 1); cout << "                ";

	for (i = 0; i < 11; i++)
	{
		if (i % 2 == 0)
		{
			mover_XY(x, y + i);   cout << "             ";
		}
		else
		{
			mover_XY(x, y + i); cout << " ° ° ° ° ° ° ";
		}
	}

}
void BigBoss::Mover() {


	Borrar();
	char tecla = random();

	if (tecla == DERECHA || tecla == IZQUIERDA || tecla == ARRIBA || tecla == ABAJO) {
	}
	if (tecla == DERECHA && x + 13 < mn - 1) {
		x += 2;
	}
	if (tecla == IZQUIERDA && x > 1) {
		x -= 2;
	}
	if (tecla == ARRIBA && y > 3) {
		y -= 2;
	}
	if (tecla == ABAJO && y + 11 < mn / 2 + 1) {
		y += 2;
	}
	if (tecla == 'e') {
		energy--;
	}
	Pintar();
	PintarVida();


}
void BigBoss::PintarVida() {
	mover_XY(0, 0); cout << "BIGBOSS ENERGY";

	for (i = 0; i < energy; i++)
	{
		mover_XY(0 + i, 1); cout << (char)254;
	}
}
int BigBoss::getX()
{
	return x;
}
int BigBoss::getY()
{
	return y;
}

void Imprimir_Mapa_facil() {
	system("cls");
	mover_XY(0, 2); cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";


	for (i = 0; i < mn / 2; i++)
	{
		if (i % 2 == 0 and j % 2 == 0)
		{
			mover_XY(0, 4 + i); cout << "° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° ° °";
		}
		else
		{
			mover_XY(0, 2 + i); cout << "°";
			mover_XY(mn - 1, 2 + i); cout << "°";
		}
	}
	mover_XY(0, 22); cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
}

int main() {

	
	//stack<bomba> bomba1; 
	string menu_1 = "Presione X para empezar: ";
	string menu_2 = "\n\n\t\t\tA. Facil"
		"\n\n\t\t\tB. Dificil"
		"\n\n\t\t\tSeleccione el nivel: ";
	string menu_3 = "Ingrese el numero de partidas:";
	string menu_final = "ha seleccionado una tecla diferente";

	string submenu_1 = "\n\t\t\tINSTRUCCIONES PARA BOMBERMAN:"
		"\n\n\t\t1. Inicia con 16 de ENERGY."
		"\n\n\t\t2. Tus bombas quitan BIGBOSS ENERGY."
		"\n\n\t\t3. Ganas cuando el BIGBOSS ENERGY quede en 0."
		"\n\n\t\t4. Pierdes cuando tu ENERGY quede en 0. "
		"\n\n\t\t   Presiona X para continuar: ";

	system("cls");
	Menu menu_uno;
	menu_uno.draw(13, menu_1, 8);
	Jugador J1;
	int Scr;

	if (menu_uno.opcion == "X" || menu_uno.opcion == "x") {
		system("cls");
		J1.Enter_nickname();
		system("cls"); ///limpiar pantalla
		Menu menu_dos;
		menu_dos.draw(20, menu_2, 8);
		
		if (menu_dos.opcion == "A" || menu_dos.opcion == "a") {
			system("cls");
			Menu submenu_uno;
			submenu_uno.draw(22, submenu_1, 6);
			if (submenu_uno.opcion == "X" || submenu_uno.opcion == "x") {
				Imprimir_Mapa_facil();
				BomberMan BM(39, 21, 16);
				BigBoss BB(1, 3, 14);//
				BM.Pintar();
				BB.Pintar();//
				BM.PintarVida();
				BB.PintarVida();//
				ocultarcursor();//OcultarCursor();
				while (true) {
					if (BB.getX() < BM.getX() && BB.getY() < BM.getY()&& BB.getX()+10 > BM.getX() && BB.getY()+5 > BM.getY()) {
						BM.energy--;
					}
					BM.Mover();					             
					BB.Mover();//
					Sleep(100);

					if (BB.energy == 0) {
						//Scr = BM.energy;
						BM.Borrar();
						BB.Borrar();
						mover_XY(16, 12); cout << "GAME OVER";
						break;
					}
					if (BM.energy == 0) {
						//Scr = BM.energy;
						BM.Borrar();
						BB.Borrar();
						mover_XY(16, 12); cout << "GAME OVER";
						break;
					}
				}
				J1.Ordenar(333);
			}

		}
		else if (menu_dos.opcion == "B" || menu_dos.opcion == "b") {
			system("cls");
			Menu menu_tres;
			menu_tres.draw(18, menu_3, 8);
			string menu_4 = "   Numero de partidas seleccionadas: " + menu_tres.opcion +
				"\n\n\t\t\t Ingrese el numero de vidas:";
			system("cls");
			Menu menu_cuatro;
			menu_cuatro.draw(18, menu_4, 8);
			string menu_5 = "   Numero de partidas seleccionadas:" + menu_tres.opcion +
				"\n\n\t\t\t Numero de vidas seleccionadas:" + menu_cuatro.opcion +
				"\n\n\t\t\t Posicion aleatoria(A) o por dafauil(D):";
			system("cls");
			Menu menu_cinco;
			menu_cinco.draw(18, menu_5, 8);
			string menu_6 = "   Numero de partidas seleccionadas:" + menu_tres.opcion +
				"\n\n\t\t\t Numero de vidas seleccionadas:" + menu_cuatro.opcion +
				"\n\n\t\t\t Posicion seleccionada:" + menu_cinco.opcion;

			string menu_fail = "   Numero de partidas seleccionadas:" + menu_tres.opcion +
				"\n\n\t\t\t Numero de vidas seleccionadas:" + menu_cuatro.opcion +
				"\n\n\t\t\t solo puede ingresa aleatoria(A) o  dafauil(D)";
			system("cls");
			cout << "jugamo xd " << endl;
		}

	}
	else {
		system("cls"); ///limpiamos pantalla 
		Menu menu_fi;
		menu_fi.draw(13, menu_final, 8);
	}
	
	Sleep(666);
	system("cls");
	J1.Salon_fama();

	system("pause > null");
	return 0;
}


#include "iostream"
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include "windows.h"
#include <math.h>
#include <fstream>
#define DERECHA 77
#define IZQUIERDA 75
#define ARRIBA 72
#define ABAJO 80
//#define ENTER 13
#define PONERBOMBA 112

const int mn=41, mn02=52, mn03=66, bn=13; 
const int FIL=26,COL=52;
char Mapa02[FIL][COL]; 
//char Mapa03[FIL][COL];
char Mapa[mn][mn];// Mapa02[mn02][mn02], Mapa03[mn03][mn03];
int i, j, m, n;
int time=0;
int tecla;
bool ex=false;
char v = 186, d = 201, h = 205, a = 200, u=187;
char g=188, RM=177;
int f,c;

//char v = 186, d = 201, h = 205, a = 200, u=187, f=188;
using namespace std;

class Menu {
public:
	string opcion;
    int num_frase;
	int height;
    Menu(int num_menu,int altura){
        height = altura; num_frase = num_menu;
    };
	string draw(string Frase[]);
};
string Menu::draw(string Frase[]) {
    
    cout<<"\n\n"<<endl;
    cout<<"\t\t";
    for (int i = 0; i < 78; i++) {//dibuja la primera horizontal
        if (i==0){cout<<d;} 
        else if (i==77){cout<<u;}                   
        else {cout << h;} 
    }
    cout<<endl;//dibuja el contenido
    for(int j=0;j<(height-1)/2;j++){
        cout<<"\t\t"<<v<<"                                                                            "<<v<<endl;
    }
    for (int k=0;k<num_frase;k++){
        cout<<"\t\t"<<v<<"\t\t"<<Frase[k]<<"                "<<v<<endl;
    }
    for(int j=0;j<(height-1)/2;j++){
        cout<<"\t\t"<<v<<"                                                                            "<<v<<endl;
    }
    cout<<"\t\t";
    for (int i = 0; i < 78; i++) {
        if (i==0){cout<<a;} 
        else if (i==77){cout<<g;}                   
        else {cout << h;} 
    }
    cout<<"\n";cin>>opcion;
	return opcion;
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
    string nick[1]={"         Ingrese nickname:                   "};
    system("cls"); ///limpiar pantalla
    Menu nick_ingresar(1,5);
    nick_ingresar.draw(nick) ;
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
    int i=2;
	string Almacenar[7]={   "\t\tSALON DE LA FAMA:            ",
                            "                                             "};
	ifstream ranking;
	ranking.open("bomberman_ranking.txt",ios::app);
	ranking>>Player;
	while(!ranking.eof()){
		ranking>>score;
		Almacenar[i]={"\t"+ Player +"\t   -------- >   \t"+ score+"  "};
        i++;
		ranking>>Player;
	}
    Almacenar[5]={"                                             "};
	Almacenar[6]={"\tPresione x para continuar:           "};
    system("cls");
	Menu Salon(7,11);
	Salon.draw(Almacenar);
	return Salon.opcion;
}
int random() {
	int x = rand() % 4 + 1;
	char move;

	if (x == 1)
	{
		move = DERECHA;
	}
	else if (x == 2)
	{
		move = IZQUIERDA;
	}
	else if (x == 3)
	{
		move = ARRIBA;
	}
	else if (x == 4)
	{
		move = ABAJO;
	}
	return move;
}

class Bomba {
	public:
		int x, y;
		//Bomba(int x,int y);
		void Pintar();
		void Explotar(int n);
		void Matar();	
};
void Bomba::Pintar() {
	Mapa[y][x]='o';
	Mapa02[y][x]='o';
} 
void Bomba::Explotar(int n) {

	if(n==1){
		Mapa[y][x]=' ';
		Mapa02[y][x]=' ';
		if ((Mapa[y+1][x]!='°')&&(Mapa02[y+1][x]!='°')) {
			Mapa[y+1][x]='*';
			Mapa02[y+1][x]='*';
		}
		if ((Mapa[y-1][x]!='°')&&(Mapa02[y-1][x]!='°')){
			Mapa[y-1][x]='*';
			Mapa02[y-1][x]='*';
		}
		if ((Mapa[y][x+1]!='°')&&(Mapa[y][x+1]!='°')) {
			Mapa[y][x+1]='*';
			Mapa02[y][x+1]='*';
		}
		if ((Mapa[y][x-1]!='°')&&(Mapa02[y][x-1]!='°')) {
			Mapa[y][x-1]='*';
			Mapa02[y][x-1]='*';
		}
	}
	
	else if(n==2){
		if ((Mapa[y+1][x]!='°')&&(Mapa02[y+1][x]!='°')) {
			Mapa[y+1][x]=' ';
			Mapa02[y+1][x]=' ';
		}
		if ((Mapa[y-1][x]!='°')&&(Mapa02[y-1][x]!='°')) {
			Mapa[y-1][x]=' ';
			Mapa02[y-1][x]=' ';
		}
		if ((Mapa[y][x+1]!='°')&&(Mapa02[y][x+1]!='°')){
			Mapa[y][x+1]=' ';
			Mapa02[y][x+1]=' ';
		}
		if ((Mapa[y][x-1]!='°')&&(Mapa02[y][x-1]!='°')) {
			Mapa[y][x-1]=' ';
			Mapa02[y][x-1]=' ';
		}
		
		if ((Mapa[y+1][x]!='°' and Mapa[y+2][x]!='°')&&(Mapa02[y+1][x]!='°' and Mapa02[y+2][x]!='°')){
			Mapa[y+2][x]='*';
			Mapa02[y+2][x]='*';
		}
		if ((Mapa[y-1][x]!='°' and Mapa[y-2][x]!='°')&&(Mapa02[y-1][x]!='°' and Mapa02[y-2][x]!='°')) {
			Mapa[y-2][x]='*';
			Mapa02[y-2][x]='*';
		}
		if ((Mapa[y][x+1]!='°' and Mapa[y][x+2]!='°')&&(Mapa02[y][x+1]!='°' and Mapa02[y][x+2]!='°')) {
			Mapa[y][x+2]='*';
			Mapa02[y][x+2]='*';
		}
		if ((Mapa[y][x-1]!='°' and Mapa[y][x-2]!='°')&&(Mapa02[y][x-1]!='°' and Mapa02[y][x-2]!='°')) {
			Mapa[y][x-2]='*';
			Mapa02[y][x-2]='*';
		}
	}
	
	else if(n==3){
		if ((Mapa[y+2][x]!='°')&&(Mapa02[y+2][x]!='°') ){
			Mapa[y+2][x]=' ';
			Mapa02[y+2][x]=' ';
		}
		if ((Mapa[y-2][x]!='°')&&(Mapa02[y-2][x]!='°')) {
			Mapa[y-2][x]=' ';
			Mapa02[y-2][x]=' ';
		}
		if ((Mapa[y][x+2]!='°')&&(Mapa02[y][x+2]!='°')) {
			Mapa[y][x+2]=' ';
			Mapa02[y][x+2]=' ';
		}
		if ((Mapa[y][x-2]!='°')&&(Mapa02[y][x-2]!='°')) {
			Mapa[y][x-2]=' ';
			Mapa02[y][x-2]=' ';
		}
		ex=false;
	}

	
}

class BomberMan {
	
	
	public:
		int x, y, ttt;
		bool arriba, abajo,derecha,izquierda; 
		int energy;
		BomberMan(int x, int y, int energy);
		//stack < Bomba > KaBoom; 
		Bomba KaBoom;
		void Pintar();
		void Borrar();
		void Mover();
		void PintarVida(char Barra[2][41]);

};
BomberMan::BomberMan(int x, int y, int energy) {
	this -> x = x;
	this -> y = y;
	this -> energy = energy;
}
void BomberMan::Pintar() {
	Mapa[y][x]='O';
	Mapa02[y][x]='O';
}
void BomberMan::Borrar() {
	Mapa[y][x]=' ';
	Mapa02[y][x]=' ';
}
void BomberMan::Mover(){
	char Barra[2][41];
	if (ex==true)
	{
	if(Mapa[KaBoom.y][KaBoom.x]==' ')
			{
				KaBoom.Pintar();
			}
	if(time>=ttt+9)
	{
		KaBoom.Explotar(1);
	}
	if(time>=ttt+13)
	{
		KaBoom.Explotar(2);
	}
	if(time>=ttt+16)
	{
		KaBoom.Explotar(3);
	}
	}
	if (_kbhit()){
			
		Borrar(); 
		tecla = getch();
		if(tecla == DERECHA || tecla == IZQUIERDA || tecla == ARRIBA || tecla == ABAJO){
		}
		if((tecla == DERECHA && Mapa[y][x+1] != '°')&&(tecla == DERECHA && Mapa[y][x+1] != RM)&&(tecla == DERECHA && Mapa02[y][x+1] != '°')&&(tecla == DERECHA && Mapa02[y][x+1] != RM)){
			//if(Mapa[y][x+1]=='@'){ energy--;}
			 
			x++;
		}
		if((tecla == IZQUIERDA && Mapa[y][x-1] != '°')&&(tecla == IZQUIERDA && Mapa[y][x-1] != RM)&&(tecla == IZQUIERDA && Mapa02[y][x-1] != '°')&&(tecla == IZQUIERDA && Mapa02[y][x-1] != RM)){
			//if(Mapa[y][x-1]=='@'){ energy--;}
			
			x--;
		}
		if((tecla == ARRIBA && Mapa[y-1][x] != '°')&&(tecla == ARRIBA && Mapa[y-1][x] != RM)&&(tecla == ARRIBA && Mapa02[y-1][x] != '°')&&(tecla == ARRIBA && Mapa02[y-1][x] != RM)){
			//if(Mapa[y-1][x]=='@'){ energy--;}
			
			y--;
		}
		if((tecla == ABAJO && Mapa[y+1][x] != '°')&&(tecla == ABAJO && Mapa[y+1][x] != RM)&&(tecla == ABAJO && Mapa02[y+1][x] != '°')&&(tecla == ABAJO && Mapa02[y+1][x] != RM)){
			//if(Mapa[y+1][x]=='@'){ energy--;}
			 
			y++;
		}
		
		if(tecla==PONERBOMBA)
		{
			ex=true;
			ttt=time;
			KaBoom.x=x; KaBoom.y=y;
		}

	}

}
void BomberMan::PintarVida(char Barra[2][41]){
			
	for(j=25;j<25+energy;j++){
		Barra[1][j]=char(254);
	}
}
/*void BomberMan::PintarVida(char Barra2[2][52],int trunc){
	
	//	Barra2[0][19]=energy;
		
	for(j=0;j<energy*trunc;j++){
		Barra2[1][j]=char(254);
	}
	
	for(i=0;i<2;i++){
		for(j=0;j<52;j++){
			cout<<Barra2[i][j];
		}
	cout<<endl;
	}
	cout<<"vidas:  "<<energy;

}*/
class BigBoss {
	
	public:
		int x, y;
		int energy;
		BigBoss(int x, int y, int energy);
		void Pintar(char BigBoss_Enemy[bn][bn]);
		void Borrar(char BigBoss_Empty[bn][bn]);
		void Mover();
		void PintarVida(char Barra[2][41]);

};
BigBoss::BigBoss(int x, int y, int energy) {
	this -> x = x;
	this -> y = y;
	this -> energy = energy;
}
void BigBoss::Pintar(char BigBoss_Enemy[bn][bn]) {
	m=0;
	for(i=y; i<y+11; i++)
		{	
		n=0;
			for(j=x; j<x+13; j++)
			{
				Mapa[i][j]=BigBoss_Enemy[m][n];
				n++;
			}
			m++;
		}
}
void BigBoss::PintarVida(char Barra[2][41]){
				/*for(j=0;j<14;j++)
				{
					Barra[1][j]=' ';
				}*/
	for(j=0;j<energy;j++){
		Barra[1][j]=char(254);				
	}
				
			
}
void BigBoss::Borrar(char BigBoss_Empty[bn][bn]){
	m=0;
	for(i=y; i<y+11; i++)
		{	
		n=0;
			for(j=x; j<x+13; j++)
			{
				Mapa[i][j]=BigBoss_Empty[m][n];
				n++;
			}
			m++;
		}

}
void BigBoss::Mover() {

			do
			{
				tecla=random();
			}
			while(tecla==IZQUIERDA and x<2 or tecla==ABAJO and y>(mn/2)-(bn-1) or tecla==ARRIBA and y<2 or tecla==DERECHA and x>mn-(bn+2));
			
			if(tecla==IZQUIERDA && x>1)
			{
				x-=2;
			}
			else if(tecla==DERECHA && x+13<mn-1)
			{
				x+=2;
			}
			else if(tecla==ARRIBA && y>3)
			{
				y-=2;
			}
			else if(tecla == ABAJO && y+11<(mn/2)+1)
			{
				y+=2;
			}
}

class DeadShots{
	int x, y;
	public:
		bool vida=true;
		DeadShots(int x, int y);
		//Bomba Boom;
		void Pintar();
		void Borrar();
		void Mover();
		~DeadShots();
		
};
DeadShots::DeadShots(int x, int y){
	this -> x = x;
	this -> y = y;
}
void DeadShots::Pintar(){
	if(vida==true)
	{
		Mapa02[y][x]=char(158);
	}
	else 
	{
		Mapa02[y][x]=' ';
	}
}
void DeadShots::Borrar(){
	Mapa02[y][x]=' ';
	
}
void DeadShots::Mover(){

			Borrar(); 
			
			do
			{
				tecla=random();
			}
			while(tecla==IZQUIERDA and x<2 or tecla==ABAJO and y>(COL/2) or tecla==ARRIBA and y<2 or tecla==DERECHA and x>FIL-1);
			
			
			if(tecla == DERECHA || tecla == IZQUIERDA || tecla == ARRIBA || tecla == ABAJO){
			}
			if((tecla == DERECHA && Mapa02[y][x+1] != '°')&&(tecla == DERECHA && Mapa02[y][x+1] != RM)){
				if(Mapa02[y][x+1]==char(42)){ vida = false;}
				x++;
			}
			if((tecla == IZQUIERDA && Mapa02[y][x-1] != '°')&&(tecla == IZQUIERDA && Mapa02[y][x-1] != RM)){
				if(Mapa02[y][x-1]==char(42)){ vida = false;}
				x--;
			}
			if((tecla == ARRIBA && Mapa02[y-1][x] != '°')&&(tecla == ARRIBA && Mapa02[y-1][x] != RM)){
				if(Mapa02[y-1][x]==char(42)){ vida = false;}
				y--;
			}
			if((tecla == ABAJO && Mapa02[y+1][x] != '°')&&(tecla == ABAJO && Mapa02[y+1][x] != RM)){
				if(Mapa02[y+1][x]==char(42)){ vida = false;}
				y++;
			}
			
			
}
DeadShots::~DeadShots(){}

void Llenar_Mapa(){
	//llenar el mapa facil 
	for(i=0; i<mn/2+1; i++)	{
			for(j=0; j<mn; j++)
			{
				if(i==0 or i==mn/2 or j==0 or j==mn-1)
				{
					Mapa[i][j]='°'; 
				}
				else if(i%2==0 and j%2==0)
				{
					Mapa[i][j]='°';
				}
				else
				{
					Mapa[i][j]=' ';
				}
			}
	}
}
void Llenar_Mapa02(){
	char matriz1[FIL][COL]={
		{'°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°'},
		{'°',' ',' ',RM,RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',RM,' ',' ',RM,' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',RM,' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ','°',' ',' ',' ',' ',RM,' ',' ','°','°','°','°','°',' ',' ',' ',' ','°',' ',' ',RM,' ',' ',' ',' ','°','°','°','°','°',' ',RM,'°',' ',' ',' ',RM,' ',' ',' ','°','°','°','°','°',' ',RM,' ','°'},
		{'°',' ',' ','°','°',' ',' ',' ',' ',RM,' ',' ',' ','°',' ',' ',' ',' ',' ',' ','°','°',' ',RM,' ',' ',' ',' ',' ',' ','°',' ',' ',RM,' ','°','°',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ',RM,' ','°'},
		{'°',' ',' ','°',' ',' ',' ','°','°',' ',RM,' ',' ',' ',' ',' ',' ',RM,' ',' ','°',' ',' ',RM,'°','°',' ',' ',' ',' ',' ',' ',RM,' ',' ','°',' ',' ',' ','°','°',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ','°'},
		{'°',RM,RM,'°',' ',' ',' ','°','°',' ',' ',RM,' ',' ',' ',' ',' ',RM,' ',' ','°',' ',' ',RM,'°','°',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ','°','°',' ',' ',' ',RM,RM,RM,' ',' ',RM,' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ','°',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ','°',RM,RM,RM,' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ','°',' ',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ','°',' ',' ',' ','°'},
		{'°',' ',' ','°','°','°',' ',' ','°',RM,RM,'°',' ',' ','°',' ',' ',RM,' ',' ','°','°','°',' ',' ','°',' ',' ','°',' ',' ','°',' ',' ',' ','°','°','°',' ',' ','°','°','°','°','°',' ',' ','°',' ',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ','°',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ','°',' ',' ','°',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',RM,RM,' ',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',RM,RM,'°',' ',' ',' ','°','°','°','°',' ',' ',' ',' ',' ',' ',' ',RM,' ','°',' ',' ',' ','°','°','°','°',' ',' ',' ',RM,' ',' ',' ',' ','°',' ',' ','°','°',' ',' ','°','°','°','°','°',' ',' ','°'},
		{'°',' ',' ',' ','°',' ',' ',' ',' ',' ',' ',' ',RM,RM,RM,' ',' ',' ',RM,' ',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',RM,' ',' ',' ','°',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ','°','°','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,'°','°','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ','°','°','°',' ',' ','°',' ',' ','°',RM,RM,' ',' ',' ',' ','°'},
		{'°',' ',' ',' ','°',' ',' ',' ','°','°','°','°','°','°','°',' ',' ',' ',RM,' ',' ','°',' ',' ',' ','°','°','°','°','°','°','°',' ',' ',' ',' ',RM,'°',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ','°',' ',' ','°'},
		{'°',' ',' ',' ','°',' ',' ',' ',' ',' ',' ','°',' ',' ',' ',RM,RM,' ',' ',' ',' ','°',' ',' ',' ',' ',RM,' ','°',' ',' ',' ',RM,' ',' ',RM,' ','°',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ','°',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',RM,' ',' ','°',' ',' ',' ',RM,' ',' ',' ',RM,' ',' ',' ',' ',' ',RM,' ',' ','°',' ',' ',' ',' ',' ','°',' ',RM,' ',' ','°',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ',RM,' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ',' ',' ','°',' ',' ',' ',' ','°',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ','°','°','°','°','°',' ',' ','°','°','°','°','°','°','°','°',' ',' ','°','°','°','°','°',' ',' ','°','°','°','°','°','°','°','°',' ',' ','°','°','°','°','°','°',' ',' ','°',' ',' ','°',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,'°',' ',' ',' ',' ',' ',' ',' ','°',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ','°',RM,RM,'°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ','°',' ',' ',' ',' ',' ',' ',' ','°',' ',' ','°'},
		{'°',' ',' ','°','°',' ',' ',' ',' ',' ',' ',' ',' ',' ','°','°','°','°','°',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',RM,'°','°','°','°','°','°','°','°',' ',' ','°',' ',' ','°','°','°','°','°','°',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',RM,RM,RM,RM,RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°'}
	
	};
	for (int f = 0; f < FIL; f++) {
        for (int c = 0; c < COL; c++) {
            Mapa02[f][c]=matriz1[f][c];
        }
    }
}
void Llenar_Mapa03(){
	char matriz1[FIL][COL]={
		{'°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°'},
		{'°',' ',' ',RM,' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',RM,' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ','°'},
		{'°',' ',' ',RM,' ',' ','°',' ',RM,'°',' ','°','°','°','°',' ','°','°','°','°',' ','°','°','°','°',' ',RM,' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ','°',' ',' ',' ',' ',RM,'°','°','°',' ','°','°','°','°'},
		{'°',' ',' ','°',' ',' ','°',RM,' ','°',' ','°',' ',' ',RM,' ','°',' ',' ',' ',' ','°',' ',' ','°',RM,'°','°',' ','°','°','°','°','°',' ','°',' ','°','°','°','°','°','°',' ',' ','°',' ',' ','°',' ',' ','°'},
		{'°',' ',' ','°',' ',' ','°',' ',RM,'°',' ','°',' ',' ',RM,' ','°','°','°','°',' ','°',RM,'°','°',' ',' ','°',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ','°',' ',' ','°',' ',' ',' ',' ',' ','°',' ','°','°'},
		{'°',' ',' ','°','°',' ','°',RM,' ','°',' ','°',' ',' ',RM,' ',' ',' ',' ','°',' ','°',' ',' ',' ',' ','°','°','°','°','°','°',' ','°','°','°','°','°',RM,'°',' ',' ','°','°','°','°','°','°',' ',' ',' ','°'},
		{'°',' ',' ',' ','°',' ','°','°','°','°',' ','°','°','°','°',' ','°','°','°','°',RM,'°',' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',RM,' ','°','°',' ','°',' ',' ',RM,' ',' ',' ','°'},
		{'°',' ','°','°','°',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ',RM,' ',' ',' ',' ',' ',RM,' ','°','°','°','°','°','°',RM,RM,RM,'°','°','°','°','°','°','°','°',' ',' ','°',' ',' ',' ',' ','°',' ','°',' ','°'},
		{'°',' ','°',' ',' ',' ','°',' ','°',RM,' ',' ',' ',' ',RM,' ','°',' ',' ',' ',RM,' ',' ','°',' ',' ',' ',' ',' ',' ','°',' ',' ',' ',' ',' ',' ','°',' ',RM,' ',' ',RM,' ',' ',' ',' ','°',' ','°',' ','°'},
		{'°',RM,'°',' ','°','°','°',' ','°',' ',RM,'°',' ','°',' ',' ','°',' ',' ','°',RM,'°',' ','°',' ',RM,'°','°','°','°','°','°','°','°','°',' ',' ','°',' ','°',' ','°',' ',RM,' ','°','°','°',' ','°',' ','°'},
		{'°',' ',' ',' ',' ',' ',' ',' ','°',RM,' ','°',' ','°',' ',' ',' ',' ',' ','°',' ','°',RM,'°',' ',' ',' ',' ',' ',' ','°',' ',' ',' ',' ',RM,' ','°',' ','°',' ','°',' ',' ',RM,' ',' ',' ',' ','°',' ','°'},
		{'°',' ','°',RM,'°','°','°','°','°',' ',RM,'°',' ','°','°','°',RM,'°','°','°',' ','°',' ',' ',RM,'°',RM,'°','°','°','°','°','°','°',RM,'°',' ',RM,' ','°',' ','°','°','°',' ','°','°','°','°','°','°','°'},
		{'°',' ','°',' ',' ',' ',' ',' ',' ',RM,' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ',' ',' ','°',' ',' ',' ',' ','°',' ',' ',' ',' ','°',' ',' ',' ','°',' ',' ',' ',' ',' ',' ',RM,' ',' ',' ',' ','°'},
		{'°',' ','°',' ',RM,' ','°','°',RM,' ','°','°','°','°','°','°',RM,'°','°','°','°','°','°',' ','°','°',' ',RM,'°','°','°','°','°',RM,' ','°','°',' ','°','°','°','°','°','°',RM,' ',' ','°','°',' ','°','°'},
		{'°',RM,'°',RM,' ',' ',' ','°',' ',RM,'°',' ',' ',' ',' ',RM,' ',RM,' ',' ',' ',' ','°',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°','°','°',' ',' ',' ',' ',' ',RM,' ',' ',' ','°',' ',' ','°'},
		{'°',' ',' ',' ','°','°',' ','°',RM,' ','°',' ','°','°',' ',' ','°',' ',' ','°','°',' ','°',' ','°',RM,'°','°','°',RM,RM,RM,'°','°','°',RM,'°',' ','°',' ','°','°',RM,RM,' ','°','°',' ','°',' ',' ','°'},
		{'°',' ',RM,' ','°',' ',' ','°',' ',' ','°',' ','°',' ',' ',' ',RM,' ',' ',' ','°',' ','°',' ','°',' ','°',' ',' ',' ',RM,' ',' ',' ','°',' ','°',' ','°',' ','°',' ',' ',' ',' ','°',' ',RM,'°','°',' ','°'},
		{'°',' ','°',' ','°',' ',RM,' ',' ',' ','°',' ','°',' ','°','°',' ','°','°',' ','°',' ','°',RM,'°',' ','°',' ',' ',' ',RM,' ',' ',' ','°',' ','°',RM,'°',RM,'°',RM,'°','°',' ','°',' ',' ',' ',' ',' ','°'},
		{'°',' ','°',' ',' ',' ','°',' ','°',' ','°',' ','°',RM,' ','°',' ','°',' ',RM,'°',' ','°',' ','°',' ','°','°','°','°','°','°','°','°','°',' ','°',' ','°',' ','°',' ',' ','°',RM,' ',' ','°',RM,'°','°','°'},
		{'°',RM,'°',RM,' ',' ','°',' ','°',' ','°',' ',RM,' ',' ','°',RM,'°',' ',' ',RM,' ','°',' ','°',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','°',' ','°',' ',RM,' ',' ','°',' ',' ',' ','°',' ','°',' ','°'},
		{'°',' ',' ',' ',' ',' ','°',' ','°',' ','°','°',' ','°',RM,' ',' ',' ',RM,'°',' ','°','°',' ','°','°',RM,RM,'°','°','°','°','°',RM,RM,'°','°',' ','°','°',' ','°',' ',' ',' ',' ',RM,'°',' ','°',' ','°'},
		{'°',RM,'°','°','°',RM,RM,RM,'°',' ',' ','°',' ','°',' ','°','°','°',' ','°',' ','°',' ',' ',' ','°',' ',' ',' ',' ','°',' ',' ',' ',' ','°',' ',' ',' ','°',' ','°',' ','°','°','°',' ',RM,' ','°',' ','°'},
		{'°',' ',' ','°',' ',' ','°',' ','°',' ',RM,'°',' ','°',' ',' ','°',' ',' ','°',' ','°',' ',RM,' ','°',' ','°','°','°','°','°','°','°',' ','°',' ',RM,' ','°',' ','°',RM,' ','°',' ',RM,'°',' ','°',' ','°'},
		{'°',' ',' ','°',' ',' ','°',' ',' ',RM,' ','°',' ',' ',RM,' ','°',' ',RM,' ',' ','°',' ','°',' ','°',RM,' ',' ',' ','°',' ',' ',' ',RM,'°',' ','°',' ','°',' ',' ',' ',' ','°',' ',' ','°',RM,' ',' ','°'},
		{'°',' ',' ','°',' ',' ','°',' ','°',' ',' ','°',' ','°',' ',' ','°',' ',' ','°',' ','°',' ','°',' ',' ',' ',' ','°',' ','°',' ','°',' ',' ',' ',' ','°',' ','°',' ','°',' ',' ','°',' ',' ','°',' ',' ','°','°'},
		{'°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°','°'}
	};
	for (int f = 0; f < FIL; f++) {
        for (int c = 0; c < COL; c++) {
            Mapa02[f][c]=matriz1[f][c];
        }
    }
}

void Imprimir(char Mapa[mn][mn]){
	system("cls");
	for(i=0; i<mn/2+1; i++)
	{
		for(j=0; j<mn; j++)
		{
			cout<<Mapa[i][j];
		}
		cout<<endl;
	}
}
void Imprimir_Mapa(char Mapa02[FIL][COL]){
	system("cls");
	for (int fil = 0; fil < FIL; fil++) {
        for (int col = 0; col < COL ; col++) {
            cout<<Mapa02[fil][col]; 
        }
        cout<<endl;
    }
}
/*void Imprimir_Mapa03(char Mapa03[FIL][COL]){
	system("cls");
	for (int fil = 0; fil < FIL; fil++) {
        for (int col = 0; col < COL ; col++) {
            cout<<Mapa03[fil][col]; 
        }
        cout<<endl;
    }
}*/
template<typename q>
int distancia(q bm, BigBoss bb){
	return sqrt(pow(bm.x-bb.x, 2)+pow(bm.y-bb.y, 2));
}
void Imprimir_vida(int energy_BB ,int energy_BM, char Barra[2][41]){

	for(j=0;j<energy_BB;j++){
		Barra[1][j]=char(254);				
	}
	for(j=25;j<25+energy_BM;j++){
		Barra[1][j]=char(254);
	}
	for(i=0;i<2;i++){
		for(j=0;j<41;j++){
			cout<<Barra[i][j];
		}
		cout<<endl;
	}
	
}

int main(){
	char start, modo; 
	bool facil;
	string menu_1[1] =     {"       Presione X para empezar:              "};
	string menu_2[3] =     {"A. MODO 1                                     ",
                            "B. MODO 2                                   ",
                            "Seleccione el nivel:                         "};
	
	string menu_final[1] ={ "      ha seleccionado una tecla diferente    "};

	string submenu_1[7] ={  "\tINSTRUCCIONES PARA BOMBERMAN:        ",
                            "                                             ",
		                    "1. Inicia con 16 de ENERGY.                  ",
		                    "2. Tus bombas quitan BIGBOSS ENERGY.         ",
		                    "3. Ganas cuando el BIGBOSS ENERGY quede en 0.",
		                    "4. Pierdes cuando tu ENERGY quede en 0.      ",
		                    "   Presiona X para continuar:                "};
		                    
    string menu_3[1] = {    "Ingrese el numero de partidas:               "};
    string menu_loss[3]={    "          ¡BIGBOSS ha ganado!                ",
    						"                                             ",
	 						"    Presiona X para continuar:               "};
	string menu_return[4]={ "A.Volver a jugar en el MODO 1.               ",
							"E.Jugar el MODO 2.                           ",
							"I.Finalizar juego.                           ",
							"Seleccione :                                 " };
    char Barra[2][41]={
				{'B','I','G','B','O','S','S',' ','E','N','E','R','G','Y',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B','O','M','B','E','R','M','A','N',' ','E','N','E','R','G','Y'},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				};
	char GameOver[9]={'G','A','M','E',' ','O','V','E','R'};
    system("cls");
    Menu menu_uno(1,5);
    menu_uno.draw(menu_1);
	Jugador Player_now;
	int score_now;

    if(menu_uno.opcion == "X" || menu_uno.opcion == "x"){

    	system("cls");
		Menu menu_dos(3,7);
		menu_dos.draw(menu_2);
		
		if(menu_dos.opcion == "A" || menu_dos.opcion == "a"){
		    system("cls");
			Menu submenu_uno(7,11);
			submenu_uno.draw(submenu_1);
			Player_now.Enter_nickname();
			 
			if (submenu_uno.opcion == "X" || submenu_uno.opcion == "x") {
				Llenar_Mapa();
				
								
				char BigBoss_Enemy[bn][bn]={
					{' ',' ',' ','@','@','@','@','@','@','@',' ',' ',' '},
					{' ','°','@','@','@','@','@','@','@','@','@','°',' '},
					{' ','@','@','@','@','@','@','@','@','@','@','@',' '},
					{'@','@','@',' ',' ',' ',' ',' ',' ',' ','@','@','@'},
					{'@','@','@',' ',' ','B','I','G',' ',' ','@','@','@'},
					{'@','@','@',' ','=','=','=','=','=',' ','@','@','@'},
					{'@','@','@',' ','B','O','-','S','S',' ','@','@','@'},
					{'@','@','@',' ',' ',' ',' ',' ',' ',' ','@','@','@'},
					{' ','@','@','@','@','@','@','@','@','@','@','@',' '},
					{' ','°','@','@','@','@','@','@','@','@','@','°',' '},
					{' ',' ',' ','@','@','@','@','@','@','@',' ',' ',' '},
				};				
				char BigBoss_Empty[bn][bn]={
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ','°',' ','°',' ','°',' ','°',' ','°',' ','°',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ','°',' ','°',' ','°',' ','°',' ','°',' ','°',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ','°',' ','°',' ','°',' ','°',' ','°',' ','°',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ','°',' ','°',' ','°',' ','°',' ','°',' ','°',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ','°',' ','°',' ','°',' ','°',' ','°',' ','°',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				};
				
				
				BomberMan BM(19,19,16);
				BM.Pintar();
				Imprimir(Mapa);
				BigBoss BB(1,1,14);	
				int BM_energy;	
				facil=true;
				while(facil==true){
					char Barra[2][41]={
						{'B','I','G','B','O','S','S',' ','E','N','E','R','G','Y',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','B','O','M','B','E','R','M','A','N',' ','E','N','E','R','G','Y'},
						{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
						};
					BB.Borrar(BigBoss_Empty);					
					BM.Mover();
					BB.Mover();					
					Sleep(90);					
					BB.Pintar(BigBoss_Enemy);
					BM.Pintar();
					
					time++;
					
					
					/*for(j=0;j<41;j++) {	Barra[1][j]=' '; }
					
					if(Mapa[f+1][c]=='@' or Mapa[f-1][c]=='@' or Mapa[f][c+1]=='@' or Mapa[f][c-1]=='@')
					{
						BM.energy--;
					}
					if(Mapa[f+2][c]=='@' or Mapa[f-2][c]=='@' or Mapa[f][c+2]=='@' or Mapa[f][c-2]=='@')
					{
						BM.energy--;
					}*/
				
					
					if(distancia<BomberMan>(BM,BB)<=7){
						BM.energy--; 
					}
					
					if(BigBoss_Enemy[m+1][n] == 'O'){
		 				BB.energy;
					}
					cout<<BB.energy;
					Imprimir(Mapa);
					Imprimir_vida(14,BM.energy,Barra);
					/*for(j=0;j<12;j++){
						Barra[1][j]=char(254);				
					}
					for(j=25;j<25+BM.energy;j++){
						Barra[1][j]=char(254);
					}
					for(i=0;i<2;i++){
						for(j=0;j<41;j++){
							cout<<Barra[i][j];
						}
						cout<<endl;
					}*/
					if(BB.energy==0 or BM.energy==0){
						BM.Borrar();
						m=0;
						for(j=16; j<25; j++)
						{
							Mapa[10][j]=GameOver[m];
							m++;
						}
						Imprimir(Mapa);
						Sleep(90);
						system("cls");
						Menu menu_loser(3,7);
						menu_loser.draw(menu_loss);
						system("cls");
						Menu menu_returnf(4,8);
						menu_returnf.draw(menu_return);
						
						break;
					}
					
					
				}
			}
		} 
		else if(menu_dos.opcion == "B" || menu_dos.opcion == "b"){
			system("cls");
			Menu menu_tres(1,11);
    		menu_tres.draw(menu_3);
    		system("cls");
		    string menu_4[2] = {    "Numero de partidas seleccionadas: " + menu_tres.opcion +"          ",
		                            "Ingrese el numero de vidas:                  "};
		    Menu menu_cuatro(2,11);
		    menu_cuatro.draw(menu_4);
		    system("cls");
		    string menu_5[6] ={     "Numero de partidas seleccionadas: " + menu_tres.opcion +"          ",
		                            "Numero de vidas seleccionadas:    " + menu_cuatro.opcion+"          " ,
		                            "eliga el mapa:                               ",
									"A. laberinto 1                               ",
									"B. laberinto 2                 		 ",
									"Opcion:                                      "}; 
		    Menu menu_cinco(6,11);
		    menu_cinco.draw(menu_5);
		    Jugador Player_now;
			Player_now.Enter_nickname();
		    
		    if(menu_cinco.opcion == "A" || menu_cinco.opcion == "a"){
		    	Llenar_Mapa02();
				
				BomberMan BM(3,2,16);
				BM.Pintar();
				DeadShots DS01(1,1);
				DeadShots DS02(39,1);
				DeadShots DS03(1,19);
				DeadShots DS04(39,19);
				Imprimir_Mapa(Mapa02);
				
		    	while(true){
					
									
					BM.Mover();
					DS01.Mover();
					DS02.Mover();
					DS03.Mover();
					DS04.Mover();
					Sleep(90);
					BM.Pintar();
					DS01.Pintar();
					DS02.Pintar();
					DS03.Pintar();
					DS04.Pintar();
					
					time++;
					
					Imprimir_Mapa(Mapa02);
					for(i=0;i<2;i++){
						for(j=0;j<41;j++){
							cout<<Barra[i][j];
						}
						cout<<endl;
					}
					BM.PintarVida(Barra);
				} 
		    	
		 	}
			else if(menu_cinco.opcion == "B" || menu_cinco.opcion == "b"){
				Llenar_Mapa03();
				
				BomberMan BM(3,2,16);
				BM.Pintar();
				DeadShots DS01(1,1);
				DeadShots DS02(39,1);
				DeadShots DS03(1,19);
				DeadShots DS04(39,19);
				Imprimir_Mapa(Mapa02);
				while(true){
					
									
					BM.Mover();
					DS01.Mover();
					DS02.Mover();
					DS03.Mover();
					DS04.Mover();
					Sleep(90);
					BM.Pintar();
					DS01.Pintar();
					DS02.Pintar();
					DS03.Pintar();
					DS04.Pintar();
					
					time++;
					
					Imprimir_Mapa(Mapa02);
					for(i=0;i<2;i++){
						for(j=0;j<41;j++){
							cout<<Barra[i][j];
						}
						cout<<endl;
					}
					BM.PintarVida(Barra);
				} 
		 	}
		}
		else{
			system("cls");
			Menu menu_fi(1,5);
	    	menu_fi.draw(menu_final);
		}
		Player_now.Ordenar(score_now);
		Player_now.Salon_fama();
	
}}
 

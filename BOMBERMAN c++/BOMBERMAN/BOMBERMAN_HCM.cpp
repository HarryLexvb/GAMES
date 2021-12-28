#include "iostream"
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include "windows.h"
#include <math.h>
#include <string>  
#include <fstream>
#define DERECHA 77
#define IZQUIERDA 75
#define ARRIBA 72
#define ABAJO 80
//#define ENTER 13
#define PONERBOMBA 113

const int mn=41, mn02=52, mn03=66, bn=13; 
const int FIL=26,COL=52;
char Mapa02[FIL][COL]; 
//char Mapa03[FIL][COL];
char Mapa[mn][mn];// Mapa02[mn02][mn02], Mapa03[mn03][mn03];
int i, j, m, n;
int time=0;
int tecla,tecla2;
int posBx=0, posBy=0;
bool ex=false,murio=false,murio2=false;
bool repetir=true;
char v = 186, d = 201, h = 205, a = 200, u=187;
char g=188, RM=177;
int posDS01x,posDS02x,posDS03x,posDS04x;
int posDS01y,posDS02y,posDS03y,posDS04y;
bool murioDS01=false, murioDS02=false, murioDS03=false, murioDS04=false;
int f,c;
int VidaBMapa02 = 0;

//char v = 186, d = 201, h = 205, a = 200, u=187, f=188;
using namespace std;

class Menu {
public:
	string opcion;
    int num_frase;
	int height;
    Menu(int num_menu,int altura){
         num_frase = num_menu;
         height = altura;
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
		void Pintar2();  //Bomba de los DS
		void Explotar(int n);  //para bomberman, ya que es diferente el comportamiento de su bomba con la de otros
		void Explotar2(int n);   //para deadshot
		void Matar();
		void Revisar_posicion(int a,int b); //funcion usada en explotar para ahorrar codigo
};
void Bomba::Pintar() {
	Mapa[y][x]=254;
	Mapa02[y][x]=254;
} 
void Bomba::Pintar2() {
	Mapa02[y][x]=254;
} 
void Bomba::Revisar_posicion(int a, int b){
			if(posDS01x==a && posDS01y==b)	murioDS01 = true;
			if(posDS02x==a && posDS02y==b)	murioDS02 = true;
			if(posDS03x==a && posDS03y==b)	murioDS03 = true;
			if(posDS04x==a && posDS04y==b)	murioDS04 = true;
}
void Bomba::Explotar(int n) {
		char c = char(158);
	if(n==1){
		Mapa[y][x]= c;
		Mapa02[y][x]= c;
		if((Mapa02[y+1][x]=='O' || Mapa02[y-1][x]=='O' || Mapa02[y][x+1]=='O' || Mapa02[y][x-1]=='O' || (posBx==x && posBy==y) ) && murio == false)
		{
			VidaBMapa02--;
			murio = true;
		
		}
		
		Revisar_posicion(x,y);
		
		if(Mapa02[y+1][x]==char(89)) // 89 = Y
		{
			Revisar_posicion(x, y+1);
		}
		if(Mapa02[y-1][x]==char(89))
		{
			Revisar_posicion(x, y-1);
		}
		if(Mapa02[y][x+1]==char(89))
		{
			Revisar_posicion(x+1, y);
		}
		if(Mapa02[y][x-1]==char(89))
		{
			Revisar_posicion(x-1, y);
		}
		
		

		if ((Mapa[y+1][x]!='°')&&(Mapa02[y+1][x]!='°')) {
			Mapa[y+1][x]=c;
			Mapa02[y+1][x]=c;
		}
		if ((Mapa[y-1][x]!='°')&&(Mapa02[y-1][x]!='°')){
			Mapa[y-1][x]=c;
			Mapa02[y-1][x]=c;
		}
		if ((Mapa[y][x+1]!='°')&&(Mapa02[y][x+1]!='°')) {
			Mapa[y][x+1]=c;
			Mapa02[y][x+1]=c;
		}
		if ((Mapa[y][x-1]!='°')&&(Mapa02[y][x-1]!='°')) {
			Mapa[y][x-1]=c;
			Mapa02[y][x-1]=c;
		}
		
	}
	
	else if(n==2){
			if((Mapa02[y+2][x]=='O' || Mapa02[y-2][x]=='O' || Mapa02[y][x+2]=='O' || Mapa02[y][x-2]=='O' || (posBx==x && posBy==y) ) && murio == false)
		{
			VidaBMapa02--;
			murio = true;
		
		}
		
		if(Mapa02[y+2][x]==char(89))
		{
			Revisar_posicion(x, y+2);
		}
		if(Mapa02[y-2][x]==char(89))
		{
			Revisar_posicion(x, y-2);
		}
		if(Mapa02[y][x+2]==char(89))
		{
			Revisar_posicion(x+2, y);
		}
		if(Mapa02[y][x-2]==char(89))
		{
			Revisar_posicion(x-2, y);
		}
		
		
		if ((Mapa[y+1][x]!='°' and Mapa[y+2][x]!='°')&&(Mapa02[y+1][x]!='°' and Mapa02[y+2][x]!='°')){
			Mapa[y+2][x]=c;
			Mapa02[y+2][x]=c;
		}
		if ((Mapa[y-1][x]!='°' and Mapa[y-2][x]!='°')&&(Mapa02[y-1][x]!='°' and Mapa02[y-2][x]!='°')) {
			Mapa[y-2][x]=c;
			Mapa02[y-2][x]=c;
		}
		if ((Mapa[y][x+1]!='°' and Mapa[y][x+2]!='°')&&(Mapa02[y][x+1]!='°' and Mapa02[y][x+2]!='°')) {
			Mapa[y][x+2]=c;
			Mapa02[y][x+2]=c;
		}
		if ((Mapa[y][x-1]!='°' and Mapa[y][x-2]!='°')&&(Mapa02[y][x-1]!='°' and Mapa02[y][x-2]!='°')) {
			Mapa[y][x-2]=c;
			Mapa02[y][x-2]=c;
		}
	}
	
	else if(n==3){
		Mapa[y][x]=' ';
		Mapa02[y][x]=' ';
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
		murio=false;
	}

	
}
void Bomba::Explotar2(int n) {
		int c = 158;
	if(n==1){
		
		Mapa02[y][x]=char(158);
		if((Mapa02[y+1][x]=='O' || Mapa02[y-1][x]=='O' || Mapa02[y][x+1]=='O' || Mapa02[y][x-1]=='O' || (posBx==x && posBy==y) ) && (murio2 == false))
		{
			VidaBMapa02--;
			murio2 = true;
		}

		if (Mapa02[y+1][x]!='°') {
			Mapa02[y+1][x]=char(c); // 158 = x
		}
		if (Mapa02[y-1][x]!='°'){
			Mapa02[y-1][x]=char(c);
		}
		if (Mapa02[y][x+1]!='°') {
			Mapa02[y][x+1]=char(c);
		}
		if (Mapa02[y][x-1]!='°') {
			Mapa02[y][x-1]=char(c);
		}
		
	}
	
	else if(n==2){
		if((Mapa02[y+2][x]=='O' || Mapa02[y-2][x]=='O' || Mapa02[y][x+2]=='O' || Mapa02[y][x-2]=='O' || (posBx==x && posBy==y) ) && (murio2 == false))
		{
			VidaBMapa02--;
			murio2 = true;
		
		}
	
		
		if (Mapa02[y+1][x]!='°' and Mapa02[y+2][x]!='°'){
			Mapa02[y+2][x]=char(c);
		}
		if (Mapa02[y-1][x]!='°' and Mapa02[y-2][x]!='°') {
			Mapa02[y-2][x]=char(c);
		}
		if (Mapa02[y][x+1]!='°' and Mapa02[y][x+2]!='°') {
			Mapa02[y][x+2]=char(c);
		}
		if (Mapa02[y][x-1]!='°' and Mapa02[y][x-2]!='°') {
			Mapa02[y][x-2]=char(c);
		}
	}
	
	else if(n==3){
		Mapa02[y][x]=' ';
		
		if (Mapa02[y+1][x]!='°') {
			Mapa02[y+1][x]=' ';
		}
		if (Mapa02[y-1][x]!='°') {
			Mapa02[y-1][x]=' ';
		}
		if (Mapa02[y][x+1]!='°'){
			Mapa02[y][x+1]=' ';
		}
		if (Mapa02[y][x-1]!='°') {
			Mapa02[y][x-1]=' ';
		}
		if (Mapa02[y+2][x]!='°'){
			Mapa02[y+2][x]=' ';
		}
		if (Mapa02[y-2][x]!='°') {
			Mapa02[y-2][x]=' ';
		}
		if (Mapa02[y][x+2]!='°') {
			Mapa02[y][x+2]=' ';
		}
		if (Mapa02[y][x-2]!='°') {
			Mapa02[y][x-2]=' ';
		}
		
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
		void PintarVida(char Barra[2][52],int trunc);

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
	
	if (ex==true)
	{
	if(Mapa[KaBoom.y][KaBoom.x]==' ')
			{
				KaBoom.Pintar();
			}
		posBx=this->x;
		posBy=this->y;
	if(time>=ttt+20)
	{
		
		KaBoom.Explotar(1);
	}
	if(time>=ttt+25)
	{
		KaBoom.Explotar(2);
	}
	if(time>=ttt+30)
	{
		KaBoom.Explotar(3);
	}
	}
	if (_kbhit()){
			
		Borrar(); 
		tecla = getch();
		
		if((tecla == DERECHA && Mapa[y][x+1] != '°')&&(tecla == DERECHA && Mapa02[y][x+1] != '°' && Mapa02[y][x+1] != char(254))&&(tecla == DERECHA && Mapa02[y][x+1] != RM)){
			//if(Mapa[y][x+1]=='@'){ energy--;}
			 
			x++;
		}
		if((tecla == IZQUIERDA && Mapa[y][x-1] != '°')&&(tecla == IZQUIERDA && Mapa02[y][x-1] != '°' && Mapa02[y][x-1] != char(254))&&(tecla == IZQUIERDA && Mapa02[y][x-1] != RM)){
			//if(Mapa[y][x-1]=='@'){ energy--;}
			
			x--;
		}
		if((tecla == ARRIBA && Mapa[y-1][x] != '°')&&(tecla == ARRIBA && Mapa02[y-1][x] != '°' && Mapa02[y-1][x] != char(254))&&(tecla == ARRIBA && Mapa02[y-1][x] != RM)){
			//if(Mapa[y-1][x]=='@'){ energy--;}
			
			y--;
		}
		if((tecla == ABAJO && Mapa[y+1][x] != '°')&&(tecla == ABAJO && Mapa02[y+1][x] != '°' && Mapa02[y+1][x] != char(254))&&(tecla == ABAJO && Mapa02[y+1][x] != RM)){
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
void BomberMan::PintarVida(char Barra2[2][52],int trunc){
	
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
	
}

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
	public:
	int x=0, y=0, tiempo;
	bool vida=true, exDS=false;
	Bomba B_DS;
	DeadShots(int x, int y);
	//Bomba Boom;
	void Pintar();
	void Borrar();
	void Mover();
	void Bomba();
	~DeadShots();
		
};
DeadShots::DeadShots(int x, int y){
	this -> x = x;
	this -> y = y;
}
void DeadShots::Pintar(){

		Mapa02[y][x]=char(89);

}
void DeadShots::Borrar(){
	Mapa02[y][x]=' ';
	
}
void DeadShots::Mover(){

			Borrar(); 
			
			tecla=random();
			
		
			if((tecla == DERECHA && Mapa02[y][x+1] != '°' && Mapa02[y][x+1] != char(254)) &&(tecla == DERECHA && Mapa02[y][x+1] != RM)){
				x++;
			}
			if((tecla == IZQUIERDA && Mapa02[y][x-1] != '°'&& Mapa02[y][x-1] != char(254))&&(tecla == IZQUIERDA && Mapa02[y][x-1] != RM)){
				x--;
			}
			if((tecla == ARRIBA && Mapa02[y-1][x] != '°' && Mapa02[y-1][x] != char(254))&&(tecla == ARRIBA && Mapa02[y-1][x] != RM)){
				y--;
			}
			if((tecla == ABAJO && Mapa02[y+1][x] != '°' && Mapa02[y+1][x] != char(254))&&(tecla == ABAJO && Mapa02[y+1][x] != RM)){
				y++;
			}	
			
			
}
void DeadShots::Bomba(){
	
	if(exDS == false){
	int w = rand() % 16 + 1; 
		if(w==5)// 5 es un numero cualquiera la cosa es que la probabilidad sea de 1/16
		{
			
			tiempo = time;	
			tecla2=random();
			//if( y>1 && x>1 && y<24 && x<50){
				if(tecla2==DERECHA &&Mapa02[y][x+1] != '°'){
					B_DS.x=x+1;
					B_DS.y=y;
					exDS = true;
				}
				if(tecla2==IZQUIERDA && Mapa02[y][x-1] != '°'){
					B_DS.x=x-1;
					B_DS.y=y;
					exDS = true;
				}
				if(tecla2==ARRIBA && Mapa02[y+1][x] != '°'){
					B_DS.x=x;
					B_DS.y=y+1;
					exDS = true;
				}
				if(tecla2==ABAJO && Mapa02[y-1][x] != '°'){
					B_DS.x=x;
					B_DS.y=y-1;
					exDS = true;
				}
			//}
		}
	}
	if(exDS == true){
		
		if(Mapa02[B_DS.y][B_DS.x]==' ')
			{
				B_DS.Pintar2();
			}
			
		if(time>=tiempo+20)
		{
			
			B_DS.Explotar2(1);
		}
		if(time>=tiempo+25)
		{
			B_DS.Explotar2(2);
		}
		if(time>=tiempo+30)
		{
			B_DS.Explotar2(3);
			exDS = false;
			murio2=false;
		}
		
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
	bool facil,dificil;
	
	string menu_1[1] =     {"       Presione X para empezar:              "};
	string menu_2[3] =     {"A. MODO 1                                    ",
                            "B. MODO 2                                    ",
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
	char Derrota[11]={'H','A','S',' ','P','E','R','D','I','D','O'};
	char Victoria[10]={'H','A','S',' ','G','A','N','A','D','O'};
    system("cls");
    Menu menu_uno(1,5);
    menu_uno.draw(menu_1);
	Jugador Player_now;
	int score_now;
	string w,l;
		

    if(menu_uno.opcion == "X" || menu_uno.opcion == "x"){

	
	while(repetir){
    	system("cls");
		Menu menu_dos(3,7);
		menu_dos.draw(menu_2);
		
		if(menu_dos.opcion == "A" || menu_dos.opcion == "a"){
		    system("cls");
			Menu submenu_uno(7,11);
			submenu_uno.draw(submenu_1);
			
			 
			if (submenu_uno.opcion == "X" || submenu_uno.opcion == "x") {
				Player_now.Enter_nickname();
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
						
					BM.Mover();	
					BM.Pintar();
					Imprimir(Mapa);
					BB.Borrar(BigBoss_Empty);					
					BB.Mover();	
					Sleep(50);									
					BB.Pintar(BigBoss_Enemy);
					
					time++;
				 
					
					if(distancia<BomberMan>(BM,BB)<=11){
						BM.energy--; 
					}
					
					
					Imprimir(Mapa);
					Imprimir_vida(14,BM.energy,Barra);
					
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
			int np=atoi(menu_tres.opcion.c_str()),nv=atoi(menu_cuatro.opcion.c_str()); //atoi sirve para convertir de String a int
		    int trunc = (int)(52/nv);        //para la barra
		    int victorias=0;
		    int derrotas=0;
		    ex=false;
		    
		    if(menu_cinco.opcion == "A" || menu_cinco.opcion == "a"){
		    
				while(np>0){
			    	Llenar_Mapa02();
					BomberMan BM(3,2,nv);
					BM.Pintar();
					DeadShots DS01(1,1);
					murioDS01 = false;
					DeadShots DS02(39,1);
					murioDS02 = false;
					DeadShots DS03(1,19);
					murioDS03 = false;
					DeadShots DS04(39,19);
					murioDS04 = false;
					Imprimir_Mapa(Mapa02);
					VidaBMapa02 = BM.energy;
					dificil = true;
					time = 0;
			    	while(dificil){
						char Barra2[2][52]={
				{'B','O','M','B','E','R','M','A','N',' ','E','N','E','R','G','Y',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				};
						posDS01x=DS01.x; posDS02x = DS02.x;posDS03x=DS03.x;posDS04x=DS04.x;
				  		posDS01y=DS01.y; posDS02y = DS02.y;posDS03y=DS03.y;posDS04y=DS04.y;		
						BM.Mover();
						BM.energy=VidaBMapa02;
						if(time%10==0)
						{
							DS01.Mover();
							DS02.Mover();
							DS03.Mover();
							DS04.Mover();
							
						}
						if(murioDS01!=true || DS01.exDS==true)		DS01.Bomba();      //es una probabilidad de poner una bomba
						if(murioDS02!=true || DS02.exDS==true)		DS02.Bomba(); 
						if(murioDS03!=true || DS03.exDS==true)		DS03.Bomba(); 
						if(murioDS04!=true || DS04.exDS==true)		DS04.Bomba(); 
					
						if(murioDS01!=true)		DS01.Pintar();
						if(murioDS02!=true)		DS02.Pintar();
						if(murioDS03!=true)		DS03.Pintar();
						if(murioDS04!=true)		DS04.Pintar();
						
						Sleep(20);
						BM.Pintar();        //como este metodo va despues de mover, entonces el bomberman siempre se pintará sobre las bombas y explosiones
						
						time++;
						
						Imprimir_Mapa(Mapa02);
						
						BM.PintarVida(Barra2,trunc);
						
						if(murioDS01==true && murioDS02==true && murioDS03==true && murioDS04==true)
						{
							m=0;
							for(j=19; j<29; j++)
							{
								Mapa02[10][j]=Victoria[m];
								m++;
							}
							dificil = false;
							victorias++;
							np--;
							Imprimir_Mapa(Mapa02);
							Sleep(2000);
							system("cls");
						}
						
						if(BM.energy == 0)
						{
							BM.Borrar();
							m=0;
							for(j=19; j<30; j++)
							{
								Mapa02[10][j]=Derrota[m];
								m++;
							}
							derrotas++;
							dificil = false;
							Imprimir_Mapa(Mapa02);
							np--;
							Sleep(2000);
							system("cls");
						}
					} 
		    	}
		    	w=to_string(victorias);
		    	l=to_string(derrotas);
		    	string menu_victoria[6] ={"              ¡VICTORIA!                     ",
									      "                                             ",
									      "    Numero partidas ganadas: "+w+"               ",
									      "    Numero partidas perdidas: "+l+"              ", 
										  "                                             ",   
				 						  "    Presiona x para volver al menu:          "};
				string menu_derrota[6] ={"              GAME OVER                      ",
										 "                                             ",
										 "    Numero partidas ganadas: "+w+"               ",
									     "    Numero partidas perdidas: "+l+"              ", 
									     "                                             ",
				 						 "    Presiona x para volver al menu:          "};
		    	if(victorias>derrotas){
		    		Menu victoria(6,9);
		    		victoria.draw(menu_victoria);
		    		if(victoria.opcion == "X" || victoria.opcion == "x") repetir=true;	
		    		else{
		    			repetir=false;
					}
				}else
				{
					Menu derrota(6,9);
		    		derrota.draw(menu_derrota);
		    		if(derrota.opcion == "X" || derrota.opcion == "x") repetir=true;
					else{
		    			repetir=false;
					}	
				}
		    	
		    	
		 	}
			else if(menu_cinco.opcion == "B" || menu_cinco.opcion == "b"){
				
				while(np>0){
			    	Llenar_Mapa03();
					BomberMan BM(3,2,nv);
					BM.Pintar();
					DeadShots DS01(1,1);
					murioDS01 = false;
					DeadShots DS02(39,1);
					murioDS02 = false;
					DeadShots DS03(1,19);
					murioDS03 = false;
					DeadShots DS04(39,19);
					murioDS04 = false;
					Imprimir_Mapa(Mapa02);
					
					VidaBMapa02 = BM.energy;
					dificil = true;
					time = 0;
			    	while(dificil){
						char Barra2[2][52]={
				{'B','O','M','B','E','R','M','A','N',' ','E','N','E','R','G','Y',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				};
						posDS01x=DS01.x; posDS02x = DS02.x;posDS03x=DS03.x;posDS04x=DS04.x;
				  		posDS01y=DS01.y; posDS02y = DS02.y;posDS03y=DS03.y;posDS04y=DS04.y;	
						  
						BM.Mover();	
						BM.energy=VidaBMapa02;
						if(time%10==0)
						{
							DS01.Mover();
							DS02.Mover();
							DS03.Mover();
							DS04.Mover();
							
						}
						if(murioDS01!=true || DS01.exDS==true)		DS01.Bomba();      //es una probabilidad de poner una bomba
						if(murioDS02!=true || DS02.exDS==true)		DS02.Bomba(); 
						if(murioDS03!=true || DS03.exDS==true)		DS03.Bomba(); 
						if(murioDS04!=true || DS04.exDS==true)		DS04.Bomba(); 
					
						if(murioDS01!=true)		DS01.Pintar();
						if(murioDS02!=true)		DS02.Pintar();
						if(murioDS03!=true)		DS03.Pintar();
						if(murioDS04!=true)		DS04.Pintar();
						
						Sleep(20);
						BM.Pintar();        //como este metodo va despues de mover, entonces el bomberman siempre se pintará sobre las bombas y explosiones
						
						time++;
						
						Imprimir_Mapa(Mapa02);
						
						BM.PintarVida(Barra2,trunc);
						
						if(murioDS01==true && murioDS02==true && murioDS03==true && murioDS04==true)
						{
							m=0;
							for(j=19; j<29; j++)
							{
								Mapa02[10][j]=Victoria[m];
								m++;
							}
							dificil = false;
							victorias++;
							np--;
							Imprimir_Mapa(Mapa02);
							Sleep(2000);
							system("cls");
						}
						
						if(BM.energy == 0)
						{
							BM.Borrar();
							m=0;
							for(j=19; j<30; j++)
							{
								Mapa02[10][j]=Derrota[m];
								m++;
							}
							derrotas++;
							dificil = false;
							Imprimir_Mapa(Mapa02);
							np--;
							Sleep(2000);
							system("cls");
						}
					} 
		    	}
		    	w=to_string(victorias);
		    	l=to_string(derrotas);
		    	string menu_victoria[6] ={"               ¡VICTORIA!                    ",
									      "                                             ",
									      "    Numero partidas ganadas: "+w+"               ",
									      "    Numero partidas perdidas: "+l+"              ", 
										  "                                             ",   
				 						  "    Presiona x para volver al menu:          "};
				string menu_derrota[6] ={"              GAME OVER                      ",
										 "                                             ",
										 "    Numero partidas ganadas: "+w+"               ",
									     "    Numero partidas perdidas: "+l+"              ", 
									     "                                             ",
				 						 "    Presiona x para volver al menu:          "};
		    	if(victorias>derrotas){
		    		Menu victoria(6,9);
		    		victoria.draw(menu_victoria);
		    		if(victoria.opcion == "X" || victoria.opcion == "x") repetir=true;	
		    		else{
		    			repetir=false;
					}
				}else
				{
					Menu derrota(6,9);
		    		derrota.draw(menu_derrota);
		    		if(derrota.opcion == "X" || derrota.opcion == "x") repetir=true;
					else{
		    			repetir=false;
					}	
				}
		 	}
		}
		else{
			system("cls");
			Menu menu_fi(1,5);
	    	menu_fi.draw(menu_final);
		}
		//Player_now.Ordenar(score_now);
		//Player_now.Salon_fama();
		}
	}

}
 

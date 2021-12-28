#include "iostream"
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include "windows.h"

#define DERECHA 77
#define IZQUIERDA 75
#define ARRIBA 72
#define ABAJO 80
#define FIL 28 
#define COL 33
using namespace std;
const int mn=41, bn=13; 
int i,j;
char move;
char muro=178;
int nivel;
char h = 205, v = 186, e1 = 201, e2 = 200, e3=187, e4=188; ///defino valores para dibujar un marco en consola 

void mover_XY(int x, int y){    HANDLE  hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}
void draw(){
	
    ///lineas horizontales
    for (int i = 2; i < 78; i++) {
        ///arriba
        mover_XY(i, 3); ///nos situamos en la posicion i y en el eje y nos situamos a 3 espacios        			 
        cout<<h; ///imprimir el simbolo especificando que pertenece al codigo ascii
        ///abajo
        mover_XY(i, 23);///nos situamos en la posicion i y en el eje y nos situamos a 23 espacios
        cout<<h; ///imprimir el simbolo especificando que pertenece al codigo ascii
        
    }

    ///lineas verticales
    for (int i = 4; i < 23; i++) {
        mover_XY(2, i); ///nos situamos en el eje x= 2 y en el eje y la i varie
        cout<<v; ///imprimir el simbolo especificando que pertenece al codigo ascii
        mover_XY(77, i);///nos situamos en el eje x= 77 y en el eje y la i varie
        cout<<v; ///imprimir el simbolo especificando que pertenece al codigo ascii
    }
    ///esquinas
    mover_XY(2,3);cout<<e1;
    mover_XY(2,23);cout<<e2;
    mover_XY(77,3);cout<<e3;
    mover_XY(77,23);cout<<e4;
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
char movimiento(){
	int x=rand()%4+1;
	
	if (x==1)
	{
		move='a';
	}
	else if (x==2)
	{
		move='s';
	}
	else if (x==3)
	{
		move='w';
	}
	else if (x==4)
	{
		move='d';
	}
	return move;
}
int main()
{
	char empezar, posicion;
    char Mapa[mn][mn];
    int f=1,c=1, m,n, t=0;
    int x = 19, y=19, tecla; 
    int nivel, partidas, vidas, jugador;
    draw();
	mover_XY(22,12);cout<<"presione x para empezar"; cin>>empezar;
	
	
	
		if(empezar == 'x'){
	        system("cls"); ///limpiar pantalla
	        draw(); ///volver a dibujar el marco
	        mover_XY(22,10);cout<<"seleccione el nivel"
								"\n\n\t\t\t1. facil"
								"\n\n\t\t\t2. dificil"<<endl;
	
			mover_XY(22,16);cout<<"seleccion: "; cin>>nivel;
			
			if (nivel==1)
			{
				for(i=0; i<mn/2+1; i++)
			{
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
			
	char BigBoss[bn][bn]=
	{
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
	
	Imprimir(Mapa);
	
			
		mover_XY(x, y); cout<<(char)42;//bomberman
	while (true)
	{
		
		
		do
		{
			move=movimiento();
		}
		while(move=='a' and c<3 or move=='s' and f>(mn/2)-(bn-1) or move=='w' and f<3 or move=='d' and c>mn-(bn+2));
		
		
		for(i=0; i<mn/2+1; i++)
		{
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
		
		mover_XY(x, y); cout<<(char)42;
		tecla = getch(); 
		
		if(tecla == DERECHA || tecla == IZQUIERDA || tecla == ARRIBA || tecla == ABAJO){
		}
		if(tecla == DERECHA && Mapa[y][x+1] != '°'){
			x++;
		}
		if(tecla == IZQUIERDA && Mapa[y][x-1] != '°'){
			x--;
		}
		if(tecla == ARRIBA && Mapa[y-1][x] != '°'){
			y--;
		}
		if(tecla == ABAJO && Mapa[y+1][x] != '°'){
			y++;
		}
		
		if(move=='a')
		{
			c-=2;
		}
		else if(move=='d')
		{
			c+=2;
		}
		else if(move=='w')
		{
			f-=2;
		}
		else 
		{
			f+=2;
		}
		
		
		
		m=0; 
		for(i=f; i<f+11; i++)
		{
			n=0;	
			for(j=c; j<c+13; j++)
			{
				Mapa[i][j]=BigBoss[m][n];
				n++;
			}
			m++;
		}
	
		Imprimir(Mapa);
	}}
	 else if(nivel==2){
        	system("cls");
        	draw();
        	mover_XY(22,12); cout<<"Ingrese el numero de partidas:"; cin>>partidas;
        	system("cls");
        	draw();
        	mover_XY(22,12); cout<<"Numero de partidas seleccionadas:"<<partidas<<endl;
        	mover_XY(22,14); cout<<"Ingrese el numero de vidas:"; cin >> vidas;
        	system("cls");
        	draw();
        	mover_XY(22,12); cout<<"Numero de partidas seleccionadas:"<<partidas<<endl;
        	mover_XY(22,14); cout<<"Numero de vidas seleccionadas:"<<vidas<<endl;
        	mover_XY(22,16); cout<<"Posicion aleatoria(A) o por dafauil(D):"; cin>>posicion;
        	system("cls");
        	draw();
        	mover_XY(22,12); cout<<"Numero de partidas seleccionadas:"<<partidas<<endl;
        	mover_XY(22,14); cout<<"Numero de vidas seleccionadas:"<<vidas<<endl;
        	if(posicion == 'a' || posicion == 'A'){
        	    mover_XY(22,16); cout<<"posicion seleccionada: Aleatoria"<<endl;
        	}
        	else if(posicion == 'd' || posicion == 'D'){
        	    mover_XY(22,16); cout<<"posicion seleccionada: Default"<<endl;
        	}
			else {
				mover_XY(22,16); cout<<"solo puede ingresa aleatoria(A) o  dafauil(D) "<<endl;
			}
        }

	}else{
		system("cls"); ///limpiamos pantalla 
    	draw();
        mover_XY(22,12);cout<<"ha seleccionado una tecla diferente"<<endl;
    }

	
	

	system("pause >null");
    return 0;
}



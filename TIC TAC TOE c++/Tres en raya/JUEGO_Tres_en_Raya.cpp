/**********************************************************
 *  PROGRAMA CREADO POR ELMO ABRAHAM SµNCHEZ MIRAMONTES   *
 *  Tepic, Nayarit, M‚xico                                *
 *  elabra_sanchez@hotmail.com                            *
 **********************************************************/

#include <conio.h>
#include <stdio.h>

#define HUMANO  1
#define COMPU   -1

class gato
{
	// Datos del juego
	int tablero[3][3];
	int turno;
	// Necesitan an lisis
	int  mejor_jugada;
	int  puntos_mejor;
	// Suban lisis
	gato *siguiente;

	// Funciones
		int  evalua_aqui();
		int  evalua_alla();
		int  busca_jugada(int comienzo);
		void nuevo_ana();
	public:
		int  haz_mejor_jugada();
		int  pedir_jugada(int x,int y);
		int  ganador(int x,int y);
		void efectua(int mov);
		void nuevo();
		void imprimir(int x,int y);
};

int gato::ganador(int x,int y)
{
	int aux;
	aux=evalua_aqui();
	if (x>0 && y>0 && aux!=7)
	{
		gotoxy(x,y);
		if (aux*turno==1) {textcolor(LIGHTMAGENTA);cprintf("GANAN: O");}
		else if (aux*turno==-1) {textcolor(LIGHTGREEN);cprintf("GANAN: X");}
		else if (aux==0) {textcolor(BROWN);cprintf("EMPATE");}
	}
	return(aux==7 ? 7 : -aux*turno);
}

int gato::pedir_jugada(int x,int y)
{
	char letra;
	int x_cur=0,y_cur=0;

	do
	{
		imprimir(x,y);
		textcolor(YELLOW);
		gotoxy(x+x_cur*4,y+y_cur*2);
		cprintf("(");
		gotoxy(x+x_cur*4+2,y+y_cur*2);
		cprintf(")");
		letra=getch();
		if (letra==0)
		{
			letra=getch();
			switch (letra)
			{case 'H': y_cur--;break;
			 case 'P': y_cur++;break;
			 case 'K': x_cur--;break;
			 case 'M': x_cur++;break;}
			if (x_cur>2) x_cur=0;
			else if (x_cur<0) x_cur=2;
			if (y_cur>2) y_cur=0;
			else if (y_cur<0) y_cur=2;
		}
	}while((tablero[x_cur][y_cur]!=0 || letra!=13) && letra!=27);
	if (letra!=27)
	{
		tablero[x_cur][y_cur]=turno;
		turno=-turno;
	}
	return(letra==27 ? NULL : 1);
}

int gato::haz_mejor_jugada()
{
	if (evalua_aqui()==7)
	{
		nuevo_ana();
		evalua_alla();
		efectua(mejor_jugada);
	}
	return(1);
}

int  gato::evalua_alla()
{
	int aux,jugada;
	int sietes=0,ceros=0;

	nuevo_ana();
	siguiente=new gato;
	jugada=busca_jugada(0);

	while (jugada!=0 && puntos_mejor!=1)
	{
		*siguiente=*this;
		siguiente->nuevo_ana();
		siguiente->efectua(jugada);
		aux=siguiente->evalua_aqui();
		if (aux==7) sietes++;
		else if (aux==0)
		{
			ceros++;
			mejor_jugada=jugada;
		}
		else
		{
			puntos_mejor=1;
			mejor_jugada=jugada;
		}
		jugada=busca_jugada(jugada);
	}
	if (puntos_mejor!=1 && sietes+ceros>1 && sietes>0)
	{
		puntos_mejor=-1;
		mejor_jugada=0;
		jugada=busca_jugada(0);
		while (jugada!=0 && puntos_mejor!=1)
		{
			*siguiente=*this;
			siguiente->nuevo_ana();
			siguiente->efectua(jugada);
			aux= - siguiente->evalua_alla();
			if (aux>puntos_mejor)
			{
				puntos_mejor=aux;
				mejor_jugada=jugada;
			}
			jugada=busca_jugada(jugada);
		}
	};
	delete siguiente;
	siguiente=NULL;
	return(puntos_mejor);
}

int gato::evalua_aqui()
{
	int prueba=0,i;

	for (i=0;prueba!=3 && prueba!=-3 && i<3;i++)
		prueba=tablero[0][i]+tablero[1][i]+tablero[2][i];
	for (i=0;prueba!=3 && prueba!=-3 && i<3;i++)
		prueba=tablero[i][0]+tablero[i][1]+tablero[i][2];
	for (i=0;prueba!=3 && prueba!=-3 && i<2;i++)
		prueba=tablero[0+2*i][0]+tablero[1][1]+tablero[2-2*i][2];
	if (prueba==3 || prueba==-3) return(1);
	else return(busca_jugada(0)==0 ? 0 : 7);
}

int gato::busca_jugada(int comienzo)
{
	while (tablero[comienzo/3][comienzo%3]!=0 && comienzo<9)
		comienzo++;
	return(comienzo!=9 ? comienzo+1 : 0);
}

void gato::efectua(int mov)
{
	if (mov>=1 && mov<=9)
	{
		mov--;
		tablero[mov/3][mov%3]=turno;
		turno=-turno;
	}
}

void gato::nuevo()
{
	for (int i=0;i<9;i++)
		tablero[i/3][i%3]=0;
	turno=1;
}

void gato::nuevo_ana()
{
	mejor_jugada=NULL;
	puntos_mejor=NULL;
	siguiente=NULL;
}


void gato::imprimir(int x,int y)
{
	int i;
	for (i=0;i<11;i++)
	{
		textcolor(WHITE);
		gotoxy(x+i,y+1);
		cprintf("Í");
		gotoxy(x+i,y+3);
		cprintf("Í");
		if (i<5)
		{
			gotoxy(x+3,y+i);
			cprintf("º");
			gotoxy(x+7,y+i);
			cprintf("º");
		}
		if (i<9)
		{
			gotoxy(x+(i/3)*4,y+(i%3)*2);
			if (tablero[i/3][i%3]==1)
			{
				textcolor(LIGHTRED);
				cprintf(" X ");
			}
			else if (tablero[i/3][i%3]==-1)
			{
				textcolor(LIGHTBLUE);
				cprintf(" O ");
			}
			else cprintf("   ");
		}
	}
	textcolor(WHITE);
	gotoxy(x+3,y+1);cprintf("Î");
	gotoxy(x+3,y+3);cprintf("Î");
	gotoxy(x+7,y+1);cprintf("Î");
	gotoxy(x+7,y+3);cprintf("Î");
}

int haz_juego(int x,int y,int primero,int segundo);

void main()
{
	int x=1,y=1;
	int fin=NULL;
	int jug1;

	clrscr();
	jug1=HUMANO;
	while (fin!=7)
	{
		fin=haz_juego(x,y,jug1,-jug1);
		x+=14;
		if (x>66)
		{
			x=1;
			y+=7;
		}
		if (y>18)
		{
			x=1;
			y=1;
			getch();
			clrscr();
		}
		jug1=-jug1;
	}
}

int haz_juego(int x,int y,int primero,int segundo)
{
	gato prueba;
	int num;

	prueba.nuevo();
	prueba.imprimir(x,y);
	do
	{
			if   (primero==HUMANO) num=prueba.pedir_jugada(x,y);
			else num=prueba.haz_mejor_jugada();
			prueba.imprimir(x,y);
		if (prueba.ganador(0,0)==7 && num!=NULL)
		{
			if  (segundo==HUMANO) num=prueba.pedir_jugada(x,y);
			else num=prueba.haz_mejor_jugada();
			prueba.imprimir(x,y);
		}
	}while (prueba.ganador(0,0)==7 && num!=NULL);
	if (num==NULL) return(7);
	else return(prueba.ganador(x+1,y+5));
}
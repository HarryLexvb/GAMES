#include <iostream>
#include <windows.h>
#include <ctime>
//#include <thread>         // std::thread


using namespace std;


bool game_running = true ;

int x = 2;
int y = 2 ;
int ex = 4;
int ey = 8;
int posxb;
int posyb;

char map[12][23] = {"$$$$$$$$$$$$$$$$$$$$$$",
					"$$$$$$$$$$$$$$$$$$$$$$",
					"$$                  $$",
					"$$   ###      ###   $$",
					"$$    #        #   #$$",
					"$$                 #$$",
					"$$                 #$$",
					"$$      #####      #$$",
					"$$                  $$",
					"$$$$$$$$$$$$$$$$$$$$$$",
					"$$$$$$$$$$$$$$$$$$$$$$"};

void printmapa()
{
	system("cls");
	for(int display = 0 ; display <11 ; display++)
	{
		cout<<map[display]<<endl;
	}
	system ("pause>nul");
}

void dibujarbomba()
{
	posyb = y;
	posxb = x;
	map[y][x] = 250;
	printmapa();
}
void explosionbomba()
{
	if(map[posyb-2][posxb] != '$')
		map[posyb-2][posxb] = 250;
	if(map[posyb-1][posxb] != '$')
		map[posyb-1][posxb] = 250;
	if(map[posyb][posxb] != '$')
		map[posyb][posxb] = 250;
	if(map[posyb+1][posxb]!= '$')
		map[posyb+1][posxb] = 250;
	if(map[posyb+2][posxb] != '$')
		map[posyb+2][posxb] = 250;
	if(map[posyb][posxb-2] != '$')
		map[posyb][posxb-2] = 250;
	if(map[posyb][posxb-1] != '$')
		map[posyb][posxb-1] = 250;
	if(map[posyb][posxb+1] != '$' )
		map[posyb][posxb+1] = 250;
	if(map[posyb][posxb+2] != '$')
		map[posyb][posxb+2] = 250;
	
	printmapa();
}
void destruccion()
{	

	if(map[posyb-2][posxb] != '$')
		map[posyb-2][posxb] = ' ';
	if(map[posyb-1][posxb] != '$')
		map[posyb-1][posxb] = ' ';
	if(map[posyb][posxb] != '$')
		map[posyb][posxb] = ' ';
	if(map[posyb+1][posxb]!= '$')
		map[posyb+1][posxb] = ' ';
	if(map[posyb+2][posxb] != '$')
		map[posyb+2][posxb] = ' ';
	if(map[posyb][posxb-2] != '$')
		map[posyb][posxb-2] = ' ';
	if(map[posyb][posxb-1] != '$')
		map[posyb][posxb-1] = ' ';
	if(map[posyb][posxb+1] != '$')
		map[posyb][posxb+1] = ' ';
	if(map[posyb][posxb+2] != '$')
		map[posyb][posxb+2] = ' ';
	posxb = 0;
	posyb = 0;
	printmapa();
}

void movimientoenemigo()
{
	//map[ex][ey] = 'X';
	int random = rand()%(4)+1;
	if(random == 1)
		{
			int ey_ = ey+1;
			if(map[ey_][ex] == ' ')
			{
				
				map[ey][ex] = ' ' ;
				ey++;
				map[ey][ex] = 'X';
				
			}
			//printmapa();
		}
		if(random == 2)
		{
			int ey_ = ey-1;
			if(map[ey_][ex] == ' ')
			{
				map[ey][ex] = ' ' ;
				ey--;
				map[ey][ex] = 'X';	
			}//printmapa();
		}
		if(random == 3)
		{
			int ex_ = ex+1;
			if(map[ey][ex_] == ' ')
			{
				map[ey][ex] = ' ' ;
				ex++;
				map[ey][ex] = 'X';
				
			}//printmapa();
		}

		if(random == 4)
		{
			int ex_ = ex-1;
			if(map[ey][ex_] == ' ')
			{
					map[ey][ex] = ' ' ;
					ex--;
					map[ey][ex] = 'X';
			}//printmapa();
		}


}
void movimiento()
{
	if(GetAsyncKeyState(VK_DOWN))
		{
			int y_ = y+1;
			if(map[y_][x] == ' ')
			{
				if(x == posxb && y == posyb)
				{
					y++;
					map[y][x] = 'O';
				}
				else
				{
					map[y][x] = ' ' ;
					y++;
					map[y][x] = 'O';
				}
			}
			printmapa();
		}
		if(GetAsyncKeyState(VK_UP))
		{
			int y_ = y-1;
			if(map[y_][x] == ' ')
			{
				if(x == posxb && y == posyb)
				{
					y--;
					map[y][x] = 'O';
				}
				else
				{
					map[y][x] = ' ' ;
					y--;
					map[y][x] = 'O';
				}
			}printmapa();
		}
		if(GetAsyncKeyState(VK_RIGHT))
		{
			int x_ = x+1;
			if(map[y][x_] == ' ')
			{
				if(x == posxb && y == posyb)
				{
					x++;
					map[y][x] = 'O';
				}	
				else
				{	
					map[y][x] = ' ' ;
					x++;
					map[y][x] = 'O';
				}
			}printmapa();
		}

		if(GetAsyncKeyState(VK_LEFT))
		{
			int x_ = x-1;
			if(map[y][x_] == ' ')
			{
				if(x == posxb && y == posyb)
				{
					x--;
					map[y][x] = 'O';
				}
				else
				{	
					map[y][x] = ' ' ;
					x--;
					map[y][x] = 'O';
				}
			}printmapa();
		}
}


int main ()
{
	srand(time(NULL));
	while(game_running = true)
	{
		
		movimientoenemigo();
		movimiento();
		if(GetAsyncKeyState(VK_SPACE))
		{

			dibujarbomba();
			movimientoenemigo();
			movimiento();
			movimientoenemigo();	
			movimiento();
			movimientoenemigo();
			explosionbomba();
			if(x == posxb && y == posyb || x == posxb && y == posyb-1 || x == posxb && y == posyb-2 || x == posxb && y == posyb+1 || x == posxb && y == posyb+2|| 
			x == posxb-1 && y == posyb || x == posxb-2 && y == posyb || x == posxb+1 && y == posyb || x == posxb+2 && y == posyb)
			return EXIT_SUCCESS;
			destruccion();
			
		}
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			return(EXIT_SUCCESS);
		}
	}
}

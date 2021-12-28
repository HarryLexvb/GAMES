#include <iostream>
#include <windows.h>
       


using namespace std;


bool game_running = true ;
bool bomba = false;

int x = 1 ;
int y = 1 ;
int posxb;
int posyb;

char map[10][20] = {"##################",
					"#*               #",
					"#                #",
					"#                #",
					"#                #",
					"#                #",
					"#                #",
					"#                #",
					"##################"};

void printmapa()
{
	system("cls");
	for(int display = 0 ; display <10 ; display++)
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
			//Sleep(500);
			map[posyb-2][posxb] = 250;
			map[posyb-1][posxb] = 250;
			map[posyb][posxb] = 250;
			map[posyb+1][posxb] = 250;
			map[posyb+2][posxb] = 250;
			map[posyb][posxb-2] = 250;
			map[posyb][posxb-1] = 250;
			map[posyb][posxb+1] = 250;
			map[posyb][posxb+2] = 250;
			printmapa();
}
void destruccion()
{
	map[posyb-2][posxb] = ' ';
	map[posyb-1][posxb] = ' ';
	map[posyb][posxb] = ' ';
	map[posyb+1][posxb] = ' ';
	map[posyb+2][posxb] = ' ';
	map[posyb][posxb-2] = ' ';
	map[posyb][posxb-1] = ' ';
	map[posyb][posxb+1] = ' ';
	map[posyb][posxb+2] = ' ';
	printmapa();
}

void movimiento()
{
	if(GetAsyncKeyState(VK_DOWN))
		{
			int y_ = y+1;
			if(map[y_][x] == ' ')
			{
				map[y][x] = ' ' ;
				y++;
				map[y][x] = '*';
			}printmapa();
		}
		if(GetAsyncKeyState(VK_UP))
		{
			int y_ = y-1;
			if(map[y_][x] == ' ')
			{
				map[y][x] = ' ' ;
				y--;
				map[y][x] = '*';
			}printmapa();
		}
		if(GetAsyncKeyState(VK_RIGHT))
		{
			int x_ = x+1;
			if(map[y][x_] == ' ')
			{
				map[y][x] = ' ' ;
				x++;
				map[y][x] = '*';
			}printmapa();
		}

		if(GetAsyncKeyState(VK_LEFT))
		{
			int x_ = x-1;
			if(map[y][x_] == ' ')
			{
				map[y][x] = ' ' ;
				x--;
				map[y][x] = '*';
			}printmapa();
		}
}


int main ()
{
	while(game_running = true)
	{
		
		movimiento();
		if(GetAsyncKeyState(VK_SPACE))
		{

			dibujarbomba();
			movimiento();
			movimiento();	
			movimiento();
			explosionbomba();
			destruccion();
			/*
			Sleep(1000);
			
			*/
		}
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			return(EXIT_SUCCESS);
		}
	}
}
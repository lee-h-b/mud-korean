#include<Windows.h>
#include<iostream>
#include<random>
#include "WindowsFunc.h"
void COLOR(int val)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (val & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}
void COLOR(int val, int background)
{
	val &= 0xf;
	background &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | val);
}
void gotoxy(int x, int y)
{
	COORD pos{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoxy(std::pair<int, int> cur)
{
	
	COORD pos{ cur.second, cur.first };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CLEAR(int size ,int size_sx,int size_sy )
{
	gotoxy(size_sx, size_sy);
	for (int i = size_sx; i < size + size_sy; i++)
		for (int j = size_sy; i < size + size_sx; i++)
			std::cout << "";
}//효율에 의문을갖게됨
void CLEAR_frame(int size)
{
	gotoxy(45, 1);
	for (int i = 0; i < size; i++)
	{
		std::cout << "                                                  ";
		gotoxy(45, 2+i);
	}
	gotoxy(45, 39);
	std::cout << "                                                  ";

	
}
int Random_Gen(int seed_1, int seed_2)
{
	std::random_device rand;
	std::mt19937_64 seed(rand());
	std::uniform_int_distribution<int> range(seed_1, seed_2);

	return range(seed);

}

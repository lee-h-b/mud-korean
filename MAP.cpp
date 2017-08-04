#pragma once
#include "MAP.h"
#include"WindowsFunc.h"


CMAP::CMAP(int _size )
	:Rect(0,_size),max_bar(6), drunker(Rect, Rect, max_bar)
{
	check = true;
	MAP = new char*[Rect.second];
	this->Map_init();
}
void CMAP::Map_Set()
{
	std::random_device rand;
	for (int i = 0; i < Rect.second + Rect.second; i++)
	{
		std::mt19937_64 seed(rand());
		drunker.Randomdrawing(seed,MAP);
		if (i + 1 == Rect.second + Rect.second)
		{
			drunker.Exit_Draw(MAP);
			this->E_Point = drunker.Get_now();
		}
	}
}
void CMAP::Map_init()
{//∏ √ ±‚»≠
	for (int i = 0; i < Rect.second; i++)
	{
		MAP[i] = new char[Rect.second];

		for (int j = 0; j < Rect.second; j++)
		{
			MAP[i][j] = '#';
		}
	}

}
void CMAP::Map_Drawing()
{
	for (int i = 0; i < Rect.second; i++)
	{
		for (int j = 0; j < Rect.second; j++)
		{
			if (MAP[i][j] == 'S')
			{
				this->set_start(i,j);
				COLOR(14,10);
			}
			else if (MAP[i][j] == 'E')
			{
				COLOR(14,10);
			}
			else		
			COLOR(15, 0);
			std::cout << MAP[i][j];
		}
		COLOR(15, 0);
		std::cout << std::endl;
	}
}




CMAP::~CMAP()
{
/*	for (int i = 0; i < this->Rect.second; ++i) {
		delete[] MAP[i];
	}
	delete[] MAP;
*/
}

void CMAP::Reset()
{
	this->Map_init();
	this->Map_Set();
	this->Map_Drawing();
}
